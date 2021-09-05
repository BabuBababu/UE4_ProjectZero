// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PortfolioProjectGameMode.generated.h"

class UUserWidget;

UCLASS(minimalapi)
class APortfolioProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APortfolioProjectGameMode();

	virtual void BeginPlay() override;
};



