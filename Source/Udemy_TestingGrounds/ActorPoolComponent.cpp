// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPoolComponent.h"


// Sets default values for this component's properties
UActorPoolComponent::UActorPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor * UActorPoolComponent::Checkout()
{
	if (PooledNavMesh == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Actor to checkout!"))
			return nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checkout."), *GetName())
	return PooledNavMesh;
}

void UActorPoolComponent::Return(AActor * ActorToReturn)
{
	if (ActorToReturn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Actor to return!"))
		return;
	}
	PooledNavMesh = ActorToReturn;
	UE_LOG(LogTemp, Warning, TEXT("[%s] Return."), *PooledNavMesh->GetName())
}

void UActorPoolComponent::Add(AActor * ActorToAdd)
{
	PooledNavMesh = ActorToAdd;
}
