// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "../FinalProjectCharacter.h"
#include "../Interfaces/Animation.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Chest.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionBox->InitBoxExtent(FVector(40, 50, 30));
	CollisionBox->SetupAttachment(Root);

	TreassureParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TreassureParticlesComponent"));
	TreassureParticleComponent->SetupAttachment(Root);

	SpawnerComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnerComponent"));
	SpawnerComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();

	//Get the animable components of the actors actors who inherit from this class
	TInlineComponentArray<USceneComponent*> SceneComponents(this);
	//Get the meshes who has the tag "Animable"
	for (USceneComponent* component : SceneComponents)
	{
		if (component->ComponentHasTag(FName("Animable")))
		{
			AnimableComponents.Add(component);
		}
	}
	TArray<UActorComponent*> AnimArray = GetComponentsByInterface(UAnimation::StaticClass());
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("Animation Components Found %i"),AnimArray.Num()));
	/*Only one Animation component will be used*/
	if (AnimArray.Num()) Animation = Cast<IAnimation>(AnimArray[0]);

	if (Animation != nullptr)
	{
		Animation->SetStartingPropertiesValues_Implementation(AnimableComponents);
		Animation->OnAnimationEnded().AddUObject(this, &AChest::ActivateParticleSystem);
		Animation->OnAnimationEnded().AddUObject(this, &AChest::SpawnPickupItem);
	}
		
	if (TreassureParticleComponent) TreassureParticleComponent->DeactivateSystem();

}

void AChest::ActivateParticleSystem()
{
	TreassureParticleComponent->ActivateSystem();
}

void AChest::SpawnPickupItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Spawn Chest Pick Up"));
	if (Pickup_BP)
	{
		FActorSpawnParameters SpawnParams;

		AConsumablePickupItem* Pickup = GetWorld()->SpawnActor<AConsumablePickupItem>(Pickup_BP, SpawnerComponent->GetComponentTransform(), SpawnParams);		
		//Projectile->FireInDirection(NormalizedShootDirection);
	}
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AChest::Interacted_Implementation(AActor* OtherActor)
{
	InteractedEvent.Broadcast();

	//Should spawn a pickeable item inside the chest this i think must be controled by the gamemode if the items are random
	//or maybe by the chest I dont know if the spawn is controled by the game mode then the chest must have an event with a 
	//pointer to the chest in order to spawn the items inside the chest

	//Animation for opening the chest.
	if (Animation != nullptr) Animation->PlayFromStart_Implementation();

	//TreassureParticleComponent->ActivateSystem();
	//Disable the collisions, once opened cant be interacted any more 
	CollisionBox->DestroyComponent();
	
}

bool AChest::IsAnimationPlaying_Implementation() const
{
	if (Animation != nullptr)
	{
		return Animation->IsPlaying_Implementation();
	}
	return false;
}
