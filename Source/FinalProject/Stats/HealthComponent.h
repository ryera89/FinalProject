// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	/*Event braodcasted when the health has been changed it broadcast two floats the current health and the max health*/
	DECLARE_EVENT_TwoParams(UHealthComponent,FHealthChange,float,float)
	FHealthChange OnHealthChange;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*Base health of the owner actor*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin="1"))
	float MaxHealth = 100;


public:

	/*Set the maximum health property it will affect the heatlh property by the same percentage 
	 * @param NewMaxHealth
	 */
	UFUNCTION(BlueprintCallable, category = "Health")
	void SetMaxHealth(float NewMaxHealth);

	/*Modify the health property by
	 * @param Amount: negative (ie damage recieved), positive (ie healed)
	 */
	UFUNCTION(BlueprintCallable, category = "Health")
	void ModifyHealth(float Amount);

private:
	/*Current health of the owner actor*/
	float Health;
};
