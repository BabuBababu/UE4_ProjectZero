// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Components/WidgetComponent.h"
#include "DoubleHitEnemy.generated.h"


USTRUCT()
struct FDoubleHitEnemyData : public FTableRowBase
{
	GENERATED_BODY()

	//이름
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString D_DoubleHitEnemyName;
	//HP
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float D_CurrentHP;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float D_MaxHP;
	//Damage
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float D_Damage;

	//메쉬
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USkeletalMesh* D_Mesh;
	//본체,양손 구 컴포넌트
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float D_BodyX;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float D_BodyY;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float D_HandRdius;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector D_LHandFLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector D_RHandFLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector D_WidgetFLocation;
	//위치
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector D_Location;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRotator D_Rotation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector D_Scale;

	//애니메이션BP
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UAnimBlueprint* D_AnimBP;
	
	
	
};

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
	//데이터 테이블 행
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CyrrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName DefaultEnemyName = "Hulk";
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
	UAnimBlueprint* AnimBP;
	
	
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
