// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "DoubleHitEnemy.h"
#include "MeleeAttackTask.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UMeleeAttackTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	public:
	UMeleeAttackTask(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	private:
	bool MontageHasFinished(ADoubleHitEnemy* const Enemy);
};
