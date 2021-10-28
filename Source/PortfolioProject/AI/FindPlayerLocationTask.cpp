// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocationTask.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Monster/MeleeEnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Monster/DoubleHitEnemy.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/AI/BlackBoardKeys.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Player/PortfolioProjectCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UFindPlayerLocationTask::UFindPlayerLocationTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("FindPlayerLocation");
}

EBTNodeResult::Type UFindPlayerLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//ACharacter* player = Cast<ACharacter>(GetWorld()->GetFirstPlayerController());
	//player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);

	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	auto const Cont = Cast<AMeleeEnemyAIController>(OwnerComp.GetAIOwner());
	ADoubleHitEnemy* const Enemy = Cast<ADoubleHitEnemy>(Cont->GetPawn());
	

	FVector const Player_Location = Player->GetActorLocation();
	if(!Enemy->IsDead)
	{
		if(search_random)
		{
			FNavLocation loc;
			//플레이어 근처의 임의의 지점으로 이동한다.
			UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
			if(nav_sys->GetRandomPointInNavigableRadius(Player_Location,search_radius,loc,nullptr))
			{
				Cont->get_blackboard()->SetValueAsVector(bb_keys::target_location,loc.Location);
			}

		
		}
		else
		{
			Cont->get_blackboard()->SetValueAsVector(bb_keys::target_location,Player_Location);
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
