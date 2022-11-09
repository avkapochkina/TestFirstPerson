// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAmmoWidget.h"

void UBaseAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseAmmoWidget::UpdateWidget(const int8 Clips, const int8 Bullets)
{
	FString String = FString::FromInt(Clips) + " / " + FString::FromInt(Bullets);
	TextBlock->SetText(FText::FromString(String));
}