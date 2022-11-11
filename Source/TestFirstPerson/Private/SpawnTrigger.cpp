// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnTrigger.h"

#include "TestFirstPersonCharacter.h"


// Sets default values
ASpawnTrigger::ASpawnTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;
	MeshComponent->SetSimulatePhysics(false);
	SkeletalMeshComponent->SetVisibility(false);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ASpawnTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpawnTrigger::Interact()
{
	FActorSpawnParameters SpawnInfo;

	FRotator Rotation = GetActorRotation();
	FVector Location = GetActorLocation();
	Location.Z += 50.0;
	GetWorld()->SpawnActor<ABasePickup>(SpawnedActorClass, Location, Rotation, SpawnInfo);
}

// Called every frame
void ASpawnTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

