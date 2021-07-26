// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationAnimation.h"
#include "../Interfaces/Animable.h"

// Sets default values for this component's properties
URotationAnimation::URotationAnimation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotationAnimation::BeginPlay()
{
	Super::BeginPlay();

	AnimableActor = GetOwner<IAnimable>();

	if (CurveVector != nullptr)
	{
		//Execute AnimationEnded function when animation ends
		OnTimelineEnd.BindUFunction(this, FName("AnimationEnded"));
		CurveVTimeline.SetTimelineFinishedFunc(OnTimelineEnd);

		//Parent->OnActivableStateChanged().AddUObject(this, &UActivableRotationComponent::PlayAnimation);

		FOnTimelineVector TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveVTimeline.AddInterpVector(CurveVector, TimelineProgress);
	}
	
}


// Called every frame
void URotationAnimation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurveVTimeline.TickTimeline(DeltaTime);	
}

void URotationAnimation::SetStartingPropertiesValues_Implementation(const TArray<USceneComponent*>& AnimableComponents)
{
	//Clears previus set values
	StartRotators.Empty();
	EndRotators.Empty();
	for (USceneComponent* component : AnimableComponents)
		{
			FRotator StartR = component->GetRelativeRotation();
			FRotator EndR = StartR + RotationOffset;
			StartRotators.Emplace(StartR);
			EndRotators.Emplace(EndR);
		}
}

void URotationAnimation::Play_Implementation()
{
	bIsPlaying = true;
	CurveVTimeline.Play();
}

void URotationAnimation::PlayFromStart_Implementation()
{
	bIsPlaying = true;
	CurveVTimeline.PlayFromStart();
}

void URotationAnimation::Reverse_Implementation()
{
	bIsPlaying = true;
	CurveVTimeline.Reverse();
}

void URotationAnimation::ReverseFromEnd_Implementation()
{
	bIsPlaying = true;
	CurveVTimeline.ReverseFromEnd();
}

void URotationAnimation::TimelineProgress(float alpha)
{
	for (int i = 0; i < StartRotators.Num(); ++i)
	{
		FRotator NewRotator = FMath::Lerp(StartRotators[i], EndRotators[i], alpha);
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("NewRotator (alpha = %f), (Pitch = %f, Yaw = %f, Roll = %f)"),alpha,NewRotator.Pitch,NewRotator.Yaw,NewRotator.Roll));
		AnimableActor->GetAnimableSceneComponents()[i]->SetRelativeRotation(NewRotator);
	}
}



