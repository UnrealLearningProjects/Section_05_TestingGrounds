// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Udemy_TestingGroundsGameMode.h"
#include "Player/Udemy_TestingGroundsHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUdemy_TestingGroundsGameMode::AUdemy_TestingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Character/Character_Blueprints/TP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUdemy_TestingGroundsHUD::StaticClass();
}
