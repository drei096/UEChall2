// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UEChall2HUD.generated.h"

UCLASS()
class AUEChall2HUD : public AHUD
{
	GENERATED_BODY()

public:
	AUEChall2HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

