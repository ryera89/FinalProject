// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Pickable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickable : public UInteractable
{
	GENERATED_BODY()
};

/**
 * 
 */
class FINALPROJECT_API IPickable : public IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
