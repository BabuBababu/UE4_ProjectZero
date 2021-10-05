// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeleeEnemyAIController.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Animation/AnimInstance.h"
#include "Components/WidgetComponent.h"
#include "DoubleHitEnemy.generated.h"

//
// USTRUCT()
// struct FDoubleHitEnemyData : public FTableRowBase
// {
// 	GENERATED_BODY()
//
// 	
// 	
// 	
// };

class UParticleSystem;

UCLASS()
class PORTFOLIOPROJECT_API ADoubleHitEnemy : public ACharacter
{
	GENERATED_BODY()

	

public:
	// Sets default values for this character's properties
	ADoubleHitEnemy();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
	USkeletalMeshComponent* SkeletalMesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UWidgetComponent* EnemyWidget;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USphereComponent* LHand;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USphereComponent* RHand;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetEnemy(FName EnemyName);
	void MyReceiveDamage(float damage, FName boneName, AActor* DamageCauser);
	void Death();
	//데이터 테이블 행
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMeleeEnemyAIController* EnemyAI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ADoubleHitEnemy* EnemyCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName DefaultEnemyName = "Hulk";
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName RandomName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BodyX;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BodyY;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float HandRdius;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector LHandFLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector RHandFLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector WidgetFLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector EnemyLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRotator EnemyRotation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector EnemyScale;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString AnimName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class UAnimInstance> HulkAnimInstance;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class UAnimInstance> ParasiteAnimInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> EnemyWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* EnemyWidget_UI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* EnemyDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PlayerFound;
};
