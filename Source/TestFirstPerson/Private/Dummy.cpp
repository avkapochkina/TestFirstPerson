// Fill out your copyright notice in the Description page of Project Settings.


#include "Dummy.h"
#include "HealthComponent.h"

// Sets default values
ADummy::ADummy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;
	//WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
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
	
	HealthWidget_BP = CreateWidget<UBaseHealthWidget>(GetWorld(), HealthWidgetClass);
	if(HealthWidget_BP)
	{
		HealthWidget_BP->AddToViewport();
		HealthWidget_BP->SetVisibility(ESlateVisibility::Visible);
		//WidgetComponent->SetWidget(HealthWidget_BP);
		//WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Visible);
	}
}

// Called every frame
void ADummy::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
}

