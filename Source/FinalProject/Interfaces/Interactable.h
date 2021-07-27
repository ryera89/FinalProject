// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FINALPROJECT_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/** Active the event to happen when the actor who implement this interface is interacted by other actor
	* @param OtherActor - Actor who interact
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interacted(AActor* OtherActor);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void FocusStart();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void FocusEnd();

	/** Interaction hint to show on UI*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FString InteractionHint() const;

	/** Name of the object to be interacted with, show on UI*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FString InteractableObjectName() const;

	DECLARE_EVENT(IInteractable,FInteractedEvent)
	virtual FInteractedEvent& OnInteracted() = 0;
};
