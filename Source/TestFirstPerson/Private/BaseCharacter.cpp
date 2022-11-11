// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "TestFirstPersonGameMode.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
}

void ABaseCharacter::OnDeath()
{
	SetLifeSpan(5.0f);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	
	CallRestartPlayer();
}

void ABaseCharacter::Destroyed()
{	
	Super::Destroyed();
	
	// Example to bind to OnPlayerDied event in GameMode. 
	if (UWorld* World = GetWorld())
	{
		if (ATestFirstPersonGameMode* GameMode = Cast<ATestFirstPersonGameMode>(World->GetAuthGameMode()))
		{
			GameMode->GetOnCharacterDied().Broadcast(this);
		}
	}
}

void ABaseCharacter::CallRestartPlayer()
{
}


// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//
}

