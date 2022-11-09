// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleShotWeapon.h"


// Sets default values
ASingleShotWeapon::ASingleShotWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMeshComponent->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ASingleShotWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASingleShotWeapon::MakeShot()
{
	Super::MakeShot();
	
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const APlayerController* Controller = GetWorld()->GetFirstPlayerController();
			const FRotator SpawnRotation = Controller->GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character
			// location to find the final muzzle position
			const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation()
				: GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			ATestFirstPersonProjectile* Projectile = World->SpawnActor<ATestFirstPersonProjectile>(ProjectileClass,
				SpawnLocation, SpawnRotation, ActorSpawnParams);
			Projectile->Damage = Damage;
		}
	}
	
	//DecreaseAmmo();	
}

void ASingleShotWeapon::StartFire()
{
	Super::StartFire();
}

void ASingleShotWeapon::StopFire()
{
	Super::StopFire();
}


// Called every frame
void ASingleShotWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

