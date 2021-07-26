// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Animable.generated.h"

class USceneComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FINALPROJECT_API IAnimable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animable")
	bool IsAnimationPlaying() const;

	/** Array of USceneComponent that will display a animation or some kind of visual effect*/
	virtual const TArray<USceneComponent*>& GetAnimableSceneComponents() const = 0;
};
