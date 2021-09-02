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

	UFUNCTION(BlueprintCallable)
	void ShowGameMessage(const FString& Message,float DisplayTime);

	UFUNCTION(BlueprintCallable)
	void SetQuestHint(const FString& Quest);

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerHealthBar(float Health,float MaxHealth);

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
	FString QuestHint = "Quest: Find the missing Sun Spear and active the pilar";

	/*Player health percentage*/
	UPROPERTY(BlueprintReadOnly)
	float PlayerHealthPercentage = 1;

	UPROPERTY(BlueprintReadOnly)
	float PlayerStaminaPercentage;

	UPROPERTY(BlueprintReadOnly)
	ESlateVisibility InteractionHintVisibility = ESlateVisibility::Hidden;

	UPROPERTY(BlueprintReadOnly)
	ESlateVisibility GameMessageVisibility = ESlateVisibility::Hidden;

	virtual void NativeOnInitialized() override;

private:
	void HideGameMessage();
	FTimerHandle timer;

	UFUNCTION()
	void SetPlayerStamina(float Stamina);
	
};
