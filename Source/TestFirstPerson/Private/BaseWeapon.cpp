﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// setup a gun mesh component
	SkeletalMeshComponent->SetOnlyOwnerSee(false);
	SkeletalMeshComponent->bCastDynamicShadow = false;
	SkeletalMeshComponent->CastShadow = false;
	RootComponent = SkeletalMeshComponent;
	
	//AmmoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	//AmmoWidgetComponent->SetupAttachment(RootComponent);
	//WidgetComponent->SetWidget(AmmoWidget);
	
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(SkeletalMeshComponent);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// setup constants
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
	bIsWeapon = true;
	CurrentClips = MaxClips;
	CurrentBullets = MaxBullets;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	if(AmmoWidget)
	{
		WidgetComponent->GetWidget()->AddToViewport();
		WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Hidden);
		WidgetComponent->SetWidget(AmmoWidget);
		//AmmoWidget->AddToViewport();
		//AmmoWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UE_LOG(LogActor, Warning, TEXT("!AmmoWidget"));
	}
}

void ABaseWeapon::MakeShot()
{
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const APlayerController* Controller = GetWorld()->GetFirstPlayerController();
			const FRotator SpawnRotation = Controller->GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character
			// location to find the final muzzle position
			const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation()
				: GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<ATestFirstPersonProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
	
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	
	DecreaseAmmo();
}

void ABaseWeapon::DecreaseAmmo()
{
	if(CurrentBullets == 0)
	{
		ChangeClip();
		return;
	}
	CurrentBullets--;
	
	if(AmmoWidget)
		AmmoWidget->UpdateWidget(CurrentClips, CurrentBullets);
}

bool ABaseWeapon::IsAmmoEmpty() const
{
	return (CurrentClips == 0) && (CurrentBullets == 0);
}

void ABaseWeapon::AttachWeapon(USkeletalMeshComponent* MeshComponent)
{
	SkeletalMeshComponent->SetupAttachment(MeshComponent, TEXT("GripPoint"));
}

void ABaseWeapon::ChangeClip()
{
	if (CurrentClips == 0)
		return;
	CurrentClips--;
	CurrentBullets = MaxBullets;
	
	if(AmmoWidget)
		AmmoWidget->UpdateWidget(CurrentClips, CurrentBullets);
}

