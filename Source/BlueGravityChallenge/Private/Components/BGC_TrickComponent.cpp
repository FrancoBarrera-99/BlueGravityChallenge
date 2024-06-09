#include "Components/BGC_TrickComponent.h"


// Sets default values for this component's properties
UBGC_TrickComponent::UBGC_TrickComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UBGC_TrickComponent::PerformTrick(TScriptInterface<IBGC_TrickInterface> Trick)
{
	Trick->PerformTrick();
	Trick->OnTrickFinished().AddDynamic(this, &ThisClass::OnTrickFinished);
}


// Called when the game starts
void UBGC_TrickComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UBGC_TrickComponent::OnTrickFinished(int32 InEarnedPoints)
{
	if (GEngine)
	{	
		FString PointsString = FString::FromInt(InEarnedPoints);
		GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Green, PointsString);
	}
}


// Called every frame
void UBGC_TrickComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

