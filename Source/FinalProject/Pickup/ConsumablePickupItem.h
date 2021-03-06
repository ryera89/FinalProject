// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Pickable.h"
#include "ConsumablePickupItem.generated.h"


UCLASS()
class FINALPROJECT_API AConsumablePickupItem : public AActor, public IPickable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConsumablePickupItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RootComponent")
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString InteractionHint = "Pickup";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString ItemName;

	/** Property that hold the type of the consumable*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "ConsumableType")
	EConsumableItemType ConsumableType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interacted_Implementation(AActor* OtherActor) override;

	FORCEINLINE FString InteractionHint_Implementation() const override { return InteractionHint; }

	FORCEINLINE FString InteractableObjectName_Implementation() const  override { return ItemName; }

	DECLARE_DERIVED_EVENT(AConsumablePickupItem,IInteractable::FInteractedEvent,FInteractedEvent)
	FORCEINLINE virtual FInteractedEvent& OnInteracted() override { return InteractedEvent; }

	FORCEINLINE EItemType ItemType_Implementation() const override { return EItemType::Consumable; }

	UFUNCTION(BlueprintCallable, category = "ConsumableType")
	FORCEINLINE EConsumableItemType GetConsumableType() const { return ConsumableType; }

private:
	/*Broadcast event when interacted event happen*/
	FInteractedEvent InteractedEvent;
};
