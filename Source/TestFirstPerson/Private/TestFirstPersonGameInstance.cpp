// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFirstPersonGameInstance.h"

#include "Components/HealthComponent.h"
#include "Pickups/RifleWeapon.h"
#include "Pickups/SingleShotWeapon.h"
#include "TestFirstPersonCharacter.h"

UTestFirstPersonGameInstance::UTestFirstPersonGameInstance(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) { }

void UTestFirstPersonGameInstance::Init()
{
	Super::Init();
}

void UTestFirstPersonGameInstance::SaveCharacterData(ATestFirstPersonCharacter* Character)
{
	if(Character->GameInstanceRef)
	{
		SavedHealth = Character->GetHealthComponent()->GetHealth();
		if(Character->PickupActor)
		{
			SavedPickup.bIsHoldingItem = true;
			SavedPickup.Type = Character->PickupActor->GetType();
			if(SavedPickup.Type != BasePickup)
			{
				SavedPickup.Bullets = Character->GetWeapon()->CurrentBullets;
				SavedPickup.Clips = Character->GetWeapon()->CurrentClips;
			}
		}
		else
		{
			SavedPickup.bIsHoldingItem = false;
		}
		bIsFirstLoading = false;
	}
	
	UE_LOG(LogActor, Warning, TEXT("SavedPickup.bIsHoldingItem = %d"), SavedPickup.bIsHoldingItem);
}

void UTestFirstPersonGameInstance::LoadCharacterData(ATestFirstPersonCharacter* Character)
{
	if(Character->GameInstanceRef)
	{
		FActorSpawnParameters SpawnInfo;
		Character->GetHealthComponent()->SetHealth(SavedHealth);
		if(SavedPickup.bIsHoldingItem)
		{
			UE_LOG(LogActor, Warning, TEXT("LoadCharacter.bIsHoldingItem = %d"), SavedPickup.bIsHoldingItem);
			switch(SavedPickup.Type)
			{
			case BasePickup:
				Character->PickupItem(GetWorld()->SpawnActor<ABasePickup>(BasePickupClass,
					Character->GetActorLocation(), Character->GetActorRotation(), SpawnInfo));
				//Character->PickupItem(Actor);
				return;
			case RifleWeapon:
				Character->PickupItem(GetWorld()->SpawnActor<ARifleWeapon>(RifleWeaponClass,
					Character->GetActorLocation(), Character->GetActorRotation(), SpawnInfo));
				if(Character->GetWeapon())
				{
					Character->GetWeapon()->CurrentBullets = SavedPickup.Bullets;
					Character->GetWeapon()->CurrentClips = SavedPickup.Clips;
				}
				return;
			case SingledShotWeapon:
				Character->PickupItem(GetWorld()->SpawnActor<ASingleShotWeapon>(SingleShotWeaponClass,
					Character->GetActorLocation(), Character->GetActorRotation(), SpawnInfo));
				if(Character->GetWeapon())
				{
					Character->GetWeapon()->CurrentBullets = SavedPickup.Bullets;
					Character->GetWeapon()->CurrentClips = SavedPickup.Clips;
				}
				return;
			default:
				return;
			}
		}
	}
}

void UTestFirstPersonGameInstance::LoadActor(ABasePickup* Actor)
{
	FActorSpawnParameters SpawnInfo;
	TSubclassOf<ABasePickup> SpawnedActorClass;
	//for(int)
	switch(Actor->GetType())
	{
	case BasePickup:
		GetWorld()->SpawnActor<ABasePickup>(SpawnedActorClass, SavedPickup.Location, SavedPickup.Rotation, SpawnInfo);
		return;
	case RifleWeapon:
		GetWorld()->SpawnActor<ARifleWeapon>(SpawnedActorClass, SavedPickup.Location, SavedPickup.Rotation, SpawnInfo);
		return;
	case SingledShotWeapon:
		GetWorld()->SpawnActor<ASingleShotWeapon>(SpawnedActorClass, SavedPickup.Location, SavedPickup.Rotation, SpawnInfo);
		return;
	default:
		return;
	}
}