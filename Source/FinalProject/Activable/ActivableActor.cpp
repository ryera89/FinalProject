// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivableActor.h"
#include "../FinalProjectCharacter.h"
#include "../Interfaces/Animation.h"
#include "../Interfaces/Interactable.h"

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

	if (Animation != nullptr) Animation->SetStartingPropertiesValues_Implementation(AnimableComponents);

	if (TriggerEventSource != nullptr)
	{
		TriggerEventSource->OnInteracted().AddUObject(this, &AActivableActor::ChangeState_Implementation);
	}
}

// Called every frame
void AActivableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActivableActor::ChangeState_Implementation()
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

