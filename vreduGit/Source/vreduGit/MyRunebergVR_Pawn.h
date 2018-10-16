// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunebergVR_Pawn.h"
#include "MyRunebergVR_Pawn.generated.h"

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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForwardBackward(float AxisValue);
	//void StartGrowing();
	//void StopGrowing();

	FVector CurrentVelocity;
	bool bGrowing;
};
