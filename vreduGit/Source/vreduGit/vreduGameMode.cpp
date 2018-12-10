// Fill out your copyright notice in the Description page of Project Settings.

#include "vreduGameMode.h"
#include "MyRunebergVR_Pawn.h"

AvreduGameMode::AvreduGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//PlayerControllerClass = AStrategyPlayerController::StaticClass();
	//PlayerControllerClass = APlayerController::StaticClass();

	//SpectatorClass = AStrategySpectatorPawn::StaticClass();

	//DefaultPawnClass = AStrategySpectatorPawn::StaticClass();
	DefaultPawnClass = AMyRunebergVR_Pawn::StaticClass();

	//GameStateClass = AStrategyGameState::StaticClass();
	//GameStateClass = AGameState::StaticClass();


	//HUDClass = AStrategyHUD::StaticClass();
	/*
	if ((GEngine != nullptr) && (GEngine->GameViewport != nullptr))
	{
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}
	*/

	//
	// Create the GameplayManager
	//
#if 0 /* Moved to StartPlay() */
	theGameplayManager = CreateDefaultSubobject<AGameplayManager>(TEXT("The GameplayManager"));

	if (theGameplayManager) {
		UE_LOG(LogTemp, Warning, TEXT("theGameplayManager is NOT null"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("theGameplayManager IS null"));
	}
#endif

	//
	// Create the PopManager
	//
	// NYI

#if 0 /* May move to StartPlay() */
	//
	// Create the ThingManager
	//
	theThingManager = CreateDefaultSubobject<AThingManager>(TEXT("The ThingManager"));

	if (theThingManager) {
		UE_LOG(LogTemp, Warning, TEXT("theThingManager is NOT null"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("theThingManager IS null"));
	}
#endif

}


void AvreduGameMode::StartPlay() {
	UE_LOG(LogTemp, Warning, TEXT("vreduGameMode::StartPlay called"));

	Super::StartPlay();

	UWorld* world = GetWorld();
	theGameplayManager = world->SpawnActor< AGameplayManager >();
	theThingManager = world->SpawnActor< AThingManager >();
	thePopManager = world->SpawnActor< APopManager >();

	//wantsDropping = false;
}


TArray< APop* > AvreduGameMode::GetWantsPicking() {
	return wantsPicking;
}

void AvreduGameMode::AddWantsPicking(APop* pop) {
	wantsPicking.Add(pop);
}

void AvreduGameMode::RemoveWantsPicking(APop* pop) {
	wantsPicking.Remove(pop);
}

void AvreduGameMode::RemoveWantsPickingAt(int ix) {
	wantsPicking.RemoveAt(ix);
}

#if 0
APop* AvreduGameMode::GetWantsDropping() {
	return wantsDropping;
}

void AvreduGameMode::SetWantsDropping(bool value) {
	wantsDropping = value;
}
#endif