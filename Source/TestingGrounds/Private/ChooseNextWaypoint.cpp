// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/ChooseNextWaypoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("DONKEY IS UP IN SHREK"));
	return EBTNodeResult::Succeeded;
}
