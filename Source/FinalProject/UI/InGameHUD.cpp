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
		HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidget != nullptr)
		{
			HUDWidget->AddToViewport();
		}
	}
}

void AInGameHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInGameHUD::UpdatePlayerHealthBar(float Health, float MaxHealth)
{
	HUDWidget->UpdatePlayerHealthBar(Health, MaxHealth);
}

void AInGameHUD::InteractionHint(const FString& Message, bool bVisible)
{
	HUDWidget->SetInteractionHint(Message, bVisible);
}

void AInGameHUD::DrawHUD()
{
	Super::DrawHUD();

}