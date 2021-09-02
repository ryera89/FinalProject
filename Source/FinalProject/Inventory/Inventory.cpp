// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "../UI/InGameHUD.h"
#include "../FinalProjectCharacter.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventory::UseConsumableItem(EConsumableItemType ConsumableType, int ItemCount)
{
	int* pItem = ConsumablesInventory.Find(ConsumableType);
	
	if (pItem != nullptr && ItemCount <= *pItem)
	{
		*pItem = *pItem - ItemCount;	

		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Consumable Object Removed from Inventory"));
	}
		//Emit a signal that the item was consumed
	
}

void UInventory::UseMissionObjectItem(EMissionObjectItemType MissionObjectType, int ItemCount, bool bShouldBeLost)
{
	int* pItem = MissionObjectsInventory.Find(MissionObjectType);
	if (pItem != nullptr && ItemCount <= *pItem)
	{
		if (bShouldBeLost)
		{
			 *pItem = *pItem - ItemCount;	
		}
	    GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Mission Object Removed from Inventory"));
	    OnMissionObjectUsed.Broadcast(true);

		AFinalProjectCharacter* Character = GetOwner<AFinalProjectCharacter>();
		if (Character != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			if (AInGameHUD* HUD = Cast<AInGameHUD>(PlayerController->GetHUD()))
			{
				HUD->SetQuestHint("Quest: Walk throw the mist");
			}
		}
	}
	else
	{
		OnMissionObjectUsed.Broadcast(false);
	}
}

void UInventory::AddConsumableItem(EConsumableItemType ConsumableType, int ItemCount)
{
	int& pItem = ConsumablesInventory.FindOrAdd(ConsumableType);
	pItem += ItemCount;
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Consumable Object Added to Inventory"));
	//ConsumablesInventory[ConsumableType] += number;
}

void UInventory::AddMissionObjectItem(EMissionObjectItemType MissionObjectType, int ItemCount)
{
	int& pItem = MissionObjectsInventory.FindOrAdd(MissionObjectType);
	pItem += ItemCount;
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Mission Object Added  to Inventory"));
	//MissionObjectsInventory[MissionObjectType] += number;
	/*Este codigo no debe ir aca el sistema de misiones tiene que ser otro asi q esto es temporal*/
	if (MissionObjectType == EMissionObjectItemType::SunSpear)
	{
		AFinalProjectCharacter* Character = GetOwner<AFinalProjectCharacter>();
		if (Character != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			if (AInGameHUD* HUD = Cast<AInGameHUD>(PlayerController->GetHUD()))
			{
				HUD->SetQuestHint("Quest: Activate the pilar with the Sun Spear and open the Golden Gate");
			}
		}
		
	}
}

bool UInventory::IsMissionObjectInInventory(EMissionObjectItemType MissionObjectType, int ItemCount)
{
	int* pItem = MissionObjectsInventory.Find(MissionObjectType);
	if (pItem != nullptr && *pItem >= ItemCount)
	{
		return true;
	}
	return false;
}


