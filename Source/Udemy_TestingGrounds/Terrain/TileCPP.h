// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileCPP.generated.h"


UCLASS()
class UDEMY_TESTINGGROUNDS_API ATileCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileCPP();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);

	bool SearchEmptyLocation(FVector& SpawnLocation, float Radius);

protected:
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float RandomScale);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	class AUdemy_TestingGroundsGameMode* Gamemode;

	void SetPoolComponentReference();



private:
	AActor* NavMeshBoundsVolume;
	void PositionNavMeshBoundsVolume();
	bool CanSpawn(FVector Location, float Radius);
	class UActorPoolComponent* ActorPoolReference;
	
};
