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
//#include "Components/HealthComponent.h"
#include "MotionControllerComponent.h"

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

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
	
	/*
	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
	*/
}

void ATestFirstPersonCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	Mesh1P->SetHiddenInGame(false, true);
}

void ATestFirstPersonCharacter::OnHealthChanged(float CurrentHealth, float HealthDelta)
{
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATestFirstPersonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATestFirstPersonCharacter::OnFire);

	// Bind pickup event
	PlayerInputComponent->BindAction("PickupItem", IE_Pressed, this, &ATestFirstPersonCharacter::PickupItem);
	
	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

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

void ATestFirstPersonCharacter::OnFire()
{
	if(!CanFire())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
			FString::Printf(TEXT("!CanFire()")));
		return;
	}
	
	if(Weapon->IsAmmoEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
			FString::Printf(TEXT("AmmoEmpty()")));
		return;
	}
	
	Weapon->MakeShot();
	// try and play a firing animation if specified
	if (Weapon->FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(Weapon->FireAnimation, 1.f);
		}
	}
}

void ATestFirstPersonCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ATestFirstPersonCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void ATestFirstPersonCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

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


void ATestFirstPersonCharacter::PickupItem()
{
	if(GetWorld() != nullptr)
	{
		// drop item if player already have something in hands
		if(PickupActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan,
				FString::Printf(TEXT("Detaching PickupItem")));
			if(PickupActor->bIsWeapon)
			{
				if(Weapon->AmmoWidget)
					Weapon->AmmoWidget->SetVisibility(ESlateVisibility::Hidden);
				Weapon = nullptr;
			}
			PickupActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			PickupActor = nullptr;
			return;
		}

		// use LineTrace to pickup item in sight
		FHitResult OutHit;
		FVector Start = GetActorLocation();
		FVector ForwardVector = GetViewRotation().Vector();
		FVector End = ForwardVector * 500.f + Start;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		
		if(GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_WorldStatic, CollisionParams))
		{
			DrawDebugLine(GetWorld(), Start, End, OutHit.bBlockingHit ? FColor::Blue : FColor::Red, false,
				5.0f, 0, 2.0f);
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
				FString::Printf(TEXT("The Actor Being Hit is: %s"), *OutHit.Actor->GetName()));
			
			FVector Distance = Start - OutHit.Actor->GetActorLocation();
			if(!Cast<ABasePickup>(OutHit.Actor))
				return;
			
			PickupActor = Cast<ABasePickup>(OutHit.Actor);
			if(PickupActor->PickupDistance < Distance.Size())
			{
				// setup weapon and it's widget
				if(PickupActor && PickupActor->bIsWeapon)
				{
					Weapon = Cast<ABaseWeapon>(PickupActor);
					if(Weapon->AmmoWidget)
						Weapon->AmmoWidget->SetVisibility(ESlateVisibility::Visible);
				}
				PickupActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), PickupItemSocket);
			}
		}
	}
}

bool ATestFirstPersonCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATestFirstPersonCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ATestFirstPersonCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATestFirstPersonCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}

bool ATestFirstPersonCharacter::CanFire() const
{
	if(!PickupActor)
		return false;
	if(!Weapon)
		return false;
	return PickupActor->bIsWeapon;
}