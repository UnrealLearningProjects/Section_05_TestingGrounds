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
	if (Pool.Num() == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("No Actor to checkout!"))
			return nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checkout."), *GetName())
	return Pool.Pop();
}

void UActorPoolComponent::Return(AActor * ActorToReturn)
{
	if (ActorToReturn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Actor to return!"))
		return;
	}
	Pool.Push(ActorToReturn);
	UE_LOG(LogTemp, Warning, TEXT("[%s] Return."), *ActorToReturn->GetName())
}

void UActorPoolComponent::Add(AActor * ActorToAdd)
{
	if (ActorToAdd == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Actor to add!"))
			return;
	}
	Pool.Push(ActorToAdd);
	UE_LOG(LogTemp, Warning, TEXT("[%s] add."), *ActorToAdd->GetName())
}
