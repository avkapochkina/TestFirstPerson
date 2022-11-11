// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "TestFirstPersonGameInstance.generated.h"

/**
 * 
 */

class ARifleWeapon;
class ASingleShotWeapon;
class ATestFirstPersonCharacter;

struct FActorData
{
	TEnumAsByte<EType> Type;
	FVector Location;
	FRotator Rotation;
	int Clips;
	int Bullets;
};

UCLASS()
class TESTFIRSTPERSON_API UTestFirstPersonGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	float SavedHealth;
	FActorData SavedPickup;
	TMap<FString, TArray<FActorData>> SavedActors;

	bool bIsFirstLoading = true;
	
	void SaveMapData();
	void LoadMapData();

	void SaveCharacterData(ATestFirstPersonCharacter* Character);
	void LoadCharacterData(ATestFirstPersonCharacter* Character);
	
	void SaveActor(ABasePickup* Actor);
	void LoadActor(ABasePickup* Actor);
};
