// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Interfaces/Animation.h"
#include "Components/TimelineComponent.h"
#include "TraslationAnimation.generated.h"

class IAnimable;
class UCurveVector;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALPROJECT_API UTraslationAnimation : public UActorComponent, public IAnimation
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTraslationAnimation();

	/* How much traslate */
	UPROPERTY(EditAnywhere, Category = "Animation|Offset")
	FVector PositionOffset;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimeline CurveVTimeline;

	FOnTimelineEventStatic OnTimelineEnd;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveVector* CurveVector;

	//***********************Animation Protected Interface***************************
	/*This function will be called when the timeline ends*/
	void AnimationEnded_Implementation() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/***********************Animation Iterface************************/
	/*Set the starting values of the properties target of the animation*/
	void SetStartingPropertiesValues_Implementation(const TArray<USceneComponent*>& AnimableComponents) override;

	/*Play the animation the target are the AnimableMeshes*/
	void Play_Implementation() override;

	/*Play the animation the target are the AnimableMeshes from start*/
	void PlayFromStart_Implementation() override;

	/*Play on reverse the animation the target are the AnimableMeshes*/
	void Reverse_Implementation() override;

	/*Play on reverse the animation the target are the AnimableMeshes statring form the end*/
	void ReverseFromEnd_Implementation() override;

	/*Stop the animation*/
	void Stop_Implementation() override;

	/*Return true if the animation is playing, false otherwise*/
	FORCEINLINE bool IsPlaying_Implementation() const override { return bIsPlaying; }

	DECLARE_DERIVED_EVENT(UTraslationAnimation,IAnimation::FAnimationEndedEvent,FAnimationEndedEvent)
	FORCEINLINE virtual FAnimationEndedEvent& OnAnimationEnded() override { return AnimationEndedEvent; }
	/****************************************************************/
	
	UFUNCTION()
	void TimelineProgress(float alpha);

private:
	bool bIsPlaying = false;
	/*Start and End Positions of the animable meshes*/
	TArray<FVector> StartPositions;
	TArray<FVector> EndPositions;
	/*Event braodcasted when animation ends*/
	FAnimationEndedEvent AnimationEndedEvent;
	/*Pointer to the animable interface implementation of the owner actor*/
	IAnimable* AnimableActor;

		
};
