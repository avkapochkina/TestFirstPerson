// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTrigger.generated.h"

class USphereComponent;

UCLASS()
class TESTFIRSTPERSON_API ADamageTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamageTrigger();
	
	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	USphereComponent* SphereComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constantes")
	float Distance = 100.0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constantes")
	float Damage = 100.0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
