// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileLauncher.generated.h"

class UChildActorComponent;
class IActivable;
UCLASS()
class FINALPROJECT_API AProjectileLauncher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileLauncher();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RootComponent")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSpawnerActor")
	UChildActorComponent* ProjectileSpawner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TriggerEvent")
	TScriptInterface<class IActivable> TriggerEventSource;

	/*Initial speed of the projectile*/
	UPROPERTY(EditAnywhere, Category = "ProjectileInitialProperties")
	float InitialSpeed = 1000.0f;

	/*Shoot projectile direction*/
	UPROPERTY(EditAnywhere, Category = "ProjectileInitialProperties")
	FVector ShootDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
