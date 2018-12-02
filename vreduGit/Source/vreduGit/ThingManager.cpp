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
	//UE_LOG(LogTemp, Warning, TEXT("AThingManager::Tick called"));

	Super::Tick(DeltaTime);
}

AThing* AThingManager::SpawnThingAtom(FString name) {

	//UE_LOG(LogTemp, Warning, TEXT("AThingManager::SpawnThingAtom called"));

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


AThing* AThingManager::Clone(AThing* t, FString cloneName) {
	//
	//		cloneThing = new AThing
	//		cloneThing->name = cloneName
	//		
	//		for (child in t->subThings,  childRelTrafo in t->subThingRelTrafos,  childRole in t->subThingRoles) {
	//			cloneThing->subThings.Add(Clone(child))
	//			cloneThing->subThingRelTrafos.Add(FTransform(childRelTrafo))
	//			cloneThing->subThingRoles.Add(childRole)

	AThing* cloneThing = SpawnThingAtom(cloneName);
	
	for (int i = 0; i < t->subThings.Num(); i++) {
		AThing* child = t->subThings[i];
		FTransform childRelTrafo = t->subThingRelTrafos[i];
		FString childRole = t->subThingRoles[i];

		cloneThing->subThings.Add(Clone(child));
		cloneThing->subThingRelTrafos.Add(childRelTrafo);
		cloneThing->subThingRoles.Add(childRole);
	}

	return cloneThing;
}
