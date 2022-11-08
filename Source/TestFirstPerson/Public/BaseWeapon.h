﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestFirstPerson/Public/BasePickup.h"
#include "BaseWeapon.generated.h"

UCLASS()
class TESTFIRSTPERSON_API ABaseWeapon : public ABasePickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

	UFUNCTION()
	void MakeShot();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
};
