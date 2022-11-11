// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestFirstPersonCharacter.h"
#include "BaseCharacter.h"
#include "TestFirstPersonGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ATestFirstPersonCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOtherCharacterDiedSignature, ABaseCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AActor*, Actor);

UCLASS(minimalapi)
class ATestFirstPersonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestFirstPersonGameMode();
	
	const FOnPlayerDiedSignature& GetOnPlayerDied() const { return OnPlayerDied; }

	const FOnDeath& GetOnActorDied() const { return OnActorDied; }
	
	const FOnOtherCharacterDiedSignature& GetOnCharacterDied() const { return OnCharacterDied; }
	
	void RestartPlayer(AController* NewPlayer) override;
protected:
	virtual void BeginPlay() override;

	//Signature to bind delegate. 
	UPROPERTY()
	FOnPlayerDiedSignature OnPlayerDied;
	
	UPROPERTY()
	FOnDeath OnActorDied;
	
	UPROPERTY()
	FOnOtherCharacterDiedSignature OnCharacterDied;
	//Called when Player character has died.
	UFUNCTION()
	virtual void PlayerDied(ATestFirstPersonCharacter* Character);
	
	//Called when Actor character has died.
	UFUNCTION()
	virtual void ActorDied(AActor* Actor);

	UFUNCTION()
	virtual void CharacterDied(ABaseCharacter* Character);
};
	



