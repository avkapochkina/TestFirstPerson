// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "TestFirstPersonCharacter.h"
#include "TestFirstPersonGameMode.h"


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
		Owner->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::OnTakeAnyDamageHandle);
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
	//if (OnHealthChanged.IsBound())
	//	OnHealthChanged.Broadcast(Health, HealthDelta);
}

bool UHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || IsHealthFull()) return false;
	SetHealth(Health + HealthAmount);
	return true;
}

void UHealthComponent::Respawn(int32 RespawnTime)
{
	//RespawnCountdown = RespawnTime;
	//GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this,
	//	&UHealthComponent::RespawnTimerUpdate, 1.0f, true);
}

void UHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                             AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead()) return;
	SetHealth(Health - Damage);
	if (IsDead())
	{
		if(Cast<ATestFirstPersonCharacter>(DamagedActor))
		{
			ATestFirstPersonCharacter* Character = Cast<ATestFirstPersonCharacter>(DamagedActor);
			Character->OnDeath();
		}
		//
		const auto GameMode = GetWorld()->GetAuthGameMode<ATestFirstPersonGameMode>();
		if (!GameMode) return;
		GameMode->GameOver();
	}
}
