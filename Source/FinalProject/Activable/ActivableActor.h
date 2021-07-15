// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Activable.h"
#include "ActivableActor.generated.h"


DECLARE_EVENT_OneParam(AActivableActor,FOnActivatedStateChanged,bool)

UCLASS()
class FINALPROJECT_API AActivableActor : public AActor, public IActivable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActivableActor();

	FOnActivatedStateChanged OnActivatedStateChanged;
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
	
	//Interactable Interface
	void Interacted_Implementation(AActor* OtherActor) override;
	
	/** Interaction hint to show on UI*/
	FORCEINLINE FString InteractionHint_Implementation() const override { return InteractionHint; }

	/** Name of the object to be interacted with, show on UI*/
	FORCEINLINE FString InteractableObjectName_Implementation() const  override { return ItemName; }

	//Activable Interface
	FORCEINLINE  bool IsActive_Implementation() const override { return bIsActive; };

    void Activated_Implementation() override;

    void Deactivated_Implementation() override;

private:
	bool bIsActive = false;
};
