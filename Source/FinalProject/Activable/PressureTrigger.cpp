// Fill out your copyright notice in the Description page of Project Settings.


#include "PressureTrigger.h"
#include "../FinalProjectCharacter.h"
#include "../Interfaces/Animation.h"

// Sets default values
APressureTrigger::APressureTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

}

// Called when the game starts or when spawned
void APressureTrigger::BeginPlay()
{
	Super::BeginPlay();

	//Get the animable components of the actors actors who inherit from this class
	TInlineComponentArray<USceneComponent*> SceneComponents(this);

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, 
	//	FString::Printf(TEXT("Scene Components Found on activable actor %i"),SceneComponents.Num()));
	//Get the meshes who has the tag "Animable"
	for (USceneComponent* component : SceneComponents)
	{
		if (component->ComponentHasTag(FName("Animable")))
		{
			AnimableComponents.Add(component);
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("Animable Components Found %i"),AnimableComponents.Num()));
	TArray<UActorComponent*> AnimArray = GetComponentsByInterface(UAnimation::StaticClass());
	/*Only one Animation component will be used*/
	if (AnimArray.Num()) Animation = Cast<IAnimation>(AnimArray[0]);

	if (Animation != nullptr)
	{
		Animation->SetStartingPropertiesValues_Implementation(AnimableComponents);
		//Rearm(Deactivate) the trigger once the activation animation has finished.
		Animation->OnAnimationEnded().AddUObject(this, &APressureTrigger::RearmTrigger);
	}
}

void APressureTrigger::ChangeState_Implementation()
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

void APressureTrigger::Activated_Implementation()
{
	State = EActivableState::Activated;

	if (Animation != nullptr) Animation->Play_Implementation();

	ActivableStateChangedEvent.Broadcast(State);
}

void APressureTrigger::Deactivated_Implementation()
{
	State = EActivableState::Deactivated;

	if (Animation != nullptr) Animation->Reverse_Implementation();

	ActivableStateChangedEvent.Broadcast(State);
}

void APressureTrigger::RearmTrigger()
{
	if (State == EActivableState::Activated)
	{
		TArray<AActor*> OverlapingCharacters;
	    GetOverlappingActors(OverlapingCharacters, ACharacter::StaticClass());
		//If there isn't overlaping characters rearm the trigger in code deactivate state.
		if (OverlapingCharacters.Num() == 0)
		{
			Deactivated_Implementation();
		}
	}

}

// Called every frame
void APressureTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APressureTrigger::IsAnimationPlaying_Implementation() const
{
	if (Animation != nullptr)
	{
		return Animation->IsPlaying_Implementation();
	}
	return false;
}

void APressureTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//Avaluate if the activation should have a delay.
	//Check is the actor is a character.
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		if (State == EActivableState::Deactivated)
		{
			Activated_Implementation();
		}
	
	}
}

void APressureTrigger::NotifyActorEndOverlap(AActor* OtherActor)
{
	//Check is the actor is a character.
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		if (State == EActivableState::Activated  && !IsAnimationPlaying_Implementation())
		{
			Deactivated_Implementation();
		}
	}
}

