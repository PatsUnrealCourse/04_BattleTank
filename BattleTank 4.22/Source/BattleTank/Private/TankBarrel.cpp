// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{ 
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1 );
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

    auto  elevation = FMath::Clamp<float>(RawNewElevation,MinElevationDegrees,MaxElevationDegrees);

    SetRelativeRotation(FRotator(elevation,0,0));

}