// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Thing.h"
#include "ThingManager.generated.h"

UCLASS()
class VREDUGIT_API AThingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThingManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AThing* SpawnThingAtom(FString name);
	
};



#if 0 /* Old code from other project */
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Thing.h"
#include "ThingComp.h"
//#include "Pop.h"
#include "ThingManager.generated.h"

UCLASS()
class VREDU_1_THING_API AThingManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AThingManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AThingComp* SpawnThingAtom(FString name);
	UStaticMesh* MeshCube;
};
#endif