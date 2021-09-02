// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

/** Pickup item category/types enum (ie consumable, key, weapon etc...)*/
UENUM()
enum class EItemType : uint8
{
	Consumable, //potions, food, etc
	Key,
	Weapon,
	MissionObject,
};
UENUM()
enum class EConsumableItemType : uint8
{
	HealthPotion,
	EnergyPotion,
};
UENUM()
enum class EMissionObjectItemType : uint8
{
	SunSpear,
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALPROJECT_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

	DECLARE_EVENT_OneParam(UActorComponent,FMissionObjectUsed,bool)
	FMissionObjectUsed OnMissionObjectUsed;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TMap<EConsumableItemType, int> ConsumablesInventory;
	UPROPERTY()
	TMap<EMissionObjectItemType, int> MissionObjectsInventory;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void UseConsumableItem(EConsumableItemType ConsumableType, int ItemCount);

	UFUNCTION()
    void UseMissionObjectItem(EMissionObjectItemType MissionObjectType, int ItemCount, bool bShouldBeLost);

	UFUNCTION()
	void AddConsumableItem(EConsumableItemType ConsumableType, int ItemCount);

	UFUNCTION()
    void AddMissionObjectItem(EMissionObjectItemType MissionObjectType, int ItemCount);

	UFUNCTION()
    bool IsMissionObjectInInventory(EMissionObjectItemType MissionObjectType, int ItemCount);
};
