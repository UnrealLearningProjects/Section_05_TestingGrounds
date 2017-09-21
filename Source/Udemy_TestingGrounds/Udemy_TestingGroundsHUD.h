// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Udemy_TestingGroundsHUD.generated.h"

UCLASS()
class AUdemy_TestingGroundsHUD : public AHUD
{
	GENERATED_BODY()

public:
	AUdemy_TestingGroundsHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

