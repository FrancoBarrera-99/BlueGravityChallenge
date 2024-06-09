#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/BGC_TrickInterface.h"

#include "BGC_AirtimeTrick.generated.h"


#pragma region ForwardDeclarations
class ABlueGravityChallengeCharacter;
#pragma endregion ForwardDeclarations

/**
 * Calculates airtime to perform a trick on the main character.
 */
UCLASS()
class BLUEGRAVITYCHALLENGE_API UBGC_AirtimeTrick : public UObject, public IBGC_TrickInterface
{
	GENERATED_BODY()
protected:
	FTrickFinishedDelegate TrickFinished;

	TObjectPtr<ABlueGravityChallengeCharacter> Character;

	FTimerHandle TrackAirtimeTimerHandle;

	float InitialHieght;

	float MaxHeight;

	float AirtimeDistance;

	int32 BasePointReward;

public:
	UBGC_AirtimeTrick();

	void SetCharacter(TObjectPtr<ABlueGravityChallengeCharacter> InCharacter);

#pragma region ITrickInterface
	void PerformTrick() override;

	FTrickFinishedDelegate& OnTrickFinished() override;
#pragma endregion ITrickInterface

protected:
	void CheckAirtime();

	void CleanUp();
};
