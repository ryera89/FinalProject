// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivableActor.h"
#include "ActivableActor.h"
#include "../FinalProjectCharacter.h"
#include "../Animations/AnimationBaseComponent.h"

// Sets default values
AActivableActor::AActivableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AActivableActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetComponents(AnimationComponents);
}

// Called every frame
void AActivableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActivableActor::Interacted_Implementation(AActor* OtherActor)
{
	//Execute only if the Actor is not currently in transition (animation)
	if (!IsInTransition_Implementation())
	{
		if (IsActive_Implementation())
		{
			Deactivated_Implementation();
			if (AFinalProjectCharacter* Character = Cast<AFinalProjectCharacter>(OtherActor))
			{
				Character->InteractionHint.ExecuteIfBound(ActivationHint + " " + ActivableActorName, true);
			}
		}
		else
		{
			Activated_Implementation();
			if (AFinalProjectCharacter* Character = Cast<AFinalProjectCharacter>(OtherActor))
			{
				Character->InteractionHint.ExecuteIfBound(DeactivationHint + " " + ActivableActorName, true);
			}
		}

	}
}

FString AActivableActor::InteractionHint_Implementation() const
{
	return (IsActive_Implementation()) ? DeactivationHint : ActivationHint;
}

void AActivableActor::Activated_Implementation()
{
	bIsActive = true;
	//If the actor has animation components then turn on the activation transitions
	//the animation component will be responsible for notifying the actor when the transition ends
	if (AnimationComponents.Num() > 0) SetTransitionState_Implementation(true);

	OnActivatedStateChanged.Broadcast(true);
}

void AActivableActor::Deactivated_Implementation()
{
	bIsActive = false;
	//If the actor has animation components then turn on the activation transitions
	//the animation component will be responsible for notifying the actor when the transition ends
	if (AnimationComponents.Num() > 0) SetTransitionState_Implementation(true);

	OnActivatedStateChanged.Broadcast(false);
}

