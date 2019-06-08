// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToset) 
{
	Barrel = BarrelToset;
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
			ESuggestProjVelocityTraceOption::DoNotTrace
		)
	)
	{

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	// rotate to aimdirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotatror = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp,Warning, TEXT("AimasRotator: %s"), *AimAsRotator.ToString());
	// give max elevationspeed

	// up down to height
}

