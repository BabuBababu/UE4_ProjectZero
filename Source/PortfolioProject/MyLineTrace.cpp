// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLineTrace.h"
#include "PortfolioProjectCharacter.h"
#include "DoubleHitEnemy.h"
#include "OneHitEnemy.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"


UMyLineTrace::UMyLineTrace()
{
}

void UMyLineTrace::OnFire(APortfolioProjectCharacter* Player)
{
	//APawn* const PlayerController = Cast<APawn>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	FQuat Rotate= FQuat(Player->GetControlRotation());
	//사격 시작지점
	FVector CameraLoc = Player->SpringArm->GetComponentLocation();
	FVector StartLoc = CameraLoc;
	//카메라 회전값 * 카메라의 포워드벡터 = 사격 방향
	FVector TempForward =Rotate.GetForwardVector();
	//사격 끝지점
	FVector EndLoc = CameraLoc + (TempForward*20000.f); //사거리 2km
	FHitResult HitResult;
	//무시할 오브젝트
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Player);

	//라인트레이스 시작
	Player->GetWorld()->LineTraceSingleByChannel
	(
		HitResult,StartLoc,EndLoc,ECollisionChannel::ECC_PhysicsBody,Params
	);
	DrawDebugLine(Player->GetWorld(),StartLoc,EndLoc,FColor::Red,false,5.f,0,5.f);
		
	if(HitResult.GetActor()!=nullptr)
	{
		auto DoubleEnemy = Cast<ADoubleHitEnemy>(HitResult.GetActor());
		auto OneEnemy = Cast<AOneHitEnemy>(HitResult.GetActor());
		if(DoubleEnemy)
		{
			UE_LOG(LogTemp, Warning, TEXT("SucceedCastDouble"));
			DrawDebugBox(Player->GetWorld(),HitResult.ImpactPoint,FVector(5,5,5),FColor::Yellow,false,2.f);
		}
		else if (OneEnemy)
		{
			DrawDebugBox(Player->GetWorld(),HitResult.ImpactPoint,FVector(5,5,5),FColor::Blue,false,2.f);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FailedCast"));
			DrawDebugBox(Player->GetWorld(),HitResult.ImpactPoint,FVector(5,5,5),FColor::Purple,false,2.f);
		}
	}

	
}
