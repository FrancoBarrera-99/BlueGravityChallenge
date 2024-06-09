#include "Objects/BGC_AirtimeTrick.h"

#include "BlueGravityChallenge/BlueGravityChallengeCharacter.h"
#include "GameFramework/PawnMovementComponent.h"


UBGC_AirtimeTrick::UBGC_AirtimeTrick()
{
	InitialHieght = 0.0f;
	MaxHeight = 0.0f;
	AirtimeDistance = 0.0f;
	BasePointReward = 10;
}

void UBGC_AirtimeTrick::SetCharacter(TObjectPtr<ABlueGravityChallengeCharacter> InCharacter)
{
	Character = InCharacter;
}

void UBGC_AirtimeTrick::PerformTrick()
{
	InitialHieght = Character->GetActorLocation().Z;
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TrackAirtimeTimerHandle, this, &UBGC_AirtimeTrick::CheckAirtime, 0.01f, true);
	}
}

void UBGC_AirtimeTrick::AbortTrick()
{
    CleanUp();
}

FTrickFinishedDelegate& UBGC_AirtimeTrick::OnTrickFinished()
{
	return TrickFinished;
}

void UBGC_AirtimeTrick::CheckAirtime()
{
    const bool bIsCharacterJumping = MaxHeight < Character->GetActorLocation().Z || Character->GetMovementComponent()->Velocity.Z > 0;
    if (bIsCharacterJumping)
    {
        MaxHeight = FMath::Max(MaxHeight, Character->GetActorLocation().Z);
    }
    else
    {
        if (Character->GetMovementComponent()->IsFalling())
        {
            const float CurrentLocationZ = Character->GetActorLocation().Z;
            const float CurrentDistance = MaxHeight - CurrentLocationZ;
            const float Threshold = 10.0f;
            AirtimeDistance = CurrentDistance > (MaxHeight - InitialHieght + Threshold) ? CurrentDistance : 0.0f;
        }
        else
        {
            CleanUp();
        }
    }
}


void UBGC_AirtimeTrick::CleanUp()
{
	GetWorld()->GetTimerManager().ClearTimer(TrackAirtimeTimerHandle);
	InitialHieght = 0.0f;
	MaxHeight = 0.0f;
	const int32 EarnedPoints = FMath::Abs(BasePointReward * (AirtimeDistance / 100.0f));
	TrickFinished.Broadcast(EarnedPoints);
}
