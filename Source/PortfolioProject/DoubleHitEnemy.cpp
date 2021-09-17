// Fill out your copyright notice in the Description page of Project Settings.


#include "DoubleHitEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DoubleEnemyDataTable.h"
#include "math.h"
#include "MeleeEnemyAIController.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ADoubleHitEnemy::ADoubleHitEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	RootComponent = GetCapsuleComponent();
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	EnemyWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	LHand = CreateDefaultSubobject<USphereComponent>(TEXT("LHand"));
	RHand = CreateDefaultSubobject<USphereComponent>(TEXT("RHand"));
	
	
	//DataTable 초기화
	static ConstructorHelpers::FObjectFinder<UDataTable> DoubleHitEnemyDataObject(TEXT("/Game/Movable/DataTable/DoubleHitEnemyDataTable"));
	if(DoubleHitEnemyDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
		EnemyDataTable = DoubleHitEnemyDataObject.Object;
	}

	SkeletalMesh->SetSkeletalMesh(SMesh); //팔 붙이기 위해 임시로 아무거나 넣어두기
	EnemyWidget->SetupAttachment(RootComponent);
	SkeletalMesh->SetupAttachment(RootComponent);
	LHand->SetupAttachment(SkeletalMesh,TEXT("LeftHand"));
	RHand->SetupAttachment(SkeletalMesh,TEXT("RightHand"));

	
	
	//애님인스턴스 전부 선언
	//static ConstructorHelpers::FClassFinder<UAnimInstance> AnimObj((TEXT("%s"),*AnimName));
	
	static ConstructorHelpers::FClassFinder<UAnimInstance> HulkAnimObj(TEXT("/Game/Movable/ZombieAsset/Hulk/Animation/CPP_Hulk_Anim"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> ParasiteAnimObj(TEXT("/Game/Movable/ZombieAsset/Parasite/ZombieAnimation/CPP_Parasite_Anim"));


	if(HulkAnimObj.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hulk AnimInstance Succeed!"));
		HulkAnimInstance = HulkAnimObj.Class;
	}
	if(HulkAnimObj.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Parasite AnimInstance Succeed!"));
		ParasiteAnimInstance = ParasiteAnimObj.Class;
	}
	
	//AI컨트롤러 초기화
	AIControllerClass = AMeleeEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	//UE_LOG(LogTemp, Warning, TEXT("InitRandomName: %s"),*RandomName.ToString());

}

// Called when the game starts or when spawned
void ADoubleHitEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	//좀비 랜덤으로 이름을 선택
	auto List = EnemyDataTable->GetRowNames();
	RandomName = List[FMath::RandRange(0,1)];
	FDoubleEnemyDataTable* EnemyData = EnemyDataTable->FindRow<FDoubleEnemyDataTable>(RandomName,FString(""));

	
	//이름에 의한 좀비 초기화
	SetEnemy(RandomName);
	UE_LOG(LogTemp, Warning, TEXT("BeginplayRandomName: %s"),*RandomName.ToString());
	//데이터테이블 적용
	SkeletalMesh->SetSkeletalMesh(SMesh);
	SkeletalMesh->SetRelativeLocation(EnemyLocation);
	SkeletalMesh->SetRelativeRotation(EnemyRotation);
	SkeletalMesh->SetRelativeScale3D(EnemyScale);
	GetCapsuleComponent()->InitCapsuleSize(BodyX, BodyY);
	LHand->InitSphereRadius(HandRdius);
	LHand->SetRelativeLocation(LHandFLocation);
	RHand->InitSphereRadius(HandRdius);
	RHand->SetRelativeLocation(RHandFLocation);
	EnemyWidget->SetRelativeLocation(WidgetFLocation);
	EnemyWidget->SetRelativeRotation(FRotator(0.0f,0.0f,0.0f));
	EnemyWidget->SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));
	//손 붙이기
	//애니메이션 설정
	if (DefaultEnemyName == "Hulk")
	{
		SkeletalMesh->SetAnimInstanceClass(HulkAnimInstance);
	}
	else if (DefaultEnemyName == "Parasite")
	{
		SkeletalMesh->SetAnimInstanceClass(ParasiteAnimInstance);
	}
	
	//GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("%s"),AnimName));
	if(DefaultEnemyName == "Parasite")
	{
		UE_LOG(LogTemp, Warning, TEXT("Name Parasite Okay!"));
	}
	else if (DefaultEnemyName == "Hulk")
	{
		UE_LOG(LogTemp, Warning, TEXT("Name Hulk Okay!"));
	}
	
}

// Called every frame
void ADoubleHitEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 void ADoubleHitEnemy::SetEnemy(FName EnemyName)
 {
 	FDoubleEnemyDataTable* EnemyData = EnemyDataTable->FindRow<FDoubleEnemyDataTable>(EnemyName,FString(""));
 	if(EnemyData)
 	{
 		UE_LOG(LogTemp, Warning, TEXT("EnemyData Succeed!"));
 		DefaultEnemyName = EnemyName;
 		MaxHealth = EnemyData->D_MaxHP;
 		SMesh = EnemyData->D_Mesh;
 		BodyX = EnemyData->D_BodyX;
 		BodyY = EnemyData->D_BodyY;
 		HandRdius = EnemyData->D_HandRdius;
 		LHandFLocation = EnemyData->D_LHandFLocation;
 		RHandFLocation = EnemyData->D_RHandFLocation;
 		WidgetFLocation = EnemyData->D_WidgetFLocation;
 		EnemyLocation = EnemyData->D_Location;
 		EnemyRotation = EnemyData->D_Rotation;
 		EnemyScale = EnemyData->D_Scale;
 		Damage = EnemyData->D_Damage;
 		AnimName= EnemyData->D_AnimName;
 		
 	}



 
 }

void ADoubleHitEnemy::MyReceiveDamage(float damage, FName boneName, AActor* DamageCauser)
{
	if (boneName == TEXT("Head")|| boneName == TEXT("Spine2"))
	{
		damage *= 2;
	}
	CyrrentHealth -= damage;
	if (CyrrentHealth <= 0)
	{
		Death();
	}
}

void ADoubleHitEnemy::Death()
{
	//UE_LOG(LogTemp, Warning, TEXT("DoubleHitEnemy_Die!"));
}

