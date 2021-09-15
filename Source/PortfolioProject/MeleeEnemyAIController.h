// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MeleeEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API AMeleeEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
	public:
	AMeleeEnemyAIController(FObjectInitializer const& object_initializer);
	void BeginPlay() override;
	void OnPossess(APawn* pawn) override;

	class UBlackboardComponent* get_blackboard() const;

	private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* behavior_tree_component;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* btree;

	class UBlackboardComponent* blackboard;

	public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;
};
