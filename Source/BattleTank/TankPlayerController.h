// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//ATankPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

private:
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;


	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.333333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection,FVector& HitLocation) const;
	
};
