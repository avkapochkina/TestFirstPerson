// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTFIRSTPERSON_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();
	
	UFUNCTION(BlueprintCallable, Category="Health")
	float GetHealth() const { return Health; };
	
	UFUNCTION(BlueprintCallable, Category="Health")
	float GetMaxHealth() const { return MaxHealth; };
	
	UFUNCTION(BlueprintCallable, Category="Health")
	float GetHealthPercentage() const { return Health / MaxHealth; };
	
	UFUNCTION(BlueprintCallable, Category="Health")
	bool IsDead() const { return Health <= 0.0f; };
	
	UFUNCTION(BlueprintCallable, Category="Health")
	bool IsHealthFull() const { return FMath::IsNearlyEqual(Health, MaxHealth); };
	
	void SetHealth(float NewHealth);
	
	bool TryToAddHealth(float HealthAmount);
	
	// respawn:
	void Respawn(int32 RespawnTime);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth;

	float Health;
	
	//UFUNCTION()
	//void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	//	class AController* InstigatedBy, AActor* DamageCauser);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	 FActorComponentTickFunction* ThisTickFunction) override;
};
