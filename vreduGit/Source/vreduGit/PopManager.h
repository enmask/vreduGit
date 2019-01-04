// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pop.h"
#include "PopManager.generated.h"

class AvreduGameMode;

UENUM(BlueprintType)
enum class EPickModeEnum : uint8
{
	M_Pick		 UMETA(DisplayName = "Pick"),
	M_PickChild  UMETA(DisplayName = "PickChild"),
	M_Clone		 UMETA(DisplayName = "Clone"),
	M_CloneChild UMETA(DisplayName = "CloneChild")
};

UENUM(BlueprintType)
enum class EDropModeEnum : uint8
{
	M_Drop			UMETA(DisplayName = "Drop"),
	M_DropChild		UMETA(DisplayName = "DropChild"),
	M_DropSibling	UMETA(DisplayName = "DropSibling")
};

UCLASS()
class VREDUGIT_API APopManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APopManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AvreduGameMode* GetGameMode();

	UPROPERTY(VisibleAnywhere)
		APop* pickedPop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EPickModeEnum pickModeEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EDropModeEnum dropModeEnum;

	//
	// API methods
	//

	// Spawn a Pop in the world. Its shape is described by "thing"
	APop* Spawn(AThing* thing,
				FTransform transform,
				ESpawnActorCollisionHandlingMethod collisionHandling = ESpawnActorCollisionHandlingMethod::Undefined);

	// Destroy a Pop
	void DestroyPop(APop* pop);

	// Pickup the Pop:s who have signalled
	void PickupThoseWhoWant();

	// Drop held Pop to whom have signalled
	//void DropChildToThoseWhoWant();

	// Add toBeChild as a child of parent
	void AddChild(APop* parent, APop* toBeChild);

	// Attach pop to a player motion controller
	void Pickup(APop* pop);

	// Separate one child thing of a pop and pick it up
	void PickChild(APop* pop);

	// Deep copy origPop and give the thing of the copy the name <cloneName>
	// Return the copy
	APop* Clone(APop* origPop, FString cloneName);

	// Deep copy origPop and give the thing of the copy the name <cloneName>
	// Return the copy, but also pick it up
	void ClonePick(APop* origPop, FString cloneName);

	// Deep copy one child of origPop and give the thing of the copy the name <cloneName> or
	// , if cloneName is "", original name with "_cloneName" appended
	// ***NYI. TODO: Add parameter that specifies which child to clone
	APop* CloneChild(APop* origPop, FString cloneName);

	// Drop pop from the player motion controller
	void Drop(APop* pop);

	// Drop pop and add it as child of a close-by (brightly lit) Pop
	// This is "drop method 2", "the yellow drop"
	void DropAndAddChild(APop* pop);

	// Drop (until now) pop and add it as sibling to another (until now) pop, with a new parent pop
	void DropSibling(APop* pop);

	// Return true if pop is very close to refPop
	bool IsClose(APop* pop, APop* refPop);

	// Return true if pop is very close to refPop
	bool IsVeryClose(APop* pop, APop* refPop);

	// Return true if pop1 is closer to refPop than pop2 is
	bool IsCloser(APop* pop1, APop* pop2, APop* refPop);

	void RotateAroundLocalY(APop* p, float degrees);

	void HighlightCloseTopChildren(APop* popParam);

	bool IsPickMode();
	bool IsPickChildMode();
	bool IsCloneMode();
	bool IsCloneChildMode();
	bool IsDropMode();
	bool IsDropChildMode();
	bool IsDropSiblingMode();

	void TogglePickDropMode();


private:
	bool IsCloseAux(float distanceLimit, APop* pop, APop* refPop);

	void IncPopsCounter();
	void DecPopsCounter();
	void LogControlPops();

	void UpdateControllerModeColor();
	UActorComponent* GetRightMotionController();

	UPROPERTY(VisibleAnywhere)
		int numTicks;

	UPROPERTY(VisibleAnywhere)
		TArray<APop*> controlPops;

	UPROPERTY(VisibleAnywhere)
		int numPops;

	UPROPERTY(VisibleAnywhere)
		APop* brightPop;
};
