// Fill out your copyright notice in the Description page of Project Settings.

#include "TileCPP.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "Udemy_TestingGroundsGameMode.h"
#include "ActorPoolComponent.h"


// Sets default values
ATileCPP::ATileCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATileCPP::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	float RandomScale = FMath::RandRange(MinScale, MaxScale);
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnLocation;
		bool bFound = SearchEmptyLocation(SpawnLocation, Radius*RandomScale);
		if (bFound)
		{
			PlaceActor(ToSpawn, SpawnLocation, RandomScale);
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

void ATileCPP::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float RandomScale)
{
	AActor* Spawned = GetWorld()->SpawnActor(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, FMath::RandRange(-180, 180), 0));
	Spawned->SetActorScale3D(FVector(RandomScale));
}

// Called when the game starts or when spawned
void ATileCPP::BeginPlay()
{
	Super::BeginPlay();

	SetPoolComponentReference();
}

void ATileCPP::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ActorPoolReference == nullptr)
	{
		return;
	}
	ActorPoolReference->Return(NavMeshBoundsVolume);
	UE_LOG(LogTemp, Warning, TEXT("Returned [%s]"), *NavMeshBoundsVolume->GetName())
}

// Called every frame
void ATileCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileCPP::SetPoolComponentReference()
{
	auto Gamemode = (AUdemy_TestingGroundsGameMode*)GetWorld()->GetAuthGameMode();
	ActorPoolReference = Gamemode->PoolComponent;
	UE_LOG(LogTemp, Warning, TEXT("PoolReference: %s"), *ActorPoolReference->GetName())

	PositionNavMeshBoundsVolume();
}

void ATileCPP::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = ActorPoolReference->Checkout();
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Enough Actors in Pool!"))
			return;
	}
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation());
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
