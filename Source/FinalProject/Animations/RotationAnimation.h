// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Interfaces/Animation.h"
#include "Components/TimelineComponent.h"
#include "RotationAnimation.generated.h"


class IAnimable;
class UCurveVector;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALPROJECT_API URotationAnimation : public UActorComponent, public IAnimation

{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotationAnimation();

	/* How much rotate */
	UPROPERTY(EditAnywhere, Category = "Animation|Offset")
	FRotator RotationOffset;

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
	void SetStartingPropertiesValues_Implementation(const TArray<USceneComponent*>& AnimableComponents);

	/*Play the animation the target are the AnimableMeshes*/
	void Play_Implementation();

	/*Play the animation the target are the AnimableMeshes from start*/
	void PlayFromStart_Implementation();

	/*Play on reverse the animation the target are the AnimableMeshes*/
	void Reverse_Implementation();

	/*Play on reverse the animation the target are the AnimableMeshes statring form the end*/
	void ReverseFromEnd_Implementation();

	/*Stop the animation*/
	void Stop_Implementation();

	/*Return true if the animation is playing, false otherwise*/
	FORCEINLINE bool IsPlaying_Implementation() const { return bIsPlaying; }

	DECLARE_DERIVED_EVENT(URotationAnimation,IAnimation::FAnimationEndedEvent,FAnimationEndedEvent)
	FORCEINLINE virtual FAnimationEndedEvent& OnAnimationEnded() override { return AnimationEndedEvent; }
	/****************************************************************/
	
	UFUNCTION()
	void TimelineProgress(float alpha);

private:
	bool bIsPlaying = false;
	/*Start and End Rotators of the animable meshes*/
	TArray<FRotator> StartRotators;
	TArray<FRotator> EndRotators;
	/*Event braodcasted when animation ends*/
	FAnimationEndedEvent AnimationEndedEvent;
	/*Pointer to the animable interface implementation of the owner actor*/
	IAnimable* AnimableActor;
};
