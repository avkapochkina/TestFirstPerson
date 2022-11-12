// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BaseWeapon.h"
#include "RifleWeapon.generated.h"

UCLASS()
class TESTFIRSTPERSON_API ARifleWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARifleWeapon();

	virtual void MakeShot();

	virtual void StartFire();
	
	virtual void StopFire();

	void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Comstants")
	float TimeBetweenShots = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Comstants")
	float ShotDistance = 5000.f;
	
	/** hit effect */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite="Gameplay")
	UParticleSystem* Emitter;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle ShotTimerHandle;
};
