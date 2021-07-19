// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Activable.h"
#include "ActivableActor.generated.h"


class UAnimationBaseComponent;

UCLASS()
class FINALPROJECT_API AActivableActor : public AActor, public IActivable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActivableActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RootComponent")
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString ActivationHint = "Activate";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString DeactivationHint = "Deactivate";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString ActivableActorName;

    void Activated_Implementation() override;

    void Deactivated_Implementation() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Interactable Interface
	void Interacted_Implementation(AActor* OtherActor) override;
	
	/** Interaction hint to show on UI*/
	FORCEINLINE FString InteractionHint_Implementation() const override;

	/** Name of the object to be interacted with, show on UI*/
	FORCEINLINE FString InteractableObjectName_Implementation() const  override { return ActivableActorName; }

	//Activable Interface
	FORCEINLINE  EActivableState GetState_Implementation() const override { return State; };

	FORCEINLINE UStaticMeshComponent*  ActivableMeshComponent_Implementation() override{ return Mesh; }

	/** this function return true if the Activable Actor is on an activation transition*/
	FORCEINLINE bool IsTransitionAnimationPlaying_Implementation() const { return bInTransition; }

	/** Set the the transition state of the activable actor*/
	FORCEINLINE void SetTransitionAnimationState_Implementation(bool bAnimationPlaying) { bInTransition = bAnimationPlaying; }

	DECLARE_DERIVED_EVENT(AActivableActor,IActivable::FActivableStateChangedEvent,FActivableStateChangedEvent)
	FORCEINLINE virtual FActivableStateChangedEvent& OnActivableStateChanged() override { return ActivableStateChangedEvent; }
private:
	EActivableState State = EActivableState::Deactivated;
	bool bInTransition = false;
	FActivableStateChangedEvent ActivableStateChangedEvent;

	/*Find is the interactable object has any animation component*/
	//UPROPERTY() 
	TInlineComponentArray<UAnimationBaseComponent*> AnimationComponents;
};
