// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Proyectile.h"
#include "ExplosiveProjectile.generated.h"

class UParticleSystemComponent;

/**
 * Class for projectiles that self destroy on impact and have a limited life time.
 */
UCLASS()
class FINALPROJECT_API AExplosiveProjectile : public AProjectile
{
	GENERATED_BODY()
	
public:
	AExplosiveProjectile();

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	UParticleSystemComponent* FlyingParticleComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
