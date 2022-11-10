// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHealthWidget.h"

void UBaseHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseHealthWidget::UpdateWidget(const float Health, const float MaxHealth)
{
	const FString String = "HP: " + FString::SanitizeFloat(Health) + " / " + FString::SanitizeFloat(MaxHealth);
	TextBlock->SetText(FText::FromString(String));
}