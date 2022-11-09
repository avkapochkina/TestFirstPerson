// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"
#include "Kismet/GameplayStatics.h"

ATrigger::ATrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->InitSphereRadius(Distance);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComponent->SetupAttachment(RootComponent);
}

void ATrigger::BeginPlay()
{
	Super::BeginPlay();
	
	check(SphereComponent);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrigger::OnOverlapBegin);
}

void ATrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

void ATrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogActor, Verbose, TEXT("ADamageTrigger::OnOverlapBegin"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetWorld()->GetFirstPlayerController(),
			this, UDamageType::StaticClass());
	}
}