// Fill out your copyright notice in the Description page of Project Settings.

#include "FallingActor.h"


// Sets default values
AFallingActor::AFallingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FallingActor mesh"));
	USceneComponent* meshSC = Cast<USceneComponent>(mesh);
	//RootComponent = meshSC;
	SetRootComponent(meshSC);
	//CustomMeshComponent = CreateDefaultSubobject(TEXT("Test Component"));
	//mesh->AttachTo(RootComponent);


	bool simPhys = mesh->IsSimulatingPhysics();
	bool simPhys2 = mesh->IsAnySimulatingPhysics();
	UE_LOG(LogTemp, Warning, TEXT("AFallingActor constructor: Before mesh->SetSimulatePhysics(false):  simPhys1=%s, simPhys2=%s"),
		simPhys ? TEXT("true") : TEXT("false"),
		simPhys2 ? TEXT("true") : TEXT("false"));

	mesh->SetSimulatePhysics(false);

	bool simPhys3 = mesh->IsSimulatingPhysics();
	bool simPhys4 = mesh->IsAnySimulatingPhysics();
	UE_LOG(LogTemp, Warning, TEXT("AFallingActor constructor: After mesh->SetSimulatePhysics(false), before (true):  simPhys3=%s, simPhys4=%s"),
		simPhys3 ? TEXT("true") : TEXT("false"),
		simPhys4 ? TEXT("true") : TEXT("false"));

	mesh->SetSimulatePhysics(true);

	bool simPhys5 = mesh->IsSimulatingPhysics();
	bool simPhys6 = mesh->IsAnySimulatingPhysics();
	UE_LOG(LogTemp, Warning, TEXT("AFallingActor constructor: After mesh->SetSimulatePhysics(true):  simPhys5=%s, simPhys6=%s"),
		simPhys5 ? TEXT("true") : TEXT("false"),
		simPhys6 ? TEXT("true") : TEXT("false"));

	mesh->SetSimulatePhysics(false);

	bool simPhys7 = mesh->IsSimulatingPhysics();
	bool simPhys8 = mesh->IsAnySimulatingPhysics();
	UE_LOG(LogTemp, Warning, TEXT("AFallingActor constructor: After mesh->SetSimulatePhysics(true):  simPhys7=%s, simPhys8=%s"),
		simPhys7 ? TEXT("true") : TEXT("false"),
		simPhys8 ? TEXT("true") : TEXT("false"));

}

// Called when the game starts or when spawned
void AFallingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFallingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

