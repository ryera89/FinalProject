// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

AExplosiveProjectile::AExplosiveProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

    FlyingParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FlyingParticlesComponent"));
	FlyingParticleComponent->SetupAttachment(RootComponent);
	
	MovingProjectile = CreateDefaultSubobject<UParticleSystem>(TEXT("MovingProjectileParticles"));

	ImpactParticle = CreateDefaultSubobject<UParticleSystem>(TEXT("ImpactParticleParticles"));

	CollisionComponent->OnComponentHit.AddDynamic(this, &AExplosiveProjectile::OnHit);
}

void AExplosiveProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (FlyingParticleComponent != nullptr && MovingProjectile != nullptr)
	{
		FlyingParticleComponent->SetTemplate(MovingProjectile);
	}
}

void AExplosiveProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AExplosiveProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector EmitterLocationOffSet = FVector(0.0f, 0.0f, 20.0f);
	//FRotator EmiterRotator = FRotator(0.0f, 0.0f, 0.0f);
	FVector EmitterLocation = Hit.Location + EmitterLocationOffSet;

	++HitEventTriggeredTimes;

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("Hit event times called = %i"),HitEventTriggeredTimes));
	if (OtherActor != this)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Collision If Statemenet true"));
		//Spaw a particle emitter at location (explosion effect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, EmitterLocation);
		
		//Damage the Hited actor
		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(50, DamageEvent, nullptr, this);

		//Deactivate the flying particle effect
		FlyingParticleComponent->Deactivate();

		//No second hit event emited.
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		GetWorld()->GetTimerManager().SetTimer(timer, this, &AExplosiveProjectile::DestroyExplosiveProjectile, AfterHitDestroyDelayTime);
	}
}

void AExplosiveProjectile::DestroyExplosiveProjectile()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Projectile Destroyed"));
	Destroy();
}
