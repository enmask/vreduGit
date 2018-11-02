// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThingManager.h"
#include "GameplayManager.h"
#include "vreduGameMode.generated.h"

/**
 *  The game mode of vredu. Holds the following managers accessible anywhere:
 *		* GameplayManager
 *		* PopManager
 *		* ThingManager
 */
UCLASS()
class VREDUGIT_API AvreduGameMode : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

public:

	// A GameplayManager accessible from anywhere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		AGameplayManager* theGameplayManager;
	
	// A PopManager accessible from anywhere
	// NYI

	// A ThingManager accessible from anywhere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		AThingManager* theThingManager;

	virtual void StartPlay() override;

};
