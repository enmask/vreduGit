// Fill out your copyright notice in the Description page of Project Settings.

#include "ThingManager.h"


// Sets default values
AThingManager::AThingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThingManager::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("AThingManager::BeginPlay called"));


	Super::BeginPlay();
	
}

// Called every frame
void AThingManager::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("AThingManager::Tick called"));

	Super::Tick(DeltaTime);

}

AThing* AThingManager::SpawnThingAtom(FString name) {

	UE_LOG(LogTemp, Warning, TEXT("AThingManager::SpawnThingAtom called"));


	// Dummy transform data
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	FTransform trafo(Location);

	//
	// Start spawning
	//

	UWorld* const World = GetWorld();
	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("AThingManager::SpawnThingAtom: World exists"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AThingManager::SpawnThingAtom: World does NOT exist"));
	}

	AThing* newThing = World->SpawnActorDeferred<AThing>(AThing::StaticClass(), trafo);

	//
	// Initialize the Thing
	//
	newThing->init(name);

	//
	// Finish spawning
	//
	newThing->FinishSpawning(trafo);

	return newThing;
}



