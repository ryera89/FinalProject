// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Activable.h"
#include "../Interfaces/Animable.h"
#include "PressureTrigger.generated.h"


class IAnimation;

UCLASS()
class FINALPROJECT_API APressureTrigger : public AActor, public IActivable, public IAnimable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressureTrigger();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RootComponent")
	USceneComponent* Root;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//************************Protected Activable Interface*****************************
    void Activated_Implementation() override;

    void Deactivated_Implementation() override;

	void ChangeState_Implementation() override;
	//*********************************************************************************

	/*Function to handle the correct rearmed of the pressure trigger*/
	UFUNCTION()
	void RearmTrigger();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//****************************Activable Interface**********************************************
	FORCEINLINE  EActivableState GetState_Implementation() const override { return State; };

	//DECLARE_DERIVED_EVENT(APressureTrigger,IActivable::FActivableStateChangedEvent,FActivableStateChangedEvent)
	//FORCEINLINE virtual FActivableStateChangedEvent& OnActivableStateChanged() override { return ActivableStateChangedEvent; }

	DECLARE_DERIVED_EVENT(APressureTrigger,IActivable::FActivatedEvent,FActivatedEvent)
	FORCEINLINE  virtual FActivatedEvent& OnActivated() { return OnActivatedEvent; }

	DECLARE_DERIVED_EVENT(APressureTrigger,IActivable::FDeactivatedEvent,FDeactivatedEvent)
	FORCEINLINE virtual FDeactivatedEvent& OnDeactivated() { return OnDeactivatedEvent; }

	//***************************Animable Interface***********************************************
	bool IsAnimationPlaying_Implementation() const;

	/** Array of USceneComponent that will display a animation or some kind of visual effect*/
	FORCEINLINE virtual const TArray<USceneComponent*>&  GetAnimableSceneComponents() const override{ return AnimableComponents;}

	//*********************************************************************************************

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
	EActivableState State = EActivableState::Deactivated;
	/*Broadcast event when the activable state change*/
	//FActivableStateChangedEvent ActivableStateChangedEvent;

	FActivatedEvent OnActivatedEvent;

	FDeactivatedEvent OnDeactivatedEvent;
	//Array of Meshes that should display some kind of animation or effect on activation or deactivation.
	TArray<USceneComponent*> AnimableComponents;
	//Pointer to the Animation to execute on activation and deactivation
	IAnimation* Animation;
};
