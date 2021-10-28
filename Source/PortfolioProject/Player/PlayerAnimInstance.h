// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"
/**
 * 
 */

UCLASS(Transient,Blueprintable,HideCategories=AnimInstance,BlueprintType)
class UPlayerAnimInstance: public UAnimInstance
{
	GENERATED_BODY()
public:
	UPlayerAnimInstance();

	
};
