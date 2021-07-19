// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivableRotationComponent.h"
#include "../Interfaces/Activable.h"

// Sets default values for this component's properties
UActivableRotationComponent::UActivableRotationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UActivableRotationComponent::TimelineProgress(float alpha)
{
	FRotator NewRotator = FMath::Lerp(StartRotator, EndRotator, alpha);
}

void UActivableRotationComponent::AnimationEnded()
{
	//When the animation ends set the parent Transition State
	if (Parent != nullptr) Parent->SetTransitionState_Implementation(false);
}

// Called when the game starts
void UActivableRotationComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//AActor* ParentActor = GetOwner();
	Parent = GetOwner<IActivable>();
	//Parent = Cast<IActivable>(ParentActor);
	
	if (Parent != nullptr && Parent->ActivableMeshComponent_Implementation() != nullptr && CurveVector)
	{
		//Execute AnimationEnded function when animation ends
		OnTimelineEnd.BindUFunction(this, FName("AnimationEnded"));
		CurveVTimeline.SetTimelineFinishedFunc(OnTimelineEnd);

		FOnTimelineVector TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveVTimeline.AddInterpVector(CurveVector, TimelineProgress);

		StartRotator = EndRotator = Parent->ActivableMeshComponent_Implementation()->GetRelativeRotation();
		EndRotator += RotationOffset;
	}
}


// Called every frame
void UActivableRotationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Start Animation and continue until it finishes
	if (Parent != nullptr && Parent->IsInTransition_Implementation())
	{
		//If activated play from start
		if (Parent->IsActive_Implementation())
		{
			CurveVTimeline.PlayFromStart();
			CurveVTimeline.TickTimeline(DeltaTime);
		}
		else
		{
			CurveVTimeline.Reverse();
			CurveVTimeline.TickTimeline(DeltaTime);
		}
	}
}

