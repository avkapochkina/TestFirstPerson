// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h" 
#include "Pickups/BasePickup.h"
#include "CoreMinimal.h"
#include "TestFirstPersonGameInstance.generated.h"

/**
 * 
 */

class ARifleWeapon;
class ASingleShotWeapon;
class ATestFirstPersonCharacter;

struct FActorData
{
	bool bIsHoldingItem = false;
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
	UTestFirstPersonGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Classes)
	TSubclassOf<ABasePickup> BasePickupClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Classes)
	TSubclassOf<ARifleWeapon> RifleWeaponClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Classes)
	TSubclassOf<ASingleShotWeapon> SingleShotWeaponClass;
	
	float SavedHealth;
	FActorData SavedPickup;

	bool bIsFirstLoading = true;
	
	void SaveCharacterData(ATestFirstPersonCharacter* Character);
	void LoadCharacterData(ATestFirstPersonCharacter* Character);
	
	void LoadActor(ABasePickup* Actor);
};
