// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "InGameHUD.generated.h"

class UHUDWidget;

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	
  AInGameHUD();
  
  UPROPERTY(EditDefaultsOnly, Category = "Widgets")
  TSubclassOf<UUserWidget> HUDWidgetClass;

protected:
   virtual void BeginPlay() override;

public:
// Primary draw call for the HUD.
  virtual void DrawHUD() override;

  virtual void Tick(float DeltaTime) override;

  /*Proxy functon to access the HUDWidget*/
  UFUNCTION(BlueprintCallable)
  void UpdatePlayerHealthBar(float Health,float MaxHealth);

  /*Proxy functon to access the HUDWidget*/
  UFUNCTION(BlueprintCallable)
  void InteractionHint(const FString& Message, bool bVisible);


private:
  UHUDWidget* HUDWidget;
	
};
