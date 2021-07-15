// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Activable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActivable : public UInteractable
{
	GENERATED_BODY()
};

/**
 * 
 */
class FINALPROJECT_API IActivable : public IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
	bool IsActive() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
    void Activated();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
    void Deactivated();

};
