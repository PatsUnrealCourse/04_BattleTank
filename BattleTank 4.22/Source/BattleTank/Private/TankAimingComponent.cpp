// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToset) 
{
	Barrel = BarrelToset;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToset) 
{
	Turret = TurretToset;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) 
{
	if (!Barrel) {return;}
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		)
	)
	{

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
	    UE_LOG(LogTemp,Warning, TEXT("Aim Found %f"),Time);
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
	    UE_LOG(LogTemp,Warning, TEXT("No Aim solve %f"),Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	// rotate to aimdirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotatror = AimAsRotator - BarrelRotator;
	
	// give max elevationspeed
	
	// up down to height
	Barrel->Elevate(DeltaRotatror.Pitch);

	//Turret->Rotate(1);
}

