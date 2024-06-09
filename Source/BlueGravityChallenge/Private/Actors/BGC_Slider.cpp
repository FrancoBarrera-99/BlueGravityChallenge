#include "Actors/BGC_Slider.h"

#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "BlueGravityChallenge/BlueGravityChallengeCharacter.h"
#include "Objects/BGC_SlideTrick.h"
#include "Components/BGC_TrickComponent.h"
#include "GameFramework/PawnMovementComponent.h"


// Sets default values
ABGC_Slider::ABGC_Slider()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and set the RootComponent
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Mesh->SetupAttachment(RootComponent);

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(Mesh);

	SliderTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SliderCapsuleComponent"));
	SliderTrigger->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ABGC_Slider::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABGC_Slider::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetActorEnableCollision(true);

	if (IsValid(SliderTrigger))
	{
		SliderTrigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerOverlap);
	}
}

// Called every frame
void ABGC_Slider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABGC_Slider::OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<ABlueGravityChallengeCharacter> Character = Cast<ABlueGravityChallengeCharacter>(OtherActor);
	if (IsValid(Character))
	{
		if (Character->GetMovementComponent()->IsFalling())
		{
			TObjectPtr<UBGC_SlideTrick> SlideTrick = NewObject<UBGC_SlideTrick>(this);
			SlideTrick->Initialize(Character, SplineComponent);
			TObjectPtr<UBGC_TrickComponent> CharacterTrickComponent = Character->GetTrickComponent();
			if (IsValid(CharacterTrickComponent))
			{
				CharacterTrickComponent->PerformTrick(SlideTrick);
			}
		}
	}
}

