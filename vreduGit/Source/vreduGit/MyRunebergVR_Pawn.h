// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunebergVR_Pawn.h"
#include "MyRunebergVR_Pawn.generated.h"

class URunebergVR_Movement;
class AvreduGameMode;

UENUM(BlueprintType)
enum class EPickModeEnum : uint8
{
	M_Pick		UMETA(DisplayName = "Pick"),
	M_PickChild UMETA(DisplayName = "PickChild")
};

UENUM(BlueprintType)
enum class EDropModeEnum : uint8
{
	M_Drop			UMETA(DisplayName = "Drop"),
	M_DropChild		UMETA(DisplayName = "DropChild"),
	M_DropSibling	UMETA(DisplayName = "DropSibling")
};


/**
 * 
 */
UCLASS()
class VREDUGIT_API AMyRunebergVR_Pawn : public ARunebergVR_Pawn
{
	GENERATED_BODY()
	
public:

	//AMyRunebergVR_Pawn(const class FObjectInitializer& PCIP);
	//AMyRunebergVR_Pawn();


	//UPROPERTY(VisibleAnywhere)
	//	UStaticMeshComponent* rightHandMesh;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	AvreduGameMode* GetGameMode();

#if 1
	FString GetPickModeEnumAsString(EPickModeEnum EnumValue);
#else
	FString GetPickModeEnumAsString(EPickModeEnum EnumValue)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPickModeEnum"), true);
		if (!EnumPtr) return FString("Invalid");

		return EnumPtr->GetNameByValue((int64)EnumValue).ToString(); // for EnumValue == M_Pick returns "Pick"
	}
#endif

	FString GetDropModeEnumAsString(EDropModeEnum EnumValue);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EPickModeEnum pickModeEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EDropModeEnum dropModeEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		URunebergVR_Movement* vrMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		float controllerSpeed;

	UActorComponent* GetRightMotionController();

	void TurnSideAtRate(float Rate);
	void TurnUpDownAtRate(float Rate);

	void MoveForwardBackward(float AxisValue);
	//void MoveForwardKeyb();
	//void MoveBackwardKeyb();

	void MoveRControllerForwardBackward(float AxisValue);
	void MoveRControllerSide(float AxisValue);
	void MoveRControllerUpDown(float AxisValue);

	void TogglePickDropMode();

	//void StartGrowing();
	//void StopGrowing();

	FVector CurrentVelocity;
	bool bGrowing;
};
