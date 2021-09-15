// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemyAIController.h"
#include "DoubleHitEnemy.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EngineGlobals.h"


const FName AMeleeEnemyAIController::HomePosKey(TEXT("HomePos"));
const FName AMeleeEnemyAIController::PatrolPosKey(TEXT("PatrolPos"));

AMeleeEnemyAIController::AMeleeEnemyAIController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/Movable/AI/BT_MeleeEnemy.BT_MeleeEnemy'"));
	if (BTObject.Succeeded())
	{
		btree = BTObject.Object;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BT Connected!"));
	}
	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

}

void AMeleeEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(btree);
	behavior_tree_component->StartTree(*btree);
}

void AMeleeEnemyAIController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}

}

UBlackboardComponent* AMeleeEnemyAIController::get_blackboard() const
{
	return blackboard;
}
