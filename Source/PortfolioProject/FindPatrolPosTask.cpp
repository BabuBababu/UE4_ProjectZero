// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPatrolPosTask.h"
#include "MeleeEnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BlackBoardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"


UFindPatrolPosTask::UFindPatrolPosTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("FindPatrolPosTask");
}




EBTNodeResult::Type UFindPatrolPosTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	auto Controller = Cast<AMeleeEnemyAIController>(OwnerComp.GetAIOwner());
	auto Enemy = Controller->GetPawn();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("success!"));
	//
	if (nullptr == Enemy) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy Initialize faild!"));
		return EBTNodeResult::Failed;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("1success!"));
	//
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nullptr == NavSystem) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Enemy in Navi"));
		return EBTNodeResult::Failed;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("2success!"));
	//
	FVector const Origin = Enemy->GetActorLocation();
	FNavLocation NextPatrol;

	//NextPatrol변수에 임의의 location 데이터를 넣고 다시 TargetLocation키의 value에 값을 넣어준다.
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, search_radius, NextPatrol,nullptr))
	{
		Controller->get_blackboard()->SetValueAsVector(AMeleeEnemyAIController::TargetLocation, NextPatrol.Location);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NextPosSuccess!"));
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s"),*NextPatrol.Location.ToString()));
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}