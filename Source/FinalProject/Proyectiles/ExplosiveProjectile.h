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

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	UParticleSystem* MovingProjectile;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	UParticleSystem* ImpactParticle;

	/*Damage applied to actors hitted by the trap*/
	UPROPERTY(EditAnywhere, Category = "Trap")
	float Damage = 50;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Delay time in seconds for destroy the projectile after Hit event*/
	UPROPERTY(EditDefaultsOnly, Category = "Projectile ")
	float AfterHitDestroyDelayTime = 2.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Function to to handle whats happen when the Hit Event is fired.
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse, const FHitResult& Hit);
private:
	//timer for delay destruction of the projectile after hit event
	FTimerHandle timer;

	//Proxy function to call the Actor::Destroy() method 
	UFUNCTION()
	void DestroyExplosiveProjectile();

	int HitEventTriggeredTimes = 0;
};
