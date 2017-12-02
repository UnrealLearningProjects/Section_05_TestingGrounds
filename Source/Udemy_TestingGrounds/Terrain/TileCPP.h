// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileCPP.generated.h"

USTRUCT()
struct FSpawnTransform
{
	GENERATED_BODY()

	FVector Location;
	float Rotation;
	float Scale;

};


UCLASS()
class UDEMY_TESTINGGROUNDS_API ATileCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileCPP();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinSpawn, int MaxSpawn, float Radius);

	bool SearchEmptyLocation(FVector& SpawnLocation, float Radius);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	class AUdemy_TestingGroundsGameMode* Gamemode;

	void SetPoolComponentReference();



private:
	template<class T>
	void RandomelyPlaceActors(TSubclassOf<T> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnTransform SpawnTransform);
	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnTransform SpawnTransform);

	AActor* NavMeshBoundsVolume;
	void PositionNavMeshBoundsVolume();
	bool CanSpawn(FVector Location, float Radius);
	class UActorPoolComponent* ActorPoolReference;
};


