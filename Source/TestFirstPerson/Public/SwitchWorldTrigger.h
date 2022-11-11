// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwitchWorldTrigger.generated.h"

class USphereComponent;
UCLASS()
class TESTFIRSTPERSON_API ASwitchWorldTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASwitchWorldTrigger();
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	USphereComponent* SphereComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constants")
	float Distance = 100.0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constants")
	FString MapName;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
