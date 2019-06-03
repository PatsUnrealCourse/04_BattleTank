// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank) 
    {
        UE_LOG(LogTemp,Warning, TEXT("AI controller cant find player Tank"));
    }
    else {
        UE_LOG(LogTemp,Warning, TEXT("AI controller found player: %s"), *(PlayerTank->GetName() ));
    }
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    auto PlayerTank = GetPlayerTank();

    if (PlayerTank) 
    {
        // Aim towards Player
       GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
    }
}


ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank> (GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{  
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn() ;
    if (! PlayerPawn) { return nullptr;}
    return Cast<ATank>(PlayerPawn);
}
