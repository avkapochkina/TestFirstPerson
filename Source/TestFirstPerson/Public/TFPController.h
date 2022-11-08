// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TFPController.generated.h"

/**
 * 
 */
UCLASS()
class TESTFIRSTPERSON_API ATFPController : public APlayerController
{
	GENERATED_BODY()
public:
	ATFPController();
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
private:
	void OnPauseGame();
};
