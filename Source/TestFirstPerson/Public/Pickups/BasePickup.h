// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class UWidgetComponent;

UENUM()
enum EType
{
	BasePickup     UMETA(DisplayName = "BasePickup"),
	RifleWeapon      UMETA(DisplayName = "RifleWeapon"),
	SingledShotWeapon   UMETA(DisplayName = "SingledShotWeapon"),
};

UCLASS()
class TESTFIRSTPERSON_API ABasePickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
	UPROPERTY()
	TEnumAsByte<EType> Type = BasePickup;
public:

	UFUNCTION()
	void ShowWidget() const;
	
	UFUNCTION()
	void HideWidget() const;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constants")
	float PickupDistance = 100.0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	USphereComponent* SphereComponent;

	// pickup widget shown in Distance < PickupDistance
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	UWidgetComponent* WidgetComponent;

	UFUNCTION()
	TEnumAsByte<EType> GetType() const { return Type; }
};
