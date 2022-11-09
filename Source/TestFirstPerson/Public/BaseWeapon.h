// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAmmoWidget.h"
#include "TestFirstPerson/Public/BasePickup.h"
#include "TestFirstPerson/Public/TestFirstPersonProjectile.h"
#include "BaseWeapon.generated.h"

UCLASS()
class TESTFIRSTPERSON_API ABaseWeapon : public ABasePickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

	virtual void MakeShot();

	virtual void StartFire() {};
	
	virtual void StopFire() {};

	virtual void Reload() {};

	bool CanReload() const;
	
	virtual void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd);
	
	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* MuzzleLocation;
	
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ATestFirstPersonProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UBaseAmmoWidget* AmmoWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> AmmoWidgetClass;

	UPROPERTY()
	UBaseAmmoWidget* AmmoWidget;
	
	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void DecreaseAmmo();
	
	UFUNCTION()
	void ChangeClip();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants")
	uint8 MaxClips = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants")
	uint8 MaxBullets = 10;
	
	UPROPERTY(BlueprintReadOnly)
	uint8 CurrentClips;

	UPROPERTY(BlueprintReadOnly)
	uint8 CurrentBullets;
	
	UFUNCTION()
	bool IsAmmoEmpty() const;
	
	UFUNCTION()
	void AttachWeapon(USkeletalMeshComponent* MeshComponent);
};
