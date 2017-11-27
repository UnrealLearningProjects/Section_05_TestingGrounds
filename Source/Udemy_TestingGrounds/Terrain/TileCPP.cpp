// Fill out your copyright notice in the Description page of Project Settings.

#include "TileCPP.h"


// Sets default values
ATileCPP::ATileCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATileCPP::PlaceActors()
{
	auto SpawnLocation1 = FMath::RandPointInBox(FBox(FVector(0, -2000, 100), FVector(4000, 2000, 100)));
	auto SpawnLocation2 = FMath::RandPointInBox(FBox(FVector(0, -2000, 100), FVector(4000, 2000, 100)));
	UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *SpawnLocation1.ToString(), *SpawnLocation2.ToString());
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

