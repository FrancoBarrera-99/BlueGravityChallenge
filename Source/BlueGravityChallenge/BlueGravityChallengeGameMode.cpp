// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlueGravityChallengeGameMode.h"
#include "BlueGravityChallengeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABlueGravityChallengeGameMode::ABlueGravityChallengeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
