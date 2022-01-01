// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUIManager.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Player/PortfolioProjectCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


void UMyUIManager::NativeConstruct()
{
	Super::NativeConstruct();
}
void UMyUIManager::Init()
{
	UIArray.Empty();
	UITClassArray.Empty();
	
	
	// APortfolioProjectCharacter* const Player = Cast<APortfolioProjectCharacter>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	
	
}

void UMyUIManager::AddUI()
{
	UIArray.Add(EscMenuUI);
	UIArray.Add(MissionFailUI);
	UIArray.Add(G36CUI);
	UIArray.Add(RO635UI);
	UIArray.Add(CommanderUI);
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

void UMyUIManager::NameBySetVisibility(UUserWidget* Name, ESlateVisibility type)
{
	for (UUserWidget* widget : UIArray)
	{
		if(widget == Name)
		{
			UE_LOG(LogTemp, Warning, TEXT("sucess Read widget!"));
			if(ESlateVisibility::Hidden == type)
			{
				widget->SetVisibility(ESlateVisibility::Hidden);
				UE_LOG(LogTemp, Warning, TEXT("sucess Hidden!"));
			}
			else if(ESlateVisibility::Visible == type)
			{
				widget->SetVisibility(ESlateVisibility::Visible);
				UE_LOG(LogTemp, Warning, TEXT("sucess Visible!"));
			}
		}
	}
}


void UMyUIManager::SetContoller(APlayerController* playercon)
{
	PlayerController = playercon;
}


