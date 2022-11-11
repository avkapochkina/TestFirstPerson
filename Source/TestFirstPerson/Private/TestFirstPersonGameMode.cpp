// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestFirstPerson/Public/TestFirstPersonGameMode.h"
#include "TestFirstPerson/Public/TestFirstPersonHUD.h"
#include "EngineUtils.h"
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

void ATestFirstPersonGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);
}

void ATestFirstPersonGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	//Bind our Player died delegate to the Gamemode's PlayerDied function.
	if (!OnPlayerDied.IsBound())
	{
		OnPlayerDied.AddDynamic(this, &ATestFirstPersonGameMode::PlayerDied);
	}
	
	if (!OnActorDied.IsBound())
	{
		OnActorDied.AddDynamic(this, &ATestFirstPersonGameMode::ActorDied);
	}
}

void ATestFirstPersonGameMode::PlayerDied(ATestFirstPersonCharacter* Character)
{
	//Get a reference to our Character's Player Controller
	AController* CharacterController = Character->GetController();
	RestartPlayer(CharacterController);
}

void ATestFirstPersonGameMode::ActorDied(AActor* Actor)
{
	// 
}

