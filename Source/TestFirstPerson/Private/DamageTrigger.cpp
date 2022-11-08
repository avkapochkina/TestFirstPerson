// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTrigger.h"
#include "Components/SphereComponent.h"


// Sets default values
ADamageTrigger::ADamageTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->InitSphereRadius(Distance);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	RootComponent = SphereComponent;
}

// Called when the game starts or when spawned
void ADamageTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADamageTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

void ADamageTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogActor, Warning, TEXT("ABasePickup::OnOverlapBegin"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		FDamageEvent Event(UDamageType::StaticClass());
		OtherActor->TakeDamage(Damage, Event, GetInstigatorController(), this);
	}
}

// Called every frame
void ADamageTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

