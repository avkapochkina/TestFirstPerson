// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleWeapon.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ARifleWeapon::ARifleWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMeshComponent->SetSimulatePhysics(true);
}

void ARifleWeapon::MakeShot()
{
	Super::MakeShot();
	
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	
	if (!GetWorld()) return;
	
	FHitResult HitResult;
	FVector Start = MuzzleLocation->GetComponentLocation();
	FVector End = GetActorForwardVector() + Start;	
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.bReturnPhysicalMaterial = true;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldDynamic, CollisionQueryParams);

	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;
	DamagedActor->TakeDamage(Damage, FDamageEvent{}, GetController(), this);
	//DecreaseAmmo();	
}

void ARifleWeapon::StartFire()
{
	Super::StartFire();
	
	GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, this, &ARifleWeapon::MakeShot, TimeBetweenShots, true);
	bIsShooting = true;
	MakeShot();
}

void ARifleWeapon::StopFire()
{
	Super::StopFire();
	GetWorld()->GetTimerManager().ClearTimer(ShotTimerHandle);
	bIsShooting = false;
}

void ARifleWeapon::MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd)
{
	if (!GetWorld()) return;
	
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.bReturnPhysicalMaterial = true;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_WorldDynamic, CollisionQueryParams);
	//GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams);
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

