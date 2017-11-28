// Fill out your copyright notice in the Description page of Project Settings.

#include "TileCPP.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATileCPP::ATileCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATileCPP::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnLocation;
		bool bFound = SearchEmptyLocation(SpawnLocation, Radius);
		if (bFound)
		{
			PlaceActor(ToSpawn, SpawnLocation);
		}		
	}
}

bool ATileCPP::SearchEmptyLocation(FVector& OutLocation, float Radius)
{
	FVector Min = FVector(0, -2000, 0);
	FVector Max = FVector(4000, 2000, 0);
	FBox Bounds = FBox(Min, Max);
	const int MaxLoops = 100;
	for (size_t i = 0; i < MaxLoops; i++)
	{
		FVector SpawnLocation = FMath::RandPointInBox(Bounds);
		if (CanSpawn(SpawnLocation, Radius))
		{
			OutLocation = SpawnLocation;
			return true;
		}
	}
	return false;
}

void ATileCPP::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint)
{
	AActor* Spawned = GetWorld()->SpawnActor(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

// Called when the game starts or when spawned
void ATileCPP::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATileCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATileCPP::CanSpawn(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, 
		GlobalLocation, 
		GlobalLocation, 
		FQuat::Identity, 
		ECollisionChannel::ECC_GameTraceChannel2, 
		FCollisionShape::MakeSphere(Radius)
	);
	if (HasHit)
	{
	DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, FColor(200, 0, 0, 0), true);
	}
	else
	{
		DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, FColor(0, 200, 0, 0), true);
	}
	return !HasHit;
}
