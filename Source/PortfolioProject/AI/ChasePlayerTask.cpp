// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayerTask.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Monster/MeleeEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Monster/DoubleHitEnemy.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/AI/BlackBoardKeys.h"
#include "GameFramework/CharacterMovementComponent.h"

UChasePlayerTask::UChasePlayerTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("ChasePlayerTask");
}

EBTNodeResult::Type UChasePlayerTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//TargetLocation값을 AI컨트롤러의 BB에서 가져와서 PlayerLocation에 저장한다.
	AMeleeEnemyAIController* const Cont = Cast<AMeleeEnemyAIController>(OwnerComp.GetAIOwner());
	FVector const PlayerLocation = Cont->get_blackboard()->GetValueAsVector(bb_keys::target_location);
	ADoubleHitEnemy* const Enemy = Cast<ADoubleHitEnemy>(Cont->GetPawn());
	

	// 플레이어의 위치로 이동한다.
	if(!Enemy->IsDead)
	{
		Enemy->GetCharacterMovement()->MaxWalkSpeed = 600.f;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Cont,PlayerLocation);
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	//성공
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}