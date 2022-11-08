// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
	bIsWeapon = true;
	CurrentClips = MaxClips;
	CurrentBullets = MaxBullets;
	
	// Create a gun mesh component
	//SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	//SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetOnlyOwnerSee(false);
	SkeletalMeshComponent->bCastDynamicShadow = false;
	SkeletalMeshComponent->CastShadow = false;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(SkeletalMeshComponent);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
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
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

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

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
		
	if(AmmoWidget)
	{
		AmmoWidget->AddToViewport();
		AmmoWidget->SetVisibility(ESlateVisibility::Hidden);
	}
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

