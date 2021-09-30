// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttackTask.h"
#include "MeleeEnemyAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UMeleeAttackTask::UMeleeAttackTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("MeleeAttack");
}

EBTNodeResult::Type UMeleeAttackTask::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* NodeMemory)
{
	AMeleeEnemyAIController* const Cont = Cast<AMeleeEnemyAIController>(owner_comp.GetAIOwner());
	ADoubleHitEnemy* const Enemy = Cast<ADoubleHitEnemy>(Cont->GetPawn());
	Enemy->Attack = true;
	
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UMeleeAttackTask::MontageHasFinished(ADoubleHitEnemy* const Enemy)
{
	return false;
}
