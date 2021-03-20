// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortfolioProjectGameMode.h"
#include "PortfolioProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

APortfolioProjectGameMode::APortfolioProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
