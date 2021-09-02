// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Interactable.h"
#include "../Interfaces/Activable.h"
#include "../Interfaces/Animable.h"
#include "../Inventory/Inventory.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionComponent")
	class UBoxComponent* CollisionBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Activable|UIHint")
	FString ActivationHint = "Activate";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Activable|UIHint")
	FString DeactivationHint = "Deactivate";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Activable|UIHint")
	FString ActivableActorName;

	/*Trigger for activation or deactivation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TriggerEvent")
	TScriptInterface<class IInteractable> TriggerEventSource;

	/*Set if the interactable object requieres that the player carried an item*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	bool bIsItemRequiredForIteration = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	EMissionObjectItemType ItemRequiredForIteraction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	FString ItemRequiredName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	bool bOneTimeInteractable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	float GameMessageTime = 3.f;

	//*******************Protected Activable Interface***********************
    void Activated_Implementation() override;

    void Deactivated_Implementation() override;

	void ChangeState_Implementation() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//virtual bool CanBeBaseForCharacter(APawn* pawn) const override;
	
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

	//DECLARE_DERIVED_EVENT(ACharacterActivableActor,IActivable::FActivableStateChangedEvent,FActivableStateChangedEvent)
	//FORCEINLINE virtual FActivableStateChangedEvent& OnActivableStateChanged() override { return ActivableStateChangedEvent; }

	DECLARE_DERIVED_EVENT(ACharacterActivableActor,IActivable::FActivatedEvent,FActivatedEvent)
	FORCEINLINE  virtual FActivatedEvent& OnActivated() { return OnActivatedEvent; }

	DECLARE_DERIVED_EVENT(ACharacterActivableActor,IActivable::FDeactivatedEvent,FDeactivatedEvent)
	FORCEINLINE virtual FDeactivatedEvent& OnDeactivated() { return OnDeactivatedEvent; }

	//********************Animable Interface****************************
	bool IsAnimationPlaying_Implementation() const override;

	/** Array of USceneComponent that will display a animation or some kind of visual effect*/
	FORCEINLINE virtual const TArray<USceneComponent*>&  GetAnimableSceneComponents() const override{ return AnimableComponents;}

private:
	EActivableState State = EActivableState::Deactivated;
	/*Broadcast event when the activable state change*/
	//FActivableStateChangedEvent ActivableStateChangedEvent;
	FActivatedEvent OnActivatedEvent;
	FDeactivatedEvent OnDeactivatedEvent;
	/*Broadcast event when interacted event happen*/
	FInteractedEvent InteractedEvent;
	//Array of Meshes that should display some kind of animation or effect on activation or deactivation.
	TArray<USceneComponent*> AnimableComponents;
	//Array of Meshes that should become visible.
	TArray<USceneComponent*> VisibleComponents;
	//Pointer to the Animation to execute on activation and deactivation
	IAnimation* Animation;

	void Interact(AActor* OtherActor);
};
