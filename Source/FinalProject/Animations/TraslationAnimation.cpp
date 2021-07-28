// Fill out your copyright notice in the Description page of Project Settings.


#include "TraslationAnimation.h"
#include "../Interfaces/Animable.h"

// Sets default values for this component's properties
UTraslationAnimation::UTraslationAnimation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTraslationAnimation::BeginPlay()
{
	Super::BeginPlay();

	AnimableActor = GetOwner<IAnimable>();

	if (CurveVector != nullptr)
	{
		//Execute AnimationEnded function when animation ends
		OnTimelineEnd.BindUFunction(this, FName("AnimationEnded"));
		CurveVTimeline.SetTimelineFinishedFunc(OnTimelineEnd);

		FOnTimelineVector TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveVTimeline.AddInterpVector(CurveVector, TimelineProgress);
	}
	
}


inline void UTraslationAnimation::AnimationEnded_Implementation() 
{ 
	AnimationEndedEvent.Broadcast();
    bIsPlaying = false;
}

// Called every frame
void UTraslationAnimation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurveVTimeline.TickTimeline(DeltaTime);	
}

void UTraslationAnimation::SetStartingPropertiesValues_Implementation(const TArray<USceneComponent*>& AnimableComponents)
{
	//Clears previus set values
	StartPositions.Empty();
	EndPositions.Empty();
	for (USceneComponent* component : AnimableComponents)
		{
			FVector StartPos = component->GetRelativeLocation();
			FVector EndPos = StartPos + PositionOffset;
			StartPositions.Emplace(StartPos);
			EndPositions.Emplace(EndPos);
		}
}
void UTraslationAnimation::Play_Implementation()
{
	bIsPlaying = true;
	CurveVTimeline.Play();
}

void UTraslationAnimation::PlayFromStart_Implementation()
{
	bIsPlaying = true;
	CurveVTimeline.PlayFromStart();
}

void UTraslationAnimation::Reverse_Implementation()
{
	bIsPlaying = true;
	CurveVTimeline.Reverse();
}

void UTraslationAnimation::ReverseFromEnd_Implementation()
{
	bIsPlaying = true;
	CurveVTimeline.ReverseFromEnd();
}
void UTraslationAnimation::Stop_Implementation()
{
	bIsPlaying = false;
	CurveVTimeline.Stop();
}

void UTraslationAnimation::TimelineProgress(float alpha)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green,
	//	FString::Printf(TEXT("Animable Bar Meshes %i"),AnimableActor->GetAnimableSceneComponents().Num()));
	for (int i = 0; i < AnimableActor->GetAnimableSceneComponents().Num(); ++i)
	{
		FVector NewPosition = FMath::Lerp(StartPositions[i], EndPositions[i], alpha);
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("NewPosition (X = %f, Y = %f, Z = %f)"),NewPosition.X,NewPosition.Y,NewPosition.Z));
		AnimableActor->GetAnimableSceneComponents()[i]->SetRelativeLocation(NewPosition);
	}
}
