// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivableActor.h"
#include "../FinalProjectCharacter.h"
#include "../Interfaces/Animation.h"

// Sets default values
AActivableActor::AActivableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;
}

// Called when the game starts or when spawned
void AActivableActor::BeginPlay()
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
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("Animation Components Found %i"),AnimArray.Num()));
	/*Only one Animation component will be used*/
	if (AnimArray.Num()) Animation = Cast<IAnimation>(AnimArray[0]);

	if (Animation != nullptr) Animation->SetStartingPropertiesValues_Implementation(AnimableComponents);
}

// Called every frame
void AActivableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AActivableActor::IsAnimationPlaying_Implementation() const
{
	if (Animation != nullptr)
	{
		return Animation->IsPlaying_Implementation();
	}
	return false;
}

void AActivableActor::Activated_Implementation()
{
	State = EActivableState::Activated;

	if (Animation != nullptr) Animation->Play_Implementation();

	ActivableStateChangedEvent.Broadcast(State);
}

void AActivableActor::Deactivated_Implementation()
{
	State = EActivableState::Deactivated;

	if (Animation != nullptr) Animation->Reverse_Implementation();

	ActivableStateChangedEvent.Broadcast(State);
}

