// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivableActor.h"
#include "ActivableActor.h"

// Sets default values
AActivableActor::AActivableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActivableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActivableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActivableActor::Interacted_Implementation(AActor* OtherActor)
{
	if (IsActive_Implementation())
	{
		Deactivated_Implementation();
	}
	else
	{
		Activated_Implementation();
	}
}

void AActivableActor::Activated_Implementation()
{
	bIsActive = true;
	OnActivatedStateChanged.Broadcast(true);
}

void AActivableActor::Deactivated_Implementation()
{
	bIsActive = false;
	OnActivatedStateChanged.Broadcast(false);
}

