#include "Components/BGC_TrickComponent.h"

#include "BlueGravityChallenge/BlueGravityChallengeCharacter.h"


void UBGC_TrickComponent::PerformTrick(TScriptInterface<IBGC_TrickInterface> Trick)
{
	if (CurrentTrick)
	{
		CurrentTrick->AbortTrick();
	}

	Trick->PerformTrick();
	Trick->OnTrickFinished().AddDynamic(this, &ThisClass::OnTrickFinished);
	CurrentTrick = Trick;
}


// Called when the game starts
void UBGC_TrickComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ABlueGravityChallengeCharacter>(GetOwner());
}

void UBGC_TrickComponent::OnTrickFinished(int32 InEarnedPoints)
{
	if (IsValid(Character) && InEarnedPoints > 0)
	{	
		Character->AddRewardPoints(InEarnedPoints);
	}
}
