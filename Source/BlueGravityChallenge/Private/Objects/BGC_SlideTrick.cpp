#include "Objects/BGC_SlideTrick.h"

#include "BlueGravityChallenge/BlueGravityChallengeCharacter.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"


UBGC_SlideTrick::UBGC_SlideTrick()
	: CurrentDistance(0.0f), SlideSpeed(200.0f)
{
}

void UBGC_SlideTrick::Initialize(TObjectPtr<ABlueGravityChallengeCharacter> InCharacter, TObjectPtr<USplineComponent> InSplineComponent)
{
	Character = InCharacter;
	SplineComponent = InSplineComponent;
}

void UBGC_SlideTrick::StartSlide()
{
	if (IsValid(Character) && IsValid(SplineComponent))
	{
		FString MontagePath = "/Game/Assets/Character/Animations/Skateboarding_balance_Montage";
		LoadMontageFromPath(MontagePath);

		// Find the closest point on the spline to the character's current location
		FVector CharacterLocation = Character->GetActorLocation();
		float InputKey = SplineComponent->FindInputKeyClosestToWorldLocation(CharacterLocation);
		CurrentDistance = SplineComponent->GetDistanceAlongSplineAtSplineInputKey(InputKey);

		// Determine slide direction based on character's movement direction
		FVector CharacterVelocity = Character->GetVelocity();
		FVector SplineDirection = SplineComponent->GetDirectionAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World);
		SliderDotProduct = FVector::DotProduct(CharacterVelocity, SplineDirection);

		// Set SlideSpeed to negative if character is moving against spline direction
		if (SliderDotProduct < 0)
		{
			SlideSpeed = -FMath::Abs(SlideSpeed);
		}
		else
		{
			SlideSpeed = FMath::Abs(SlideSpeed);
		}

		Character->GetMovementComponent()->StopMovementImmediately();

		if (SlideMontage)
		{
			Character->PlayAnimMontage(SlideMontage);
		}

		GetWorld()->GetTimerManager().SetTimer(SlideTimerHandle, this, &UBGC_SlideTrick::SlideAlongSpline, 0.01f, true);
	}
}

void UBGC_SlideTrick::PerformTrick()
{
	StartSlide();
}

FTrickFinishedDelegate& UBGC_SlideTrick::OnTrickFinished()
{
	return TrickFinished;
}

void UBGC_SlideTrick::SlideAlongSpline()
{
	if (!IsValid(Character) || !IsValid(SplineComponent))
	{
		EndSlide();
		return;
	}

	CurrentDistance += SlideSpeed * 0.01f;

	FVector NewLocation = SplineComponent->GetLocationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World);
	FRotator NewRotation = SplineComponent->GetRotationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World);

	if (SliderDotProduct < 0)
	{
		NewRotation.Yaw += 180.0f;
	}

	Character->SetActorLocationAndRotation(NewLocation, NewRotation);

	if (CurrentDistance >= SplineComponent->GetSplineLength() || CurrentDistance < 0)
	{
		EndSlide();
	}
}

void UBGC_SlideTrick::EndSlide()
{
	GetWorld()->GetTimerManager().ClearTimer(SlideTimerHandle);
	if (IsValid(Character) && SlideMontage)
	{
		Character->StopAnimMontage(SlideMontage);
	}
}

void UBGC_SlideTrick::LoadMontageFromPath(const FString& MontagePath)
{
	if (MontagePath.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("UBGC_SlideTrick::LoadMontageFromPath - Montage Path is empty."));
		return;
	}

	SlideMontage = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), nullptr, *MontagePath));
}

