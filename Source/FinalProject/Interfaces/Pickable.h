// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Pickable.generated.h"


/** Pickup item category/types enum (ie consumable, key, weapon etc...)*/
UENUM()
enum class EPickableItemType : uint8
{
	Consumable, //potions, food, etc
	Key,
	Weapon,
	MissionObject,
};



// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickable : public UInteractable
{
	GENERATED_BODY()
};

/**
 * Interfaz class for pickup items
 */
class FINALPROJECT_API IPickable : public IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	//void Interacted(AActor* OtherActor);

	/** Interaction hint to show on UI*/
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	//const FString& IntractionHint();

	/** Name of the object to be interacted with, show on UI*/
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	//const FString& InteractableObjectName();

	/** Item type/category  (ie consumable, key, weapon etc...) */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickup")
	EPickableItemType ItemType() const;

};
