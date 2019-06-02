// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	ATank* GetControlledTank() const;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BeginPlay() override;

	void  AimTowardCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditAnyWhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnyWhere)
    float CrossHairYLocation = 0.33333;

    UPROPERTY(EditAnyWhere)
    float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};

