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

	bool Reload();

	bool CanReload() const;
	
	//virtual void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd);
	
	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* MuzzleLocation;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;
	
	/** AnimMontage to play each time we reload */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* ReloadAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> AmmoWidgetClass;
	
	/** Widget that shows current ammo on the top of the screen */
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

	AController* GetController() const;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants")
	uint8 MaxClips = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants")
	uint8 MaxBullets = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constants")
	float Damage = 10.f;
	
	UPROPERTY(BlueprintReadOnly)
	uint8 CurrentClips;

	UPROPERTY(BlueprintReadOnly)
	uint8 CurrentBullets;
	
	UFUNCTION()
	bool IsAmmoEmpty() const;
	
	bool bIsShooting = false;
};
