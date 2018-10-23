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
	Super::BeginPlay();
	
}

// Called every frame
void AThingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

