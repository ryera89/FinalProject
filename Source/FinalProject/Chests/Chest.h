// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Interactable.h"
#include "../Interfaces/Animable.h"
#include "../Pickup/ConsumablePickupItem.h"
#include "Chest.generated.h"

class IAnimation;
class UBoxComponent;
class UParticleSystemComponent;

UCLASS()
class FINALPROJECT_API AChest : public AActor, public IInteractable, public IAnimable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RootComponent")
	USceneComponent* Root;

	/*Component who detect overlaps events*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision Component")
	UBoxComponent* CollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpawnerComponents")
	USceneComponent* SpawnerComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	UParticleSystemComponent* TreassureParticleComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString ActivableActorName = "Chest";

	/*Proxy function to activate the treassure particle system*/
	UFUNCTION()
	void ActivateParticleSystem();

	UFUNCTION()
	void SpawnPickupItem();

	/*Blueprint reference of AProjectile class*/
	UPROPERTY(EditDefaultsOnly, Category = "PickupSpawning")
	TSubclassOf<AConsumablePickupItem> Pickup_BP;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//*********************Interactable Interface********************
	void Interacted_Implementation(AActor* OtherActor) override;
	
	/** Interaction hint to show on UI*/
	FORCEINLINE FString InteractionHint_Implementation() const override { return "Open"; }

	/** Name of the object to be interacted with, show on UI*/
	FORCEINLINE FString InteractableObjectName_Implementation() const  override { return ActivableActorName; }

	DECLARE_DERIVED_EVENT(ACharacterActivableActor,IInteractable::FInteractedEvent,FInteractedEvent)
	FORCEINLINE virtual FInteractedEvent& OnInteracted() override { return InteractedEvent; }

	//********************Animable Interface****************************
	bool IsAnimationPlaying_Implementation() const override;

	/** Array of USceneComponent that will display a animation or some kind of visual effect*/
	FORCEINLINE virtual const TArray<USceneComponent*>&  GetAnimableSceneComponents() const override{ return AnimableComponents;}
private:
	/*Broadcast event when interacted event happen*/
	FInteractedEvent InteractedEvent;
	//Array of Meshes that should display some kind of animation or effect on activation or deactivation.
	TArray<USceneComponent*> AnimableComponents;
	//Pointer to the Animation to execute on activation and deactivation
	IAnimation* Animation;
};
