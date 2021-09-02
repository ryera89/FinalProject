// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionObjectPickUp.h"
#include "../FinalProjectCharacter.h"

// Sets default values
AMissionObjectPickUp::AMissionObjectPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AMissionObjectPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMissionObjectPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMissionObjectPickUp::Interacted_Implementation(AActor* OtherActor)
{
	InteractedEvent.Broadcast();

	AFinalProjectCharacter* PlayerCharacter = Cast<AFinalProjectCharacter>(OtherActor);
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->InventoryComponent->AddMissionObjectItem(MissionObjectType, 1);
	}
	
	//Action the actor that pickup the object not implemented yet.
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Item " + ItemName + " picked"));
	//after notify the actor inventory  destroy the item
	Destroy();
}

