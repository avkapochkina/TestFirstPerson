// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleWeapon.h"


// Sets default values
ARifleWeapon::ARifleWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ARifleWeapon::MakeShot()
{
	Super::MakeShot();
	
}

void ARifleWeapon::StartFire()
{
	Super::StartFire();
}

void ARifleWeapon::StopFire()
{
	Super::StopFire();
}

// Called when the game starts or when spawned
void ARifleWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARifleWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

