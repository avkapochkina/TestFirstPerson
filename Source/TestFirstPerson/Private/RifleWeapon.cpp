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
	Super::MakeShot();	
	if (!GetWorld())
	{
		UE_LOG(LogActor, Verbose, TEXT("!GetWorld()"));
		return;
	}
	
	FHitResult HitResult;
	//FVector Start = SkeletalMeshComponent->GetSocketLocation(MuzzleSocket);
	const auto Pawn = Cast<APawn>(GetOwner());
	if(Pawn == nullptr)
	{
		UE_LOG(LogActor, Verbose, TEXT("!Pawn"));
		return;
	}

	//FVector ViewLocation = SkeletalMeshComponent->GetSocketLocation(MuzzleSocket);
	FVector ViewLocation;
	//FRotator ViewRotation = SkeletalMeshComponent->GetSocketRotation(MuzzleSocket);
	FRotator ViewRotation;
	//if (GetPlayerViewPoint(ViewLocation, ViewRotation))
	//{
		const FVector ShootDirection = ViewRotation.Vector();
		//FVector Start = ViewLocation;
		FVector Start = SkeletalMeshComponent->GetSocketLocation(MuzzleSocket);
		//FVector End = ViewLocation + ShootDirection * ShotDistance;
		FVector End = Start + SkeletalMeshComponent->GetSocketRotation(MuzzleSocket).Vector() * ShotDistance;
		UE_LOG(LogActor, Verbose, TEXT("%f,%f,%f"), Start.X, Start.Y, Start.Z);
		UE_LOG(LogActor, Verbose, TEXT("%f,%f,%f"), End.X, End.Y, End.Z);
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(GetOwner());
        CollisionQueryParams.AddIgnoredActor(this);
        CollisionQueryParams.bReturnPhysicalMaterial = true;
        GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldDynamic, CollisionQueryParams);
        
        const auto DamagedActor = HitResult.GetActor();
		if (!DamagedActor)
        	return;
	
		if(Emitter)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Emitter, HitResult.Location, FRotator::ZeroRotator,
				FVector(1), true, EPSCPoolMethod::None, true);
		//DamagedActor->TakeDamage(Damage, FDamageEvent{}, GetController(), this);
	//}
	//else
	//{
	//	UE_LOG(LogActor, Verbose, TEXT("!GetPlayerViewPoint"));
	//}
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
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, HitResult.bBlockingHit ? FColor::Blue : FColor::Red, false,
			5.0f, 0, 1.0f);
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

