// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Interactable.h"
#include "../Interfaces/Activable.h"
#include "../Interfaces/Animable.h"
#include "CharacterActivableActor.generated.h"


class IAnimation;

/*Base class for actors that are interactable by the character and activables (ie levers, switchs etc)*/
UCLASS()
class FINALPROJECT_API ACharacterActivableActor : public AActor, public IInteractable, public IActivable,public IAnimable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterActivableActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RootComponent")
	USceneComponent* Root;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString ActivationHint = "Activate";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString DeactivationHint = "Deactivate";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString ActivableActorName;

	/*Trigger for activation or deactivation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TriggerEvent")
	TScriptInterface<class IInteractable> TriggerEventSource;

	//*******************Protected Activable Interface***********************
    void Activated_Implementation() override;

    void Deactivated_Implementation() override;

	void ChangeState_Implementation() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//*********************Interactable Interface********************
	void Interacted_Implementation(AActor* OtherActor) override;
	
	/** Interaction hint to show on UI*/
	FString InteractionHint_Implementation() const override;

	/** Name of the object to be interacted with, show on UI*/
	FORCEINLINE FString InteractableObjectName_Implementation() const  override { return ActivableActorName; }

	DECLARE_DERIVED_EVENT(ACharacterActivableActor,IInteractable::FInteractedEvent,FInteractedEvent)
	FORCEINLINE virtual FInteractedEvent& OnInteracted() override { return InteractedEvent; }

	//*********************Activable Interface************************
	FORCEINLINE  EActivableState GetState_Implementation() const override { return State; };

	DECLARE_DERIVED_EVENT(ACharacterActivableActor,IActivable::FActivableStateChangedEvent,FActivableStateChangedEvent)
	FORCEINLINE virtual FActivableStateChangedEvent& OnActivableStateChanged() override { return ActivableStateChangedEvent; }

	//********************Animable Interface****************************
	bool IsAnimationPlaying_Implementation() const override;

	/** Array of USceneComponent that will display a animation or some kind of visual effect*/
	FORCEINLINE virtual const TArray<USceneComponent*>&  GetAnimableSceneComponents() const override{ return AnimableComponents;}

private:
	EActivableState State = EActivableState::Deactivated;
	/*Broadcast event when the activable state change*/
	FActivableStateChangedEvent ActivableStateChangedEvent;
	/*Broadcast event when interacted event happen*/
	FInteractedEvent InteractedEvent;
	//Array of Meshes that should display some kind of animation or effect on activation or deactivation.
	TArray<USceneComponent*> AnimableComponents;
	//Pointer to the Animation to execute on activation and deactivation
	IAnimation* Animation;
};
