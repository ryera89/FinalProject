// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Proyectile.h"
#include "ProjectileSpawner.generated.h"

UCLASS()
class FINALPROJECT_API AProjectileSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileSpawner();

	UPROPERTY(BlueprintReadOnly, Category = "RootComponent")
	USceneComponent* Root;

	/*For getting the projectile spawn world transform*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpawnerComponents")
	USceneComponent* SpawnerComponent;

	/*Blueprint reference of AProjectile class*/
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileSpawning")
	TSubclassOf<AProjectile> ProjectileBP;

	/*Initial speed of the projectile*/
	UPROPERTY(EditAnywhere, Category = "ProjectileInitialProperties")
	float InitialSpeed = 1000.0f;

	UFUNCTION(BlueprintCallable, Category = "ProjectileShootDirection")
	void SetShootDirection(const FVector& Direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Shoot projectile direction*/
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileInitialProperties")
	FVector ShootDirection;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SpawnProjectile();

private:
	//Normalized projectile shoot direction.
	FVector NormalizedShootDirection;
};
