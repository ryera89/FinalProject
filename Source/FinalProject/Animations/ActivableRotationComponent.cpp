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
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("NewRotator (alpha = %f), (Pitch = %f, Yaw = %f, Roll = %f)"),alpha,NewRotator.Pitch,NewRotator.Yaw,NewRotator.Roll));
	Parent->ActivableMeshComponent_Implementation()->SetRelativeRotation(NewRotator);
}

void UActivableRotationComponent::AnimationEnded()
{
	//When the animation ends set the owner Transition State
	if (Parent != nullptr) Parent->SetTransitionAnimationState_Implementation(false);
}

void UActivableRotationComponent::PlayAnimation(EActivableState State)
{
	Parent->SetTransitionAnimationState_Implementation(true); //Animation is playing
	switch (State)
	{
	case EActivableState::Activated:
		CurveVTimeline.PlayFromStart();
		break;
	case EActivableState::Deactivated:
		CurveVTimeline.ReverseFromEnd();
		break;
	default:
		break;
	}
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

		Parent->OnActivableStateChanged().AddUObject(this, &UActivableRotationComponent::PlayAnimation);

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
	CurveVTimeline.TickTimeline(DeltaTime);	
}

