// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPatrolPosTask.h"
#include "MeleeEnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EngineGlobals.h"


UFindPatrolPosTask::UFindPatrolPosTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("FindPatrolPosTask");
}




EBTNodeResult::Type UFindPatrolPosTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	auto Controller = Cast<AMeleeEnemyAIController>(OwnerComp.GetAIOwner());
	auto boss = Controller->GetPawn();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("success!"));
	//
	if (nullptr == boss) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Boss Initialize faild!"));
		return EBTNodeResult::Failed;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("1success!"));
	//
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nullptr == NavSystem) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Boss in Navi"));
		return EBTNodeResult::Failed;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("2success!"));
	//
	FVector const Origin = boss->GetActorLocation();
	FNavLocation NextPatrol;
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, search_radius, NextPatrol,nullptr))
	{
		Controller->get_blackboard()->SetValueAsVector(AMeleeEnemyAIController::PatrolPosKey, NextPatrol.Location);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NextPosSuccess!"));
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s"),*NextPatrol.Location.ToString()));
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}