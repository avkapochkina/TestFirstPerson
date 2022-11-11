// Fill out your copyright notice in the Description page of Project Settings.


#include "Dummy.h"
#include "HealthComponent.h"

// Sets default values
ADummy::ADummy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

void ADummy::OnDeath()
{
	this->Destroy();
}

// Called when the game starts or when spawned
void ADummy::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	
	HealthComponent->SetHealth(HealthComponent->MaxHealth);
	HealthWidget_BP = CreateWidget<UBaseHealthWidget>(GetWorld(), HealthWidgetClass);
	if(WidgetComponent)
	{
	//	HealthWidget_BP->AddToViewport();
	//	HealthWidget_BP->SetVisibility(ESlateVisibility::Visible);
		WidgetComponent->SetWidget(HealthWidget_BP);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
		   FString::Printf(TEXT("!HealthWidget_BP")));
	}
}

// Called every frame
void ADummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

