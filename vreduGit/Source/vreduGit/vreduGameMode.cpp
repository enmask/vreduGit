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


	UWorld* const World = GetWorld();
	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode constructor: World exists"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode constructor: World does NOT exist"));
	}
}


void AvreduGameMode::StartPlay() {
	UE_LOG(LogTemp, Warning, TEXT("vreduGameMode::StartPlay called"));

	Super::StartPlay();


	//vrMovement = NewObject<URunebergVR_Movement>(this, TEXT("vrMovement"));
	//theGameplayManager = NewObject<AGameplayManager>(this, TEXT("The GameplayManager"));
	//WaitingScreen = NewObject<UDifferentVariables>(this, UDifferentVariables::StaticClass());
	//theGameplayManager = NewObject<AGameplayManager>(this, AGameplayManager::StaticClass());

	UWorld* world = GetWorld();
	//APlayerUnitController* cont = world->SpawnActor< APlayerUnitController >();
	theGameplayManager = world->SpawnActor< AGameplayManager >();

	if (theGameplayManager) {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::StartPlay: theGameplayManager is NOT null"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::StartPlay: theGameplayManager IS null"));
	}

	theThingManager = world->SpawnActor< AThingManager >();

	if (theThingManager) {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::StartPlay: theThingManager is NOT null"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::StartPlay: theThingManager IS null"));
	}

	thePopManager = world->SpawnActor< APopManager >();

	UWorld* const World = GetWorld();
	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::StartPlay: World exists"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::StartPlay: World does NOT exist"));
	}

	UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::StartPlay: this (game mode)=%p, World=%p, theThingManager=%p"),
		this, World, theThingManager);


	// crashes
	//theGameplayManager->CallBeginPlay();
}


TSet< APop* > AvreduGameMode::GetWantsPicking() {
	return wantsPicking;
}

void AvreduGameMode::AddWantsPicking(APop* pop) {
	wantsPicking.Add(pop);
}

void AvreduGameMode::RemoveWantsPicking(APop* pop) {
	wantsPicking.Remove(pop);
}