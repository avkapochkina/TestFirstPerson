// Fill out your copyright notice in the Description page of Project Settings.

#include "TestFirstPerson/Public/BasePickup.h"
#include "Components/WidgetComponent.h"


// Sets default values
ABasePickup::ABasePickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	RootComponent = SkeletalMeshComponent;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->InitSphereRadius(100.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComponent->SetupAttachment(RootComponent);

	HighlightMaterial = CreateDefaultSubobject<UMaterial>(TEXT("HighlightMaterial"));
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
	check(WidgetComponent);
	
	WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Hidden);
	UE_LOG(LogActor, Warning, TEXT("ABasePickup::BeginPlay"));

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABasePickup::OnOverlapEnd);
	
	SkeletalMeshComponent->SetMaterial(1, HighlightMaterial);
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	UE_LOG(LogActor, Warning, TEXT("ABasePickup::NotifyActorBeginOverlap"));
}

void ABasePickup::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	UE_LOG(LogActor, Warning, TEXT("ABasePickup::NotifyActorEndOverlap"));
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
			if(HighlightMaterial)
			{
				ShowHighlight();
			}
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
			if(HighlightMaterial)
			{
				HideHighlight();
			}
		}
	}
}

void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePickup::ShowWidget()
{
	if(WidgetComponent)
		WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Visible);
}

void ABasePickup::HideWidget()
{
	if(WidgetComponent)
		WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
}

void ABasePickup::ShowHighlight()
{
	UE_LOG(LogActor, Warning, TEXT("ADD HIGHLIGHT"));
}

void ABasePickup::HideHighlight()
{
	UE_LOG(LogActor, Warning, TEXT("ADD HIGHLIGHT"));
}
