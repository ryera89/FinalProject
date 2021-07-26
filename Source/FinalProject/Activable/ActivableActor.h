// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Activable.h"
#include "../Interfaces/Animable.h"
#include "ActivableActor.generated.h"


class IAnimation;

UCLASS()
class FINALPROJECT_API AActivableActor : public AActor, public IActivable, public IAnimable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActivableActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RootComponent")
	USceneComponent* Root;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	//UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString ActivationHint = "Activate";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString DeactivationHint = "Deactivate";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pickup|UIHint")
	FString ActivableActorName;

	//************************Protected Activable Interface*****************************
    void Activated_Implementation() override;

    void Deactivated_Implementation() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//****************************Activable Interface**********************************************
	FORCEINLINE  EActivableState GetState_Implementation() const override { return State; };

	DECLARE_DERIVED_EVENT(AActivableActor,IActivable::FActivableStateChangedEvent,FActivableStateChangedEvent)
	FORCEINLINE virtual FActivableStateChangedEvent& OnActivableStateChanged() override { return ActivableStateChangedEvent; }

	//***************************Animable Interface***********************************************
	bool IsAnimationPlaying_Implementation() const;

	/** Array of USceneComponent that will display a animation or some kind of visual effect*/
	FORCEINLINE virtual const TArray<USceneComponent*>&  GetAnimableSceneComponents() const override{ return AnimableComponents;}
private:
	EActivableState State = EActivableState::Deactivated;
	/*Broadcast event when the activable state change*/
	FActivableStateChangedEvent ActivableStateChangedEvent;
	//Array of Meshes that should display some kind of animation or effect on activation or deactivation.
	TArray<USceneComponent*> AnimableComponents;
	//Pointer to the Animation to execute on activation and deactivation
	IAnimation* Animation;
};
