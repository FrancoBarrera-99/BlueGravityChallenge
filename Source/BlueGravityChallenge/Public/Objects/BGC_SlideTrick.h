#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/BGC_TrickInterface.h"

#include "BGC_SlideTrick.generated.h"


#pragma region ForwardDeclarations
class ABlueGravityChallengeCharacter;
class USplineComponent;
class UAnimMontage;
#pragma endregion ForwardDeclarations

/**
 * 
 */
UCLASS()
class BLUEGRAVITYCHALLENGE_API UBGC_SlideTrick : public UObject, public IBGC_TrickInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TObjectPtr<ABlueGravityChallengeCharacter> Character;

	UPROPERTY()
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY()
	FTimerHandle SlideTimerHandle;

	float CurrentDistance;

	float SlideSpeed;

	float SliderDotProduct;

	FTrickFinishedDelegate TrickFinished;

	UAnimMontage* SlideMontage;

public:
	UBGC_SlideTrick();

	void Initialize(TObjectPtr<ABlueGravityChallengeCharacter> InCharacter, TObjectPtr<USplineComponent> InSplineComponent);

	void StartSlide();

#pragma region IBGC_TrickInterface
	void PerformTrick() override;

	void AbortTrick() override;

	FTrickFinishedDelegate& OnTrickFinished() override;
#pragma endregion IBGC_TrickInterface

protected:
	void SlideAlongSpline();

	void EndSlide();

	void LoadMontageFromPath(const FString& MontagePath);
};
