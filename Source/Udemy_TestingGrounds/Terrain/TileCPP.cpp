// Fill out your copyright notice in the Description page of Project Settings.

#include "TileCPP.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "Udemy_TestingGroundsGameMode.h"
#include "ActorPoolComponent.h"
#include "Engine/World.h"
#include "AI/Navigation/NavigationSystem.h"

// Sets default values
ATileCPP::ATileCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavigationBoundsOffset = FVector(2000, 0, 0);
}

template<class T>
void ATileCPP::RandomelyPlaceActors(TSubclassOf<T> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FSpawnTransform SpawnTransform;
		SpawnTransform.Scale = FMath::RandRange(MinScale, MaxScale);
		bool bFound = SearchEmptyLocation(SpawnTransform.Location, Radius*SpawnTransform.Scale);
		if (bFound)
		{
			SpawnTransform.Rotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnTransform);
		}
	}
}

void ATileCPP::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	RandomelyPlaceActors(ToSpawn, MinSpawn, MaxSpawn, Radius, MinScale, MaxScale);
}

void ATileCPP::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinSpawn, int MaxSpawn, float Radius)
{
	RandomelyPlaceActors(ToSpawn, MinSpawn, MaxSpawn, Radius, 1, 1);
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

void ATileCPP::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnTransform SpawnTransform)
{
	AActor* Spawned = GetWorld()->SpawnActor(ToSpawn);
	if (Spawned)
	{
		Spawned->SetActorRelativeLocation(SpawnTransform.Location);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		Spawned->SetActorRotation(FRotator(0, SpawnTransform.Rotation, 0));
		Spawned->SetActorScale3D(FVector(SpawnTransform.Scale));
	}
}

void ATileCPP::PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnTransform SpawnTransform)
{
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	if (Spawned)
	{
		Spawned->SetActorRelativeLocation(SpawnTransform.Location);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		Spawned->SetActorRotation(FRotator(0, SpawnTransform.Rotation, 0));
		Spawned->SetActorScale3D(FVector(SpawnTransform.Scale));
		Spawned->SpawnDefaultController();
		Spawned->Tags.Add(FName("Enemy"));
	}
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
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	GetWorld()->GetNavigationSystem()->Build();
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
	return !HasHit;
}
