#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "BGC_TrickInterface.generated.h"


#pragma region Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrickFinishedDelegate, int32, EarnedPoints);
#pragma endregion Delegates

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBGC_TrickInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for defining trick behaviors.
 */
class BLUEGRAVITYCHALLENGE_API IBGC_TrickInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void PerformTrick() = 0;
	virtual FTrickFinishedDelegate& OnTrickFinished() = 0;
};
