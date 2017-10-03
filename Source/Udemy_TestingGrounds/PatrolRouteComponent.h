// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRouteComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEMY_TESTINGGROUNDS_API UPatrolRouteComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	TArray<AActor*> GetWaypointArray() const;

private:
	UPROPERTY(EditAnywhere, Category = "Patrol Route|Cplusplus")
	TArray<AActor*> WayPoints;

};
