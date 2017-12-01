// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Udemy_TestingGroundsGameMode.generated.h"

UCLASS(minimalapi)
class AUdemy_TestingGroundsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUdemy_TestingGroundsGameMode();

	UFUNCTION(BlueprintCallable)
	void PopulateBoundsVolumePool();

	void AddToPool(class ANavMeshBoundsVolume* BoundsToAdd);

	class UActorPoolComponent* PoolComponent;
};



