// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestFirstPerson/Public/TestFirstPersonCharacter.h"
#include "BasePickup.h"
#include "DrawDebugHelpers.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "SpawnTrigger.h"
#include "TestFirstPerson/Public/BaseAmmoWidget.h"
#include "TestFirstPersonGameMode.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ATestFirstPersonCharacter

ATestFirstPersonCharacter::ATestFirstPersonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a HealthComponent
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	Levels.Add("FirstMap");
	Levels.Add("SecondMap");
}

void ATestFirstPersonCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	Mesh1P->SetHiddenInGame(false, true);
	check(HealthComponent);
}

void ATestFirstPersonCharacter::OnDeath()
{
	//PlayAnimMontage(DeathAnimMontage);
	DetachItem();

	SetLifeSpan(5.0f);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	
	CallRestartPlayer();
}

void ATestFirstPersonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);
	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATestFirstPersonCharacter::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATestFirstPersonCharacter::StopFire);

	// Bind pickup event
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ATestFirstPersonCharacter::Interact);
	
	// Bind reload event
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ATestFirstPersonCharacter::Reload);
	
	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ATestFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestFirstPersonCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATestFirstPersonCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATestFirstPersonCharacter::LookUpAtRate);
}

void ATestFirstPersonCharacter::Destroyed()
{
	Super::Destroyed();
	
	// Example to bind to OnPlayerDied event in GameMode. 
	if (UWorld* World = GetWorld())
	{
		if (ATestFirstPersonGameMode* GameMode = Cast<ATestFirstPersonGameMode>(World->GetAuthGameMode()))
		{
			GameMode->GetOnPlayerDied().Broadcast(this);
		}
	}
}

void ATestFirstPersonCharacter::CallRestartPlayer()
{
	//Get a reference to the Pawn Controller.
	AController* CortollerRef = GetController();

	//Destroy the Player.   
	Destroy();

	//Get the World and GameMode in the world to invoke its restart player function.
	if (UWorld* World = GetWorld())
	{
		if (ATestFirstPersonGameMode* GameMode = Cast<ATestFirstPersonGameMode>(World->GetAuthGameMode()))
		{
			GameMode->RestartPlayer(CortollerRef);
		}
	}
}

void ATestFirstPersonCharacter::OnFire()
{
	if(!CanFire() || Weapon->IsAmmoEmpty())
	{
		return;
	}	
	Weapon->StartFire();
}

void ATestFirstPersonCharacter::StopFire()
{
	if(Weapon)
		Weapon->StopFire();
}

void ATestFirstPersonCharacter::Reload()
{
	if(Weapon)
	{
		Weapon->Reload();
	}
}

void ATestFirstPersonCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ATestFirstPersonCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ATestFirstPersonCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATestFirstPersonCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATestFirstPersonCharacter::Interact()
{
	if(GetWorld() != nullptr)
	{
		// use LineTrace to check item in sight
		FHitResult OutHit;
		FVector Start; FRotator Rotation;
		FirstPersonCameraComponent->GetSocketWorldLocationAndRotation(FirstPersonCameraComponent->GetAttachSocketName(),
			Start, Rotation);
		FVector ForwardVector =	FirstPersonCameraComponent->GetForwardVector();
		FVector End = ForwardVector * PickupDistance + Start;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
			
		if(GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_WorldStatic, CollisionParams))
		{
			// choose action with actor
			if(Cast<ASpawnTrigger>(OutHit.Actor))
			{
				ASpawnTrigger* HitActor = Cast<ASpawnTrigger>(OutHit.Actor);
				HitActor->Interact();
				return;
			}
			// drop item if player already have something in hands
			if(PickupActor)
			{
				DetachItem();
				return;
			}
			if(Cast<ABasePickup>(OutHit.Actor))
			{
				ABasePickup* HitActor = Cast<ABasePickup>(OutHit.Actor);
				PickupItem(HitActor);
				return;
			}
		}
		else
		{
			if(PickupActor)
			{
				DetachItem();
				return;
			}
		}
	}
}


void ATestFirstPersonCharacter::PickupItem(ABasePickup* Actor)
{
	PickupActor = Actor;
	// setup weapon and it's widget
	if(PickupActor && PickupActor->bIsWeapon)
	{
		Weapon = Cast<ABaseWeapon>(PickupActor);
		if(Weapon->AmmoWidget)
		{
			Weapon->AmmoWidget->SetVisibility(ESlateVisibility::Visible);
			Weapon->AmmoWidget->UpdateWidget(Weapon->CurrentClips, Weapon->CurrentBullets);
			Weapon->SetOwner(this);
		}
	}
	// hide pickup widget and disable collision while item is in hands
	PickupActor->SkeletalMeshComponent->SetSimulatePhysics(false);
	PickupActor->SkeletalMeshComponent->SetEnableGravity(false);
	PickupActor->SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickupActor->AttachToComponent(this->Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget,
	true), PickupItemSocket);
}

void ATestFirstPersonCharacter::DetachItem()
{
	if(PickupActor)
	{
		UE_LOG(LogActor, Verbose, TEXT("Detaching PickupItem"));
		if(PickupActor->bIsWeapon)
		{
			if(Weapon)
			{
				Weapon->SetOwner(nullptr);
				if(Weapon->AmmoWidget)
					Weapon->AmmoWidget->SetVisibility(ESlateVisibility::Hidden);
				Weapon = nullptr;
			}
		}
		PickupActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PickupActor->SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		PickupActor->SkeletalMeshComponent->SetSimulatePhysics(true);
		PickupActor->SkeletalMeshComponent->SetEnableGravity(true);
		PickupActor = nullptr;
	}
}

bool ATestFirstPersonCharacter::CanFire() const
{
	if(!PickupActor)
		return false;
	if(!Weapon)
		return false;
	return PickupActor->bIsWeapon;
}
