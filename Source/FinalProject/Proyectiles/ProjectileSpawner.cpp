// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpawner.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileSpawner::AProjectileSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	SpawnerComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnerComponent"));
	SpawnerComponent->SetupAttachment(Root);

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Projectile Spawner Created"));
}


void AProjectileSpawner::SetShootDirection(const FVector& Direction)
{
	ShootDirection = Direction;
	NormalizedShootDirection = ShootDirection.GetSafeNormal();
}

// Called when the game starts or when spawned
void AProjectileSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	NormalizedShootDirection = ShootDirection.GetSafeNormal();

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Projectile Spawner Created"));
}

// Called every frame
void AProjectileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileSpawner::SpawnProjectile()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Spawn Projectile Called"));
	if (ProjectileBP)
	{
		FActorSpawnParameters SpawnParams;

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, SpawnerComponent->GetComponentTransform(), SpawnParams);
		Projectile->ProjectileMovementComponent->InitialSpeed = InitialSpeed;
		Projectile->FireInDirection(NormalizedShootDirection);
	}
}
