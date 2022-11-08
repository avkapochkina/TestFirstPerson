// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BaseAmmoWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTFIRSTPERSON_API UBaseAmmoWidget : public UUserWidget
{
public:
	virtual void NativeConstruct() override;
	GENERATED_BODY()

	UFUNCTION()
	void UpdateWidget(const int8& Clips, const int8& Bullets);
	
	UPROPERTY()
	UTextBlock* TextBlock;
};
