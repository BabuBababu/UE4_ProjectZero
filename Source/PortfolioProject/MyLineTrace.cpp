// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLineTrace.h"
#include "PortfolioProjectCharacter.h"
#include "DoubleHitEnemy.h"
#include "OneHitEnemy.h"
#include "Engine/Engine.h"
#include "particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"


UMyLineTrace::UMyLineTrace()
{
	//파티클 시스템 
	static ConstructorHelpers::FObjectFinder<UParticleSystem>Blood_ParticleAdd(TEXT("/Game/Movable/WeaponAsset/WeaponEffects/P_body_bullet_impact"));
	Blood_Particle = Blood_ParticleAdd.Object;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Block_ParticleAdd(TEXT("/Game/Movable/WeaponAsset/WeaponEffects/P_AssaultRifle_IH"));
	Block_Particle =Block_ParticleAdd.Object;
	
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
	//히트 지점으로부터 10cm
	//라인트레이스 시작
	Player->GetWorld()->LineTraceSingleByChannel
	(
		HitResult,StartLoc,EndLoc,ECollisionChannel::ECC_PhysicsBody,Params
	);
	DrawDebugLine(Player->GetWorld(),StartLoc,EndLoc,FColor::Red,false,5.f,0,5.f);

	
	if(HitResult.GetActor()!=nullptr)
	{
		
		FVector HitLoc = HitResult.ImpactNormal*20.f+HitResult.ImpactPoint;
		auto DoubleEnemy = Cast<ADoubleHitEnemy>(HitResult.GetActor());
		auto OneEnemy = Cast<AOneHitEnemy>(HitResult.GetActor());
		if(DoubleEnemy)
		{
			UE_LOG(LogTemp, Warning, TEXT("SucceedCastDouble"));
			DrawDebugBox(Player->GetWorld(),HitResult.ImpactPoint,FVector(5,5,5),FColor::Yellow,false,2.f);
			UGameplayStatics::SpawnEmitterAtLocation(Player->GetWorld(),Blood_Particle,HitLoc,FRotator(0.f,0.f,0.f),FVector(3),true,EPSCPoolMethod::None,true);
		
		}
		else if (OneEnemy)
		{
			DrawDebugBox(Player->GetWorld(),HitResult.ImpactPoint,FVector(5,5,5),FColor::Blue,false,2.f);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FailedCast"));
			//GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("LOCATION: %s"),*HitLoc.ToString()));
			DrawDebugBox(Player->GetWorld(),HitResult.ImpactPoint,FVector(5,5,5),FColor::Purple,false,2.f);
			UGameplayStatics::SpawnEmitterAtLocation(Player->GetWorld(),Block_Particle,HitLoc,FRotator(0.f,0.f,0.f),FVector(2),true,EPSCPoolMethod::None,true);
		
		}
	}

	
}


//스킬1 라인트레이스도 위에 onfire함수 그대로 사용해서 만들어보자!