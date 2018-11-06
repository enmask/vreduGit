// Fill out your copyright notice in the Description page of Project Settings.

#include "PopManager.h"


// Sets default values
APopManager::APopManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APopManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APopManager::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("APopManager::Tick called"));

	Super::Tick(DeltaTime);

}


APop* APopManager::Spawn(AThing* thing, FTransform transform) {

	UE_LOG(LogTemp, Warning, TEXT("APopManager::Spawn called"));

	/*
	// Dummy transform data
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	FTransform trafo(Location);
	*/

	//
	// Start spawning
	//

	UWorld* const World = GetWorld();
	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("APopManager::Spawn: World exists"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("APopManager::Spawn: World does NOT exist"));
	}

	APop* newPop = World->SpawnActorDeferred<APop>(APop::StaticClass(), transform);

	//
	// Initialize the Pop
	//
	newPop->init(thing, transform);

	//
	// Finish spawning
	//
	newPop->FinishSpawning(transform);

	return newPop;
}