// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pop.h"
#include "PopManager.generated.h"

UCLASS()
class VREDUGIT_API APopManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APopManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APop* Spawn(AThing* thing, FTransform transform);
	
	// NYI
	//APop* Clone(APop* origPop, FString cloneName);
};
