// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEChall2GameMode.h"
#include "UEChall2HUD.h"
#include "UEChall2Character.h"
#include "UObject/ConstructorHelpers.h"

AUEChall2GameMode::AUEChall2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUEChall2HUD::StaticClass();
}
