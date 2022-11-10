// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dummy.h"
#include "TestFirstPersonCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "TestFirstPersonGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ATestFirstPersonCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AActor*, Actor);

UCLASS(minimalapi)
class ATestFirstPersonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestFirstPersonGameMode();
	
	const FOnPlayerDiedSignature& GetOnPlayerDied() const { return OnPlayerDied; }

	const FOnDeath& GetOnActorDied() const { return OnActorDied; }
	
	void RestartPlayer(AController* NewPlayer) override;
protected:
	virtual void BeginPlay() override;

	//Called when Player character has died.
	UFUNCTION()
	virtual void PlayerDied(ATestFirstPersonCharacter* Character);

	//Signature to bind delegate. 
	UPROPERTY()
	FOnPlayerDiedSignature OnPlayerDied;
	
	//Called when Actor character has died.
	UFUNCTION()
	virtual void ActorDied(AActor* Actor);

	UPROPERTY()
	FOnDeath OnActorDied;
};



