// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivableTrap.h"
#include "Components/BoxComponent.h"
#include "../Interfaces/Animation.h"

// Sets default values
AActivableTrap::AActivableTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(Root);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AActivableTrap::OnHit);

}

// Called when the game starts or when spawned
void AActivableTrap::BeginPlay()
{
	Super::BeginPlay();

	//Get the animable components of the actors actors who inherit from this class
	TInlineComponentArray<USceneComponent*> SceneComponents(this);

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, 
	//	FString::Printf(TEXT("Scene Components Found on activable actor %i"),SceneComponents.Num()));
	//Get the meshes who has the tag "Animable"
	for (USceneComponent* component : SceneComponents)
	{
		if (component->ComponentHasTag(FName("Animable")))
		{
			AnimableComponents.Add(component);
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("Animable Components Found %i"),AnimableComponents.Num()));
	TArray<UActorComponent*> AnimArray = GetComponentsByInterface(UAnimation::StaticClass());
	/*Only one Animation component will be used*/
	if (AnimArray.Num()) Animation = Cast<IAnimation>(AnimArray[0]);

	if (Animation != nullptr) Animation->SetStartingPropertiesValues_Implementation(AnimableComponents);

	if (TriggerEventSource != nullptr)
	{
		TriggerEventSource->OnActivated().AddUObject(this, &AActivableTrap::Activated_Implementation);
		TriggerEventSource->OnDeactivated().AddUObject(this, &AActivableTrap::Deactivated_Implementation);
	}
	
}

void AActivableTrap::Activated_Implementation()
{
	State = EActivableState::Activated;

	if (Animation != nullptr) Animation->Play_Implementation();

	OnActivatedEvent.Broadcast();
}

void AActivableTrap::Deactivated_Implementation()
{
	State = EActivableState::Deactivated;

	if (Animation != nullptr) Animation->Reverse_Implementation();

	OnDeactivatedEvent.Broadcast();
}

void AActivableTrap::ChangeState_Implementation()
{
	if (State == EActivableState::Activated)
	{
		Deactivated_Implementation();
	}
	else
	{
		Activated_Implementation();
	}
}

// Called every frame
void AActivableTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AActivableTrap::IsAnimationPlaying_Implementation() const
{
	if (Animation != nullptr)
	{
		return Animation->IsPlaying_Implementation();
	}
	return false;
}

void AActivableTrap::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("OnHit Trap Event called"));
	if (OtherActor != this)
	{
		if (IsAnimationPlaying_Implementation())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Trap Apply damage to actor"));
			FDamageEvent DamageEvent;
			OtherActor->TakeDamage(Damage, DamageEvent, nullptr, this);
		}
	}

}

