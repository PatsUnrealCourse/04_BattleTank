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

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //UE_LOG(LogTemp,Warning,TEXT("Player controller ticking"));
    AimTowardCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank> (GetPawn());
}

void  ATankPlayerController::AimTowardCrosshair() {
    if (!GetControlledTank()) {return;}

    FVector HitLocation; // OutParameter
    if (GetSightRayHitLocation(HitLocation)) {
       UE_LOG(LogTemp,Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
    }
    // get world location of linetrace through crosshair
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const 
{
    // find the crosshair in pixel coordinates
    int32 ViewportSizeX,ViewportSizeY;
    GetViewportSize(ViewportSizeX,ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection)) {
       // UE_LOG(LogTemp,Warning, TEXT("Lookdirection: %s"), *LookDirection.ToString());
       GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraworldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X,ScreenLocation.Y,CameraworldLocation, LookDirection);
    
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const 
{
    FHitResult HitResult;
    auto StartLocatino = PlayerCameraManager->GetCameraLocation();
    auto EndLocation =  StartLocatino + (LookDirection * LineTraceRange );
    if (GetWorld()->LineTraceSingleByChannel(HitResult,StartLocatino,EndLocation,ECollisionChannel::ECC_Visibility)) 
    {
        HitLocation = HitResult.Location;
        return true;
    }
    return false;
}