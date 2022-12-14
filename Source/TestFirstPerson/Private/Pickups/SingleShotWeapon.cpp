// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/SingleShotWeapon.h"
#include "Actors/TestFirstPersonProjectile.h"


// Sets default values
ASingleShotWeapon::ASingleShotWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMeshComponent->SetSimulatePhysics(true);
	
	Type = SingledShotWeapon;
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
			const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation()
				: GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			ATestFirstPersonProjectile* Projectile = World->SpawnActor<ATestFirstPersonProjectile>(ProjectileClass,
				SpawnLocation, SpawnRotation, ActorSpawnParams);
			if(Projectile)
				Projectile->Damage = Damage;
		}
	}
}

void ASingleShotWeapon::StartFire()
{
	Super::StartFire();
	MakeShot();
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

