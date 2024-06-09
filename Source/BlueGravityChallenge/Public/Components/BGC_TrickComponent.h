#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/BGC_TrickInterface.h"

#include "BGC_TrickComponent.generated.h"


/**
 *	Component attached to a character for managing tricks events.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLUEGRAVITYCHALLENGE_API UBGC_TrickComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBGC_TrickComponent();

	void PerformTrick(TScriptInterface<IBGC_TrickInterface> Trick);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTrickFinished(int32 InEarnedPoints);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
