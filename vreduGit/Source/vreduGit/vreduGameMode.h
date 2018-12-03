// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThingManager.h"
#include "PopManager.h"
#include "GameplayManager.h"
#include "MyRunebergVR_Pawn.h"
#include "vreduGameMode.generated.h"

class APop;

/**
 *  The game mode of vredu. Holds the following managers accessible anywhere:
 *		* GameplayManager
 *		* ThingManager
 *		* PopManager
 */
UCLASS()
class VREDUGIT_API AvreduGameMode : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

public:

	// A GameplayManager accessible from anywhere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		AGameplayManager* theGameplayManager;
	
	// A ThingManager accessible from anywhere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		AThingManager* theThingManager;

	// A PopManager accessible from anywhere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		APopManager* thePopManager;

	// A VR pawn accessible from anywhere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		AMyRunebergVR_Pawn* thePawn;

	// Set to true in editor to activate the light-weight in-editor testing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		bool autotestInEditor;

	// Which autotest to run in-editor, provided autotestInEditor is set to true
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		int autotestNo;

	// How many Tick:s of GameplayManager to run before exiting, provided autotestInEditor is set to true
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		int autotestNumTicks;

	// Define "close" in e.g. IsClose(pop1, pop2)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		float closeDistanceSquared = 500000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		FLinearColor deHighlightColor = FLinearColor(0.0916f, 0.271f, 0.0705f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		FLinearColor highlightColor = FLinearColor(0.97f, 0.32f, 0.30f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		FLinearColor brightHighlightColor = FLinearColor(1.0f, 1.0f, 1.0f);

	// TODO: Maybe move wantsPicking and its 2 access functions to a new separate class PopSignals
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VR")
		TSet< APop* > wantsPicking;

	UFUNCTION()
		TSet< APop* > GetWantsPicking();

	UFUNCTION()
		void AddWantsPicking(APop* pop);

	UFUNCTION()
		void RemoveWantsPicking(APop* pop);

	virtual void StartPlay() override;

};
