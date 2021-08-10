// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileLauncher.h"
#include "Components/ChildActorComponent.h"
#include "../Interfaces/Activable.h"
#include "ProjectileSpawner.h"

// Sets default values
AProjectileLauncher::AProjectileLauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	ProjectileSpawner = CreateDefaultSubobject<UChildActorComponent>(TEXT("ProjectileSpawner"));
	ProjectileSpawner->SetChildActorClass(AProjectileSpawner::StaticClass());
	ProjectileSpawner->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AProjectileLauncher::BeginPlay()
{
	Super::BeginPlay();
	
	if (TriggerEventSource)
	{
		AProjectileSpawner* Spawner = Cast<AProjectileSpawner>(ProjectileSpawner->GetChildActor());
		if (Spawner)
		{
			Spawner->InitialSpeed = InitialSpeed;
			Spawner->SetShootDirection(ShootDirection);
			TriggerEventSource->OnActivated().AddUObject(Spawner, &AProjectileSpawner::SpawnProjectile);
		}
		
	}
}

// Called every frame
void AProjectileLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

