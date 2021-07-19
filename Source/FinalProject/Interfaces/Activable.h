// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
//#include "Components/MeshComponent.h"
#include "Activable.generated.h"

UENUM()
enum class EActivableState
{
	Activated,
	Deactivated,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActivable : public UInteractable
{
	GENERATED_BODY()
};


/**
 * Interface class for Activable Actors activable actors has two states activated and deactivated
 */
class FINALPROJECT_API IActivable : public IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
	EActivableState GetState() const;

	/** this function return true if the Activable Actor is on an activation transition*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
	bool IsTransitionAnimationPlaying() const;

	/** Set the the transition state of the activable actor*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
	void SetTransitionAnimationState(bool bAnimationPlaying);

	/** UMeshComponent that will display a animation or some kind of visual effect on activation and deactivation */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
	UMeshComponent* ActivableMeshComponent();

	DECLARE_EVENT_OneParam(IActivable,FActivableStateChangedEvent,EActivableState)
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
	virtual FActivableStateChangedEvent& OnActivableStateChanged() = 0;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
    void Activated();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
    void Deactivated();
};
