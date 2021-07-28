// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Animation.generated.h"

class UMeshComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimation : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FINALPROJECT_API IAnimation
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/*Set the starting values of the properties target of the animation*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")
	void SetStartingPropertiesValues(const TArray<USceneComponent*>& AnimableComponents);

	/*Play the animation the target are the AnimableMeshes*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")
	void Play();

	/*Play the animation the target are the AnimableMeshes from start*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")
	void PlayFromStart();

	/*Play on reverse the animation the target are the AnimableMeshes*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")
	void Reverse();

	/*Play on reverse the animation the target are the AnimableMeshes statring form the end*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")
	void ReverseFromEnd();

	/*Stop the animation*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")
	void Stop();

	/*Return true if the animation is playing, false otherwise*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")
	bool IsPlaying() const;

	DECLARE_EVENT(IAnimation,FAnimationEndedEvent)
	virtual FAnimationEndedEvent& OnAnimationEnded() = 0;

protected:
	/*This function will be called when the animation ends*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")
	void AnimationEnded();
};
