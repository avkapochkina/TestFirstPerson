// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BaseHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTFIRSTPERSON_API UBaseHealthWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateWidget(const float Health, const float MaxHealth);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlock;
};
