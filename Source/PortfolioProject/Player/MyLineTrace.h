// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyLineTrace.generated.h"

/**
 * 
*/
UCLASS()
class PORTFOLIOPROJECT_API UMyLineTrace : public UObject
{
	GENERATED_BODY()

	public:
	UMyLineTrace();
	void OnFire(class APortfolioProjectCharacter* Player);

	UPROPERTY(EditAnywhere,Category="Blood Particle Effects")
	UParticleSystem* Blood_Particle;
	UPROPERTY(EditAnywhere,Category="Block Particle Effects")
	UParticleSystem* Block_Particle;
		
};