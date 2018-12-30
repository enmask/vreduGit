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
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void SetupMaterial();

	AvreduGameMode* GetGameMode();

#if 0
	FString GetPickModeEnumAsString(EPickModeEnum EnumValue);
	FString GetDropModeEnumAsString(EDropModeEnum EnumValue);
#endif

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		URunebergVR_Movement* vrMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		float controllerSpeed;

	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIHandPick;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIHandPickChild;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIHandClone;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIHandCloneChild;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIHandDrop;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIHandDropChild;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIHandDropSibling;

	UActorComponent* GetRightMotionController();
	UActorComponent* GetRightMotionControllerMesh();

	void TurnSideAtRate(float Rate);
	void TurnUpDownAtRate(float Rate);

	void MoveForwardBackward(float AxisValue);
	//void MoveForwardKeyb();
	//void MoveBackwardKeyb();

	void MoveRControllerForwardBackward(float AxisValue);
	void MoveRControllerSide(float AxisValue);
	void MoveRControllerUpDown(float AxisValue);

	void TogglePickDropMode();
	//
	// Let the user spawn atoms in hand
	//
	void SpawnAtom();

	void UpdateControllerModeColor();
	void UpdateControllerPickModeColor();
	void UpdateControllerDropModeColor();

	//void StartGrowing();
	//void StopGrowing();

	FVector CurrentVelocity;
	bool bGrowing;
};
