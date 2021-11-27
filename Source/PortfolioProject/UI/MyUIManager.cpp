// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUIManager.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Player/PortfolioProjectCharacter.h"
#include "Kismet/GameplayStatics.h"


void UMyUIManager::NativeConstruct()
{
	Super::NativeConstruct();
	Init();

}
void UMyUIManager::Init()
{
	UIArray.Empty();
	UITClassArray.Empty();
}

void UMyUIManager::AddUI()
{
	
	for (int i = 0 ; i < UITClassArray.Num(); ++i)
	{
		createdWidget = CreateWidget<UUserWidget>(PlayerController, UITClassArray[i]);
		// 위젯 배열에 저장
		createdWidget->AddToViewport();
		UIArray.Add(createdWidget);
	}
}

void UMyUIManager::DelUI(UUserWidget* name)
{
	for (UUserWidget* widget : UIArray)
	{
		if(name == widget)
		{
			UIArray.Remove(widget);
		}
	}
}


void UMyUIManager::AllAddToViewPort()
{
	if (UIArray.Num() > 0)
	{
		for (int i = 0 ; i < UIArray.Num(); ++i)
		{
			UIArray[i]->AddToViewport();
		}
		UE_LOG(LogTemp, Warning, TEXT("sucess AllAddToViewport"));
	}
}

void UMyUIManager::NameByAddToViewPort(UUserWidget* name)
{
	for (UUserWidget* widget : UIArray)
	{
		if(widget == name)
		{
			name->AddToViewport();	
		}
	}
}

void UMyUIManager::NameByRemoveFromParent(UUserWidget* name)
{
	for (UUserWidget* widget : UIArray)
	{
		if(widget == name)
		{
			name->RemoveFromParent();	
		}
	}
}


void UMyUIManager::SetContoller(APlayerController* playercon)
{
	PlayerController = playercon;
}