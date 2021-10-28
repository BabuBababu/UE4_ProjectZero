// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemyAIController.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Monster/DoubleHitEnemy.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/AI/BlackBoardKeys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "EngineGlobals.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Player/PortfolioProjectCharacter.h"


const FName AMeleeEnemyAIController::HomePosKey(TEXT("HomePos"));
const FName AMeleeEnemyAIController::TargetLocation(TEXT("TargetLocation"));

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
	//Perception초기화
	SetPerceptionSystem();
	
	
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

void AMeleeEnemyAIController::OnUpdated(TArray<AActor*> const& updated_actors)
{
}

void AMeleeEnemyAIController::OnTargetDetected(AActor* actor, FAIStimulus const Stimulus)
{
	if (auto const player = Cast<APortfolioProjectCharacter>(actor))
	{
		//성공적으로 감지하면 블랙보드에 true값을 넣어준다.
		get_blackboard()->SetValueAsBool(bb_keys::can_see_player,Stimulus.WasSuccessfullySensed());
	}
}

void AMeleeEnemyAIController::SetPerceptionSystem()
{
	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception")));
	

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = SightConfig->SightRadius+AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = AILastSeenLocation;
	
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this,&AMeleeEnemyAIController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

