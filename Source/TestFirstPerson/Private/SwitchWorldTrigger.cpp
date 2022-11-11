// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchWorldTrigger.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASwitchWorldTrigger::ASwitchWorldTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->InitSphereRadius(Distance);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComponent->SetupAttachment(RootComponent);
}

void ASwitchWorldTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

void ASwitchWorldTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogActor, Warning, TEXT("ABasePickup::OnOverlapBegin"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if(Cast<APawn>(OtherActor))
		{
			FString CurrentMap = GetWorld()->GetMapName();
			CurrentMap.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

			UGameplayStatics::OpenLevel(GetWorld(), FName(MapName));
		}
	}
}

// Called when the game starts or when spawned
void ASwitchWorldTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASwitchWorldTrigger::OnOverlapBegin);
}

// Called every frame
void ASwitchWorldTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

