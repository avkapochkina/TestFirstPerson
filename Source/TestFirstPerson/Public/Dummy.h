// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Dummy.generated.h"

class UHealthComponent;

UCLASS()
class TESTFIRSTPERSON_API ADummy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADummy();
	
	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UHealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> HealthWidgetClass;
	
	UPROPERTY()
	UUserWidget* HealthWidget_BP;
	
	void OnDeath();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
