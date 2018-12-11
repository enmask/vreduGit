// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunebergVR_Pawn.h"
#include "MyRunebergVR_Pawn.generated.h"

class URunebergVR_Movement;
class AvreduGameMode;

/**
 * 
 */
UCLASS()
class VREDUGIT_API AMyRunebergVR_Pawn : public ARunebergVR_Pawn
{
	GENERATED_BODY()
	
public:

	//AMyRunebergVR_Pawn(const class FObjectInitializer& PCIP);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	AvreduGameMode* GetGameMode();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		URunebergVR_Movement* vrMovement;

	UActorComponent* GetRightMotionController();

	void TurnSideAtRate(float Rate);
	void TurnUpDownAtRate(float Rate);

	void MoveForwardBackward(float AxisValue);
	//void MoveForwardKeyb();
	//void MoveBackwardKeyb();

	void MoveRControllerForwardBackward(float AxisValue);
	void MoveRControllerSide(float AxisValue);
	void MoveRControllerUpDown(float AxisValue);

	//void StartGrowing();
	//void StopGrowing();

	FVector CurrentVelocity;
	bool bGrowing;
};
