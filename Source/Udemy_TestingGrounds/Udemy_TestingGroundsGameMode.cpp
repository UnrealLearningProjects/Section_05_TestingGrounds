// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Udemy_TestingGroundsGameMode.h"
#include "Player/Udemy_TestingGroundsHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "ActorPoolComponent.h"

AUdemy_TestingGroundsGameMode::AUdemy_TestingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Character/Character_Blueprints/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUdemy_TestingGroundsHUD::StaticClass();

	PoolComponent = CreateDefaultSubobject<UActorPoolComponent>(TEXT("ActorPoolComponent"));
}

void AUdemy_TestingGroundsGameMode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}


}

void AUdemy_TestingGroundsGameMode::AddToPool(ANavMeshBoundsVolume* BoundsToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Found Actor: %s"), *BoundsToAdd->GetName())
}
