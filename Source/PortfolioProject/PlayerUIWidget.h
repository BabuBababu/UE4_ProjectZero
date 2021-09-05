// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UPlayerUIWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
		virtual void NativeConstruct() override;
	public:
		UFUNCTION(BlueprintCallable)
		UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

		UFUNCTION(BlueprintCallable)
		bool PlayAnimationByName(FName AnimationName,float StartAtTime = 0.f,
			int32 NumLoopsToPlay = 1, EUMGSequencePlayMode::Type PlayMode=EUMGSequencePlayMode::Forward,
			float PlaybackSpeed = 1.f);

	public:
		TMap<FName, UWidgetAnimation*> AnimationMap;
	
		UWidgetAnimation* NoAmmoAnimation;
		UWidgetAnimation* Skill1TimeAnimation;
		UWidgetAnimation* Skill4TimeAnimation;

	protected:
	void FillAnimationMap();
	
	protected:
	
		
};
