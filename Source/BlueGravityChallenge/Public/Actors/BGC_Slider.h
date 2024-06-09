#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BGC_Slider.generated.h"


#pragma region ForwardDeclarations
class USplineComponent;
class UStaticMeshComponent;
class UCapsuleComponent;
#pragma endregion ForwardDeclarations

UCLASS()
class BLUEGRAVITYCHALLENGE_API ABGC_Slider : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* SliderTrigger;
	
public:	
	// Sets default values for this actor's properties
	ABGC_Slider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
