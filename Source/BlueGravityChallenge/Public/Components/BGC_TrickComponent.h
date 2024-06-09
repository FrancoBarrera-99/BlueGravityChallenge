#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/BGC_TrickInterface.h"

#include "BGC_TrickComponent.generated.h"


#pragma region ForwardDeclarations
class ABlueGravityChallengeCharacter;
#pragma region ForwardDeclarations

/**
 *	Component attached to a character for managing tricks events.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLUEGRAVITYCHALLENGE_API UBGC_TrickComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	TScriptInterface<IBGC_TrickInterface> CurrentTrick;

	TObjectPtr<ABlueGravityChallengeCharacter> Character;

public:	
	void PerformTrick(TScriptInterface<IBGC_TrickInterface> Trick);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTrickFinished(int32 InEarnedPoints);
};
