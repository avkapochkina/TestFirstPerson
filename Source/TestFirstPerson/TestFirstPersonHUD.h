// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TestFirstPersonHUD.generated.h"

UCLASS()
class ATestFirstPersonHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATestFirstPersonHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

