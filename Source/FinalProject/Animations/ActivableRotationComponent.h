// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
#include "AnimationBaseComponent.h"
#include "Components/TimelineComponent.h"
#include "ActivableRotationComponent.generated.h"

class IActivable;
class UCurveVector;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALPROJECT_API UActivableRotationComponent : public UAnimationBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActivableRotationComponent();

	UFUNCTION()
	void TimelineProgress(float alpha);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimeline CurveVTimeline;

	FOnTimelineEventStatic OnTimelineEnd;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveVector* CurveVector;

	UPROPERTY()
	FRotator StartRotator;

	UPROPERTY()
	FRotator EndRotator;

	/* How much rotate*/
	UPROPERTY(EditAnywhere, Category = "Timeline")
	FRotator RotationOffset;

	UFUNCTION()
	void AnimationEnded();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/*The parent of this animation should implement the Activable interface for this be able to play*/
	IActivable* Parent;
};
