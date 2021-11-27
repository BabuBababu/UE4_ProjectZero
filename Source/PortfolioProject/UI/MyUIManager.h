// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUIManager.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UMyUIManager : public UUserWidget
{
	GENERATED_BODY()

	public:
	virtual void NativeConstruct() override;
	public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UUserWidget>> UITClassArray;

	
	void Init();
	void AddUI();
	void DelUI(UUserWidget* name);
	void AllAddToViewPort();
	void NameByAddToViewPort(UUserWidget* name);
	void NameByRemoveFromParent(UUserWidget* name);
	void SetContoller(APlayerController* playercon);

	public:
	TArray<class UUserWidget*> UIArray;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> createdwidgetSubClass;;
	UPROPERTY()
	UUserWidget* createdWidget;

	APlayerController* PlayerController;
};
