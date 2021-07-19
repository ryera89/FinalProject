// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
//#include "Components/MeshComponent.h"
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

	/** this function return true if the Activable Actor is on an activation transition*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
	bool IsInTransition() const;

	/** Set the the transition state of the activable actor*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
	void SetTransitionState(bool InTransition);

	/** UMeshComponent that will display a animation or some kind of visual effect on activation and deactivation */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
	UMeshComponent* ActivableMeshComponent();
protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
    void Activated();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activable")
    void Deactivated();

};
