// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

#include "TestFirstPersonCharacter.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// setup a gun mesh component
	RootComponent = SkeletalMeshComponent;
	SkeletalMeshComponent->SetOnlyOwnerSee(false);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMeshComponent->SetSimulatePhysics(true);
	
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

	AmmoWidget = CreateWidget<UBaseAmmoWidget>(GetWorld(), AmmoWidgetClass);
	if(AmmoWidget)
	{
		AmmoWidget->AddToViewport();
		AmmoWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ABaseWeapon::MakeShot()
{
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	
	DecreaseAmmo();
}

bool ABaseWeapon::Reload()
{
	if(CurrentClips > 0 && CurrentBullets < MaxBullets)
	{
		ChangeClip();
		return true;
	}
	return false;
}

bool ABaseWeapon::CanReload() const
{
	return CurrentBullets < MaxBullets && CurrentClips > 0;
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
	{
		AmmoWidget->UpdateWidget(CurrentClips, CurrentBullets);
	}
}

bool ABaseWeapon::IsAmmoEmpty() const
{
	return (CurrentClips == 0) && (CurrentBullets == 0);
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

AController* ABaseWeapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	
	if(Pawn == nullptr)
		return nullptr;
	return Pawn->GetController();
}

bool ABaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Character = Cast<ATestFirstPersonCharacter>(GetOwner());
	if (!Character) return false;

	if (Character->IsPlayerControlled())
	{
		const auto Controller = GetController();
		if (!Controller) return false;
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = SkeletalMeshComponent->GetSocketLocation(MuzzleSocket);
		ViewRotation = SkeletalMeshComponent->GetSocketRotation(MuzzleSocket);
	}
	return true;
}

