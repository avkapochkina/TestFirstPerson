// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "TestFirstPersonCharacter.h"
#include "Actors/Dummy.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamageHandle);
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp<float>(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;
	Health = NextHealth;
}

bool UHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || IsHealthFull()) return false;
	SetHealth(Health + HealthAmount);
	return true;
}

void UHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                             AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f) return;
	SetHealth(FMath::Clamp(Health - Damage, 0.f, MaxHealth));
		
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
	   FString::Printf(TEXT("DamagedActor = %s, health = %f;"), *DamagedActor->GetName(), Health));
	if (IsDead())
	{
		if(Cast<ATestFirstPersonCharacter>(DamagedActor))
		{
			ATestFirstPersonCharacter* Actor = Cast<ATestFirstPersonCharacter>(DamagedActor);
			Actor->OnDeath();
			return;
		}
		if(ADummy* Actor = Cast<ADummy>(DamagedActor))
		{
			Actor->OnDeath();
			return;
		}
	}
}