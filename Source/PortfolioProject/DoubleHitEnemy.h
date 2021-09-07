// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DoubleHitEnemy.generated.h"




class UParticleSystem;

UCLASS()
class PORTFOLIOPROJECT_API ADoubleHitEnemy : public ACharacter
{
	GENERATED_BODY()

	

public:
	// Sets default values for this character's properties
	ADoubleHitEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CyrrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PlayerFound;

};
