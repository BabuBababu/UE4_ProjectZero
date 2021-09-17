// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "ChasePlayerTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PORTFOLIOPROJECT_API UChasePlayerTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	public:
	UChasePlayerTask(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
