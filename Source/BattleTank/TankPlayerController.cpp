// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

#define OUT
/*
ATankPlayerController::ATankPlayerController() {
	PrimaryActorTick.bCanEverTick = true;
}*/


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank =  GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin play %s"), *ControlledTank->GetName());
	}
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("Ticking"));

}


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair(){
	if (!GetControlledTank()) {
		return;
	}
	FVector HitLocation;
	
	//Get world location of linetrace through corsshair
	if (GetSightRayHitLocation(OUT HitLocation)) {
		//If it hits the landscape
		
		//Tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
	
		
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	float x = ViewportSizeX * CrosshairXLocation;
	float y = ViewportSizeY * CrosshairYLocation;

	FVector2D Aim2DVector = FVector2D(x, y);
	
	//Deproject the screen position of the corsshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(Aim2DVector, OUT LookDirection)) {
		//Linetrace along that look direction and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, OUT HitLocation);
		
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation;
	
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);	
	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection,FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection*LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(OUT HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		HitLocation = FVector(0);
		return false;
	}
	
	
}


