// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestFirstPersonGameMode.h"
#include "TestFirstPersonHUD.h"
#include "TestFirstPersonCharacter.h"
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
