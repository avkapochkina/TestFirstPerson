// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "TestFirstPersonGameMode.h"
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
	ATestFirstPersonCharacter* Character = Cast<ATestFirstPersonCharacter>(GetOwner());
	if(!Character)
	{
		return;
	}
	if (!GetWorld() || IsAmmoEmpty())
	{
		return;
	}
	
	Super::MakeShot();
	
	FRotator Rotation;
	FVector Start = SkeletalMeshComponent->GetSocketLocation(MuzzleSocket);
	GetPlayerViewPoint(Start,Rotation);
	FVector End = Start + ShotDistance * Rotation.Vector();
	
	FHitResult HitResult;
	MakeHit(HitResult, Start, End);
       
    const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor)
		return;
	DamagedActor->TakeDamage(Damage, FDamageEvent{}, GetController(), this);
	
	if(Emitter)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Emitter, HitResult.Location, FRotator::ZeroRotator,
			FVector(1), true, EPSCPoolMethod::None, true);
}

void ARifleWeapon::StartFire()
{
	Super::StartFire();
	
	GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, this, &ARifleWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
	bIsShooting = true;
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
	if(GetOwner())
		CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.bReturnPhysicalMaterial = true;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_WorldStatic, CollisionQueryParams);
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

