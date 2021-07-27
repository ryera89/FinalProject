// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Activable.generated.h"

UENUM()
enum class EActivableState
{
	Activated,
	Deactivated,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActivable : public UInterface
{
	GENERATED_BODY()
};


/**
 * Interface class for Activable Actors activable actors has two states activated and deactivated
 */
class FINALPROJECT_API IActivable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
	EActivableState GetState() const;

	DECLARE_EVENT_OneParam(IActivable,FActivableStateChangedEvent,EActivableState)
	virtual FActivableStateChangedEvent& OnActivableStateChanged() = 0;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
    void Activated();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
    void Deactivated();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
	void ChangeState();
};
