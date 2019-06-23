// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

    if (PlayerTank) 
    {
        // Aim towards Player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());

	    ControlledTank->Fire(); // Dont fire every frame
    }
}
