// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypointCPP.h"
#include "AIController.h"
#include "PatrolRouteComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypointCPP::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//TODO protect against no Patrol Route Component
	//TODO protect against empty parol routes

	//Get Patrol Route
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRouteComponent>();
	if (!ensure(PatrolRoute)){return EBTNodeResult::Failed;}

	
	Patrolpoints = PatrolRoute->GetWaypointArray();
	if (Patrolpoints.Num()==0){return EBTNodeResult::Failed;}
	
	//Set next Waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, Patrolpoints[Index]);
	
	

	//Cycle the Index
	auto NextIndex = (Index+1) % Patrolpoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);


	//UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i"), Index);
	return EBTNodeResult::Succeeded;

}