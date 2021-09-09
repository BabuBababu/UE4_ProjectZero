// Fill out your copyright notice in the Description page of Project Settings.


#include "DoubleHitEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ADoubleHitEnemy::ADoubleHitEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = GetCapsuleComponent();
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	EnemyWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	LHand = CreateDefaultSubobject<USphereComponent>(TEXT("LHand"));
	RHand = CreateDefaultSubobject<USphereComponent>(TEXT("RHand"));
	
	
	//DataTable 초기화
	static ConstructorHelpers::FObjectFinder<UDataTable> DoubleHitEnemyDataObject(TEXT("/Game/Movable/DataTable/DoubleHitEnemyDataTable"));
	if(DoubleHitEnemyDataObject.Succeeded())
	{
		EnemyDataTable = DoubleHitEnemyDataObject.Object;
	}
	
	// 좀비 이름에 의한 랜덤화
	SetEnemy("Hulk");
	
	EnemyWidget->SetupAttachment(RootComponent);
	SkeletalMesh->SetupAttachment(RootComponent);
	LHand->SetupAttachment(SkeletalMesh,TEXT("LeftHand"));
	RHand->SetupAttachment(SkeletalMesh,TEXT("RightHand"));
	
	//데이터테이블 적용
	SkeletalMesh->SetSkeletalMesh(SMesh);
	SkeletalMesh->SetRelativeLocation(EnemyLocation);
	SkeletalMesh->SetRelativeRotation(EnemyRotation);
	SkeletalMesh->SetRelativeScale3D(EnemyScale);
	
	UClass* tempClass = AnimBP->GetClass();
	if(AnimBP->GetClass())
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimClass Succeed!"));
	}
	SkeletalMesh->SetAnimInstanceClass(tempClass);

}

// Called when the game starts or when spawned
void ADoubleHitEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoubleHitEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 void ADoubleHitEnemy::SetEnemy(FName EnemyName)
 {
 	FDoubleHitEnemyData* EnemyData = EnemyDataTable->FindRow<FDoubleHitEnemyData>(EnemyName,FString(""));
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
 		AnimBP = EnemyData->D_AnimBP;
 		Damage = EnemyData->D_Damage;
 		
 	}



 	GetCapsuleComponent()->InitCapsuleSize(BodyX, BodyY);
 	LHand->InitSphereRadius(HandRdius);
 	LHand->SetRelativeLocation(LHandFLocation);
 	RHand->InitSphereRadius(HandRdius);
 	RHand->SetRelativeLocation(RHandFLocation);
 	EnemyWidget->SetRelativeLocation(WidgetFLocation);
 	EnemyWidget->SetRelativeRotation(FRotator(0.0f,0.0f,0.0f));
 	EnemyWidget->SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));
 }

