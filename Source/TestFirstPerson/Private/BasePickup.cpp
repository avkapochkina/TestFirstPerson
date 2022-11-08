// Fill out your copyright notice in the Description page of Project Settings.

#include "TestFirstPerson/Public/BasePickup.h"
#include "Components/WidgetComponent.h"


// Sets default values
ABasePickup::ABasePickup()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	RootComponent = SkeletalMeshComponent;
	SkeletalMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->InitSphereRadius(PickupDistance);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
	check(WidgetComponent);
	
	WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Hidden);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABasePickup::OnOverlapEnd);
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

void ABasePickup::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}

void ABasePickup::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogActor, Warning, TEXT("ABasePickup::OnOverlapBegin"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if(Cast<APawn>(OtherActor))
		{
			ShowWidget();
		}
	}
}

void ABasePickup::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogActor, Warning, TEXT("ABasePickup::OnOverlapEnd"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if(Cast<APawn>(OtherActor))
		{
			HideWidget();
		}
	}
}

void ABasePickup::ShowWidget() const
{
	if(WidgetComponent)
		WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Visible);
}

void ABasePickup::HideWidget() const
{
	if(WidgetComponent)
		WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
}