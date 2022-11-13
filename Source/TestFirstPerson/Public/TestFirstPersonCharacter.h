// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BaseWeapon.h"
#include "TestFirstPersonGameInstance.h"
#include "GameFramework/Character.h"
#include "Widgets/BaseHealthWidget.h"
#include "TestFirstPersonCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;
class ABasePickup;
class UHealthComponent;

UCLASS(config=Game)

class ATestFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay();
	
public:
	ATestFirstPersonCharacter();
		
	UPROPERTY()
	class UTestFirstPersonGameInstance* GameInstanceRef;
	
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	
	/** Return HealthComponent */
	UHealthComponent* GetHealthComponent() const { return HealthComponent; }
	
	/** Called on death */
	virtual void OnDeath();
	
	/** Pickup item */
	void PickupItem(ABasePickup* Actor);
	
	/** Item in hands */
	UPROPERTY()
	ABasePickup* PickupActor;
protected:
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);
	
	/** Interact or pickup item */
	void Interact();
	
	/** Start fire if there is weapon in hands */
	void OnFire();
	
	/** Stop fire */
	void StopFire();
	
	/** Reload weapon */
	void Reload();
	
	/** Open item spawn menu */
	void OpenMenu();
	
	/** Check is character able to fire */
	UFUNCTION()
	bool CanFire() const;
	
	/** Detach item from hands */
	void DetachItem();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UHealthComponent* HealthComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constants")
	float PickupDistance = 300.0;
	
	UPROPERTY()
	ABaseWeapon* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FName PickupItemSocket = "GripPoint";
	
	/** Widget with bindings info */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Classes)
	TSubclassOf<UUserWidget> Info_BP;
	UPROPERTY()
	UUserWidget* InfoWidget;
	
	/** Widget that spawns chosen weapon */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Classes)
	TSubclassOf<UUserWidget> SpawnMenu_BP;
	UPROPERTY()
	UUserWidget* SpawnMenu;
	
	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
	
	//Called when our Actor is destroyed during Gameplay.
	virtual void Destroyed();

	//Call Gamemode class to Restart Player Character.
	void CallRestartPlayer();
	
public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
	UFUNCTION(BlueprintCallable)
	ABaseWeapon* GetWeapon() const { return Weapon; };

};
