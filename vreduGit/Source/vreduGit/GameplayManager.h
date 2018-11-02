// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayManager.generated.h"

UCLASS()
class VREDUGIT_API AGameplayManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameplayManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void CheckIfTestRun();

	UFUNCTION()
		void CallTestCase(int testNo);

	UFUNCTION()
		void TestCase1();

	UFUNCTION()
		void TestCase2();

	UFUNCTION()
		void TestCase3();

	UFUNCTION()
		void TestLog(FString logText);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		bool calledTestCase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		bool doRunATestCase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		int testCaseNo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		int testCaseNumTicks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		int numTicks;
};
