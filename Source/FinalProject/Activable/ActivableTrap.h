// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Activable.h"
#include "../Interfaces/Animable.h"
#include "ActivableTrap.generated.h"

class UBoxComponent;
class IAnimation;

UCLASS()
class FINALPROJECT_API AActivableTrap : public AActor, public IActivable, public IAnimable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActivableTrap();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RootComponent")
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionComponent")
	UBoxComponent* CollisionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TriggerEvent")
	TScriptInterface<IActivable> TriggerEventSource;

	/*Damage applied to actors hitted by the trap*/
	UPROPERTY(EditAnywhere, Category = "Trap")
	float Damage = 100;

	//************************Protected Activable Interface*****************************
    void Activated_Implementation() override;

    void Deactivated_Implementation() override;

	void ChangeState_Implementation() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//****************************Activable Interface**********************************************
	FORCEINLINE  EActivableState GetState_Implementation() const override { return State; };

	DECLARE_DERIVED_EVENT(AActivableActor,IActivable::FActivatedEvent,FActivatedEvent)
	FORCEINLINE  virtual FActivatedEvent& OnActivated() { return OnActivatedEvent; }

	DECLARE_DERIVED_EVENT(AActivableActor,IActivable::FDeactivatedEvent,FDeactivatedEvent)
	FORCEINLINE virtual FDeactivatedEvent& OnDeactivated() { return OnDeactivatedEvent; }

	//***************************Animable Interface***********************************************
	bool IsAnimationPlaying_Implementation() const;

	/** Array of USceneComponent that will display a animation or some kind of visual effect*/
	FORCEINLINE virtual const TArray<USceneComponent*>&  GetAnimableSceneComponents() const override{ return AnimableComponents;}

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse, const FHitResult& Hit);
private:
	EActivableState State = EActivableState::Deactivated;
	/*Broadcast events when the activable state change*/
	FActivatedEvent OnActivatedEvent;
	FDeactivatedEvent OnDeactivatedEvent;
	//Array of Meshes that should display some kind of animation or effect on activation or deactivation.
	TArray<USceneComponent*> AnimableComponents;
	//Pointer to the Animation to execute on activation and deactivation
	IAnimation* Animation;
};
