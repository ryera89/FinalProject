// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterActivableActor.h"
#include "../FinalProjectCharacter.h"
#include "../Interfaces/Animation.h"

// Sets default values
ACharacterActivableActor::ACharacterActivableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;
}

// Called when the game starts or when spawned
void ACharacterActivableActor::BeginPlay()
{
	Super::BeginPlay();

	//Get the animable components of the actors actors who inherit from this class
	TInlineComponentArray<USceneComponent*> SceneComponents(this);
	//Get the meshes who has the tag "Animable"
	for (USceneComponent* component : SceneComponents)
	{
		if (component->ComponentHasTag(FName("Animable")))
		{
			AnimableComponents.Add(component);
		}
	}
	TArray<UActorComponent*> AnimArray = GetComponentsByInterface(UAnimation::StaticClass());
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("Animation Components Found %i"),AnimArray.Num()));
	/*Only one Animation component will be used*/
	if (AnimArray.Num()) Animation = Cast<IAnimation>(AnimArray[0]);

	if (Animation != nullptr) Animation->SetStartingPropertiesValues_Implementation(AnimableComponents);

}

// Called every frame
void ACharacterActivableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterActivableActor::Interacted_Implementation(AActor* OtherActor)
{
	
	//Execute only if the the animations is not playing
	if (!IsAnimationPlaying_Implementation())
	{
		InteractedEvent.Broadcast();

		switch (State)
		{
		case EActivableState::Activated:
		{
			Deactivated_Implementation();
			if (AFinalProjectCharacter* Character = Cast<AFinalProjectCharacter>(OtherActor))
			{
				Character->InteractionHint.ExecuteIfBound(ActivationHint + " " + ActivableActorName, true);
			}
			break;
		}
		case EActivableState::Deactivated:
		{
			Activated_Implementation();
			if (AFinalProjectCharacter* Character = Cast<AFinalProjectCharacter>(OtherActor))
			{
				Character->InteractionHint.ExecuteIfBound(DeactivationHint + " " + ActivableActorName, true);
			}
			break;
		}
		default:
			break;
		}
	}
}

FString ACharacterActivableActor::InteractionHint_Implementation() const
{
	switch (State)
	{
	case EActivableState::Activated:
		return DeactivationHint;
	case EActivableState::Deactivated:
		return ActivationHint;
	default:
		return FString();
	}
}

void ACharacterActivableActor::ChangeState_Implementation()
{
	if (State == EActivableState::Activated)
	{
		Deactivated_Implementation();
	}
	else
	{
		Activated_Implementation();
	}
}

bool ACharacterActivableActor::IsAnimationPlaying_Implementation() const
{
	if (Animation != nullptr)
	{
		return Animation->IsPlaying_Implementation();
	}
	return false;
}

void ACharacterActivableActor::Activated_Implementation()
{
	State = EActivableState::Activated;

	if (Animation != nullptr) Animation->PlayFromStart_Implementation();

	ActivableStateChangedEvent.Broadcast(State);
}

void ACharacterActivableActor::Deactivated_Implementation()
{
	State = EActivableState::Deactivated;

	if (Animation != nullptr) Animation->ReverseFromEnd_Implementation();

	ActivableStateChangedEvent.Broadcast(State);
}

