// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFirstPersonGameInstance.h"

#include "HealthComponent.h"
#include "RifleWeapon.h"
#include "SingleShotWeapon.h"
#include "TestFirstPersonCharacter.h"

void UTestFirstPersonGameInstance::SaveMapData()
{
}

void UTestFirstPersonGameInstance::LoadMapData()
{
}

void UTestFirstPersonGameInstance::SaveCharacterData(ATestFirstPersonCharacter* Character)
{
	SavedHealth = Character->GetHealthComponent()->GetHealth();
	if(Character->PickupActor)
	{
		SavedPickup.Type = Character->PickupActor->GetType();
		if(SavedPickup.Type != BasePickup)
		{
			SavedPickup.Bullets = Character->GetWeapon()->CurrentBullets;
			SavedPickup.Clips = Character->GetWeapon()->CurrentClips;
		}
	}
	bIsFirstLoading = false;
}

void UTestFirstPersonGameInstance::LoadCharacterData(ATestFirstPersonCharacter* Character)
{
	FActorSpawnParameters SpawnInfo;
	TSubclassOf<ABasePickup> SpawnedActorClass;
	Character->GetHealthComponent()->SetHealth(SavedHealth);
	switch(SavedPickup.Type)
	{
	case BasePickup:
		Character->PickupItem(GetWorld()->SpawnActor<ABasePickup>(SpawnedActorClass, Character->GetActorLocation(),
			Character->GetActorRotation(), SpawnInfo));
		return;
	case RifleWeapon:
		Character->PickupItem(GetWorld()->SpawnActor<ARifleWeapon>(SpawnedActorClass, Character->GetActorLocation(),
			Character->GetActorRotation(), SpawnInfo));
		if(Character->GetWeapon())
		{
			Character->GetWeapon()->CurrentBullets = SavedPickup.Bullets;
			Character->GetWeapon()->CurrentClips = SavedPickup.Clips;
		}
		return;
	case SingledShotWeapon:
		Character->PickupItem(GetWorld()->SpawnActor<ASingleShotWeapon>(SpawnedActorClass, Character->GetActorLocation(),
			Character->GetActorRotation(), SpawnInfo));
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

void UTestFirstPersonGameInstance::SaveActor(ABasePickup* Actor)
{
	//FActorData SavedActor;
	//SavedActor.Type = Actor->GetType();
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