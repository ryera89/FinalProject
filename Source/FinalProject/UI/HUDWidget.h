// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetInteractionHint(const FString& Message, bool bVisible);
	void ShowGameMessage(const FString& Message,float DisplayTime);

protected:

	UPROPERTY(BlueprintReadOnly)
	bool bInteractionHintVisibility = false;

	UPROPERTY(BlueprintReadOnly)
	bool bGameMessageVisibility = false;

	UPROPERTY(BlueprintReadOnly)
	FString GameMessage = "";

	UPROPERTY(BlueprintReadOnly)
	FString InteractionMessage = "";

	UPROPERTY(BlueprintReadOnly)
	float PlayerHealth;

	UPROPERTY(BlueprintReadOnly)
	float PlayerStamina;

	virtual void NativeOnInitialized() override;

private:
	void HideGameMessage();
	FTimerHandle timer;

	UFUNCTION()
	void SetPlayerHealth(float Health);
	UFUNCTION()
	void SetPlayerStamina(float Stamina);
	
};
