// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BaseWeapon.h"
#include "SingleShotWeapon.generated.h"

UCLASS()
class TESTFIRSTPERSON_API ASingleShotWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASingleShotWeapon();

	virtual void MakeShot() override;

	virtual void StartFire() override;
	
	virtual void StopFire() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ATestFirstPersonProjectile> ProjectileClass;
};
