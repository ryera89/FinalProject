// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{ 
	//Saveguard against passing negative values of NewMaxHealth;
	NewMaxHealth = FMath::Max(0.0f, NewMaxHealth);
	//Keep the Health-MaxHealth ratio
	Health *= NewMaxHealth / MaxHealth;
	MaxHealth = NewMaxHealth;
	OnHealthChange.Broadcast(Health, MaxHealth);
}

void UHealthComponent::ModifyHealth(float Amount)
{
	Health = FMath::Clamp(Health+Amount, 0.0f, MaxHealth);
	OnHealthChange.Broadcast(Health, MaxHealth);
}

