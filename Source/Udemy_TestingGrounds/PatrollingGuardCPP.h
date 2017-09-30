// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuardCPP.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_TESTINGGROUNDS_API APatrollingGuardCPP : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Patrol Route|Cplusplus")
		TArray<AActor*> WayPoints;
	
	
};
