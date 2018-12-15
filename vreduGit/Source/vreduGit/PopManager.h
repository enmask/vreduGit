// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pop.h"
#include "PopManager.generated.h"

class AvreduGameMode;

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

	//
	// API methods
	//

	// Spawn a Pop in the world. Its shape is described by "thing"
	APop* Spawn(AThing* thing, FTransform transform);

	// Destroy a Pop
	void DestroyPop(APop* pop);

	// Pickup the Pop:s who have signalled
	void PickupThoseWhoWant();

	// Drop held Pop to whom have signalled
	//void DropChildToThoseWhoWant();

	// Add toBeChild as a child of parent
	void AddChild(APop* parent, APop* toBeChild);

	// Deep copy origPop and give the thing of the copy the name <cloneName>
	// Return the copy
	APop* Clone(APop* origPop, FString cloneName);

	// Attach pop to a player motion controller
	void Pickup(APop* pop);

	// Drop pop from the player motion controller
	void Drop(APop* pop);

	// Drop Pop and add it as child of a close-by (brightly lit) Pop
	// This is "drop method 2", "the yellow drop"
	void DropAndAddChild(APop* pop);

	// Return true if pop is very close to refPop
	bool IsClose(APop* pop, APop* refPop);

	// Return true if pop is very close to refPop
	bool IsVeryClose(APop* pop, APop* refPop);

	// Return true if pop1 is closer to refPop than pop2 is
	bool IsCloser(APop* pop1, APop* pop2, APop* refPop);

	void RotateAroundLocalY(APop* p, float degrees);

	void HighlightCloseTopChildren(APop* popParam);

private:
	bool IsCloseAux(float distanceLimit, APop* pop, APop* refPop);

	void IncPopsCounter();
	void DecPopsCounter();
	void LogControlPops();

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
