﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Dummy.h"
#include "HealthComponent.h"


// Sets default values
ADummy::ADummy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

void ADummy::OnDeath()
{
	delete this;
}

// Called when the game starts or when spawned
void ADummy::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	
	OnTakeAnyDamage.AddDynamic(this,&ADummy::OnTakeAnyDamageHandle);
}

void ADummy::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogActor, Verbose, TEXT("ADummy::OnTakeAnyDamageHandle"));
	//
}

// Called every frame
void ADummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

