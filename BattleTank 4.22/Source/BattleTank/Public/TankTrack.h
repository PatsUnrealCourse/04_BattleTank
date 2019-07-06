// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TrankTrack is used to set maximum driving force an to apply forces to the tank
 * Class inheriting from UStaticMeshComponent having private variables 
       causes the static mesh in blueprint to be reset on editor or level load 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Blueprintcallable, Category = Input)
	void SetThrottle(float Throttle);
private:
	//Max force in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 50000000; //assume 40 ton tank. 1 G acceleatation (= 10m/s2)
};
