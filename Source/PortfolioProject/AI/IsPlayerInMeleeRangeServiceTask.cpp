// Fill out your copyright notice in the Description page of Project Settings.


#include "IsPlayerInMeleeRangeServiceTask.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Monster/MeleeEnemyAIController.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Monster/DoubleHitEnemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/AI/BlackBoardKeys.h"

UIsPlayerInMeleeRangeServiceTask::UIsPlayerInMeleeRangeServiceTask()
{
	bNotifyBecomeRelevant =true;
	NodeName = TEXT("IsPlayerInMeleeRange");
}

void UIsPlayerInMeleeRangeServiceTask::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(owner_comp, NodeMemory);

	AMeleeEnemyAIController* const Cont = Cast<AMeleeEnemyAIController>(owner_comp.GetAIOwner());
	ADoubleHitEnemy* const Enemy = Cast<ADoubleHitEnemy>(Cont->GetPawn());

	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"),Enemy->GetDistanceTo(Player)));
	

	Cont->get_blackboard()->SetValueAsBool(bb_keys::player_is_in_melee_range,Enemy->GetDistanceTo(Player) <= MeleeRange);

	if(bb_keys::player_is_in_melee_range)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("range is true!"));
	}
}
