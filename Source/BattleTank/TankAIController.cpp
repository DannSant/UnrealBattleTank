// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI not possessing a tank"));
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Begin play %s"), *ControlledTank->GetName());
	}

	auto PlayerPawn = GetPlayerTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player pawn not found"));
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player pawn found %s"), *ControlledTank->GetName());
	}

}



void ATankAIController::Tick(float DeltaTime)
{
	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();
	if (ControlledTank && PlayerTank) {
		//Move towards player
		//TODO Implement movement AI

		//Aim to player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fire if ready
		//TODO Implement fire method
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	else {
		return Cast<ATank>(PlayerPawn);
	}
	
	
}



