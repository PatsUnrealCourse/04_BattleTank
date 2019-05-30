// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) 
    {
        UE_LOG(LogTemp,Warning, TEXT("PlaYERcontroller not posessing Tank"));
    }
    else {
        UE_LOG(LogTemp,Warning, TEXT("PlaYERcontroller Posessing %s"), *(ControlledTank->GetName() ));
    }
    UE_LOG(LogTemp,Warning, TEXT("PlaYERcontroller Begin Play"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank> (GetPawn());
}