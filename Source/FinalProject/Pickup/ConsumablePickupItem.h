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

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	//UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString InteractionHint = "Pickup";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString ItemName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interacted_Implementation(AActor* OtherActor) override;

	FORCEINLINE FString IntractionHint_Implementation() const override { return InteractionHint; }

	FORCEINLINE FString InteractableObjectName_Implementation() const  override { return ItemName; }

	FORCEINLINE EPickableItemType ItemType_Implementation() override { return EPickableItemType::Consumable; }
};
