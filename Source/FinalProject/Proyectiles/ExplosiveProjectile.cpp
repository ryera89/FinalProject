// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveProjectile.h"
#include "Particles/ParticleSystemComponent.h"

AExplosiveProjectile::AExplosiveProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

    FlyingParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FlyingParticlesComponent"));
	FlyingParticleComponent->SetupAttachment(RootComponent);
}

void AExplosiveProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AExplosiveProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
