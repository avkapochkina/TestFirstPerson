// Fill out your copyright notice in the Description page of Project Settings.

#include "TFPController.h"

ATFPController::ATFPController()
{
}

void ATFPController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("Pause", IE_Pressed, this, &ATFPController::OnPauseGame);
}

void ATFPController::BeginPlay()
{
	Super::BeginPlay();
}

void ATFPController::OnPauseGame()
{
	
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	//GetWorld()->GetAuthGameMode()->SetPause(this);
}
