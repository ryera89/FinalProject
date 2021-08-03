// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "../FinalProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

void UHUDWidget::ShowGameMessage(const FString& Message,float DisplayTime)
{	
	bGameMessageVisibility = true;
	GameMessage = Message;

	UWorld* TheWorld = GetWorld();
	/*if (TheWorld != nullptr)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);

		AExamenParcialGameMode* MyGameMode = Cast<AExamenParcialGameMode>(GameMode);

		if (MyGameMode != nullptr)
		{
			//FTimerHandle timer;
			MyGameMode->GetWorldTimerManager().SetTimer(timer, this, &UHUDWidget::HideGameMessage,DisplayTime);
		}
	}*/
}

void UHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	
	//ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//if (AFinalProjectCharacter* PlayerCharacter = Cast<AFinalProjectCharacter>(Character))
	//{
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("binding of messages"));
		// 
		//PlayerCharacter->InteractionHint.BindUObject(this, &UHUDWidget::SetInteractionHint);
		// 
		//AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);

		/*AExamenParcialGameMode* MyGameMode = Cast<AExamenParcialGameMode>(GameMode);

		if (MyGameMode != nullptr)
		{
			MyGameMode->GameInteractionHintDelegate.BindUObject(this, &UHUDWidget::SetInteractionHintVisibility);
			MyGameMode->GameMessageDelegate.BindUObject(this, &UHUDWidget::ShowGameMessage);
		}*/

		
		//PlayerCharacter->OnHealthChanged.AddUObject(this, &UHUDWidget::SetPlayerHealth);
		//PlayerCharacter->OnStaminaChanged.AddUObject(this, &UHUDWidget::SetPlayerStamina);	
	//}
    
}

void UHUDWidget::HideGameMessage()
{
	bGameMessageVisibility = false;
}

void UHUDWidget::UpdatePlayerHealthBar(float Health,float MaxHealth)
{

	PlayerHealthPercentage = Health/MaxHealth;
}

void UHUDWidget::SetPlayerStamina(float Stamina)
{
	PlayerStaminaPercentage = Stamina;
}

void UHUDWidget::SetInteractionHint(const FString& Message,bool bVisible)
{
	InteractionMessage = Message;
	bInteractionHintVisibility = bVisible;

	InteractionHintVisibility = (bVisible) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}

