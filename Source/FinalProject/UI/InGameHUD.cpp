// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"
#include "HUDWidget.h"

AInGameHUD::AInGameHUD()
{

}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUD_Widget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
		if (HUD_Widget != nullptr)
		{
			HUD_Widget->AddToViewport();
		}
	}
}

void AInGameHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInGameHUD::UpdatePlayerHealthBar(float Health, float MaxHealth)
{
	HUD_Widget->UpdatePlayerHealthBar(Health, MaxHealth);
}

void AInGameHUD::InteractionHint(const FString& Message, bool bVisible)
{
	HUD_Widget->SetInteractionHint(Message, bVisible);
}

void AInGameHUD::ShowGameMessage(const FString& Message, float time)
{
	HUD_Widget->ShowGameMessage(Message, time);
}
void AInGameHUD::SetQuestHint(const FString& Quest)
{
	HUD_Widget->SetQuestHint(Quest);
}

void AInGameHUD::DrawHUD()
{
	Super::DrawHUD();

}