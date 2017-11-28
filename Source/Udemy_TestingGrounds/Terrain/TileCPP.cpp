// Fill out your copyright notice in the Description page of Project Settings.

#include "TileCPP.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATileCPP::ATileCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATileCPP::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn)
{
	FVector Min = FVector(0, -2000, 0);
	FVector Max = FVector(4000, 2000, 0);
	FBox Bounds = FBox(Min, Max);
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnLocation = FMath::RandPointInBox(Bounds);
		AActor* Spawned = GetWorld()->SpawnActor(ToSpawn);
		Spawned->SetActorRelativeLocation(SpawnLocation);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative,false));
		
	}
	

}

// Called when the game starts or when spawned
void ATileCPP::BeginPlay()
{
	Super::BeginPlay();
	SphereCast(FVector(0, 0, 0), 200);
	SphereCast(FVector(0, 0, 1000), 200);
}

// Called every frame
void ATileCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATileCPP::SphereCast(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, Location, Location, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	if (HasHit)
	{
	DrawDebugSphere(GetWorld(), Location, Radius, 32, FColor(200, 0, 0, 0), true);
	}
	else
	{
		DrawDebugSphere(GetWorld(), Location, Radius, 32, FColor(0, 200, 0, 0), true);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.ToString())
	return HasHit;
}
