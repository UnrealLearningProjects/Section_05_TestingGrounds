// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Udemy_TestingGroundsGameMode.h"
#include "Udemy_TestingGroundsHUD.h"
#include "Udemy_TestingGroundsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUdemy_TestingGroundsGameMode::AUdemy_TestingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUdemy_TestingGroundsHUD::StaticClass();
}
