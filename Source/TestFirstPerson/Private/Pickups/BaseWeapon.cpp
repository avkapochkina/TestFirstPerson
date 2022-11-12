// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/BaseWeapon.h"

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
	
	const ATestFirstPersonCharacter* Character = Cast<ATestFirstPersonCharacter>(GetOwner());
	UAnimInstance* AnimInstance = Character->Mesh1P->GetAnimInstance();
	if(Character && FireAnimation != nullptr)
	{
		AnimInstance->Montage_Play(FireAnimation, 1.f);
	}
	
	DecreaseAmmo();
}

bool ABaseWeapon::Reload()
{
	if(CanReload())
	{
		StopFire();
		ChangeClip();
		const ATestFirstPersonCharacter* Character = Cast<ATestFirstPersonCharacter>(GetOwner());
		UAnimInstance* AnimInstance = Character->Mesh1P->GetAnimInstance();
		if(Character && ReloadAnimation != nullptr)
		{
			AnimInstance->Montage_Play(ReloadAnimation, 1.f);
			AnimInstance->OnMontageEnded.AddDynamic(this, &ABaseWeapon::HandleOnMontageEnded);
			bIsReloading = true;
		}
		return true;
	}
	return false;
}

void ABaseWeapon::HandleOnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	const ATestFirstPersonCharacter* Character = Cast<ATestFirstPersonCharacter>(GetOwner());
	UAnimInstance* AnimInstance = Character->Mesh1P->GetAnimInstance();
	AnimInstance->OnMontageEnded.RemoveDynamic(this, &ABaseWeapon::HandleOnMontageEnded);
	bIsReloading = false;
}

bool ABaseWeapon::CanReload() const
{
	return CurrentBullets < MaxBullets && CurrentClips > 0 && !bIsReloading;
}

void ABaseWeapon::DecreaseAmmo()
{
	if(CurrentBullets == 0)
	{
		Reload();
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
	const ATestFirstPersonCharacter* Pawn = Cast<ATestFirstPersonCharacter>(GetOwner());
	
	if(Pawn == nullptr)
		return nullptr;
	return Pawn->GetController();
}

bool ABaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Character = Cast<ATestFirstPersonCharacter>(GetOwner());
	if (!Character)
	{
		return false;
	}

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

