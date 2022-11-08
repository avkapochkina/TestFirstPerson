// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestFirstPerson/Public/TestFirstPersonGameMode.h"

#include "EngineUtils.h"
#include "TestFirstPerson/Public/TestFirstPersonHUD.h"
#include "TestFirstPerson/Public/TestFirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestFirstPersonGameMode::ATestFirstPersonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestFirstPersonHUD::StaticClass();
}

void ATestFirstPersonGameMode::GameOver()
{
	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}
}

void ATestFirstPersonGameMode::RespawnRequest(AController* Controller)
{
	//ResetOnePlayer(Controller);
}

