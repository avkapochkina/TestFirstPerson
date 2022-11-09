// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "GameFramework/Actor.h"
#include "RifleWeapon.generated.h"

UCLASS()
class TESTFIRSTPERSON_API ARifleWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARifleWeapon();

	virtual void MakeShot();

	virtual void StartFire();
	
	virtual void StopFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
