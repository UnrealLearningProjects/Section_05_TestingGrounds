// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypointCPP.h"
#include "AIController.h"
#include "PatrollingGuardCPP.h" //TODO remove coupling
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypointCPP::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//Get Patrol points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuardCPP>(ControlledPawn);
	Patrollpoints = PatrollingGuard->WayPoints;
	
	//Set next Waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, Patrollpoints[Index]);
	
	//TODO protect against empty parol routes

	//Cycle the Index
	auto NextIndex = (Index+1) % Patrollpoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);


	//UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i"), Index);
	return EBTNodeResult::Succeeded;

}

TArray<AActor*> UChooseNextWaypointCPP::GetWaypoints(APawn* ControlledPawn)
{
	
	return TArray<AActor*>();
}
