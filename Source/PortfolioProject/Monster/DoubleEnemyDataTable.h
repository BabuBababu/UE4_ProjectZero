#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"


#include "DoubleEnemyDataTable.generated.h"

USTRUCT(BlueprintType)
struct FDoubleEnemyDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

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

	//애니메이션경로
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString D_AnimName;

};
