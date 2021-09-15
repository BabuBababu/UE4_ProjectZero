// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindPatrolPosTask.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UFindPatrolPosTask : public UBTTaskNode
{
	GENERATED_BODY()
	
	public:
	UFindPatrolPosTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
	float search_radius = 1500.f;
};
