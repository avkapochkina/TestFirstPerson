// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "SpawnTrigger.generated.h"

UCLASS()
class TESTFIRSTPERSON_API ASpawnTrigger : public ABasePickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void Interact();
	
	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABasePickup> SpawnedActorClass;
};
