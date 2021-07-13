// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumablePickupItem.h"

// Sets default values
AConsumablePickupItem::AConsumablePickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	//Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AConsumablePickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConsumablePickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AConsumablePickupItem::Interacted_Implementation(AActor* OtherActor)
{
	//Action the actor that pickup the object not implemented yet.
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Item " + ItemName + " picked"));
	//after notify the actor inventory  destroy the item
	Destroy();
}

