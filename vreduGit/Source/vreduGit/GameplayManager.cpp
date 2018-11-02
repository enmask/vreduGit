// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayManager.h"
#include "vreduGameMode.h"
#include "Util.h"

// Sets default values
AGameplayManager::AGameplayManager()
{
	UE_LOG(LogTemp, Warning, TEXT("AGameplayManager constructor *is* called"));

	UWorld* const World = GetWorld();
	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("AGameplayManager constructor: World exists"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AGameplayManager constructor: World does NOT exist"));
	}

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameplayManager::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("AGameplayManager::BeginPlay called"));

	Super::BeginPlay();

	UWorld* const World = GetWorld();
	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("AGameplayManager::BeginPlay: World exists"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AGameplayManager::BeginPlay: World does NOT exist"));
	}

	CheckIfTestRun();

	calledTestCase = false;
	numTicks = 0;
}


// Called every frame
void AGameplayManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	numTicks++;

#if 0
	if (FParse::Param(FCommandLine::Get(), TEXT("runtestcase1")))
	{
		UE_LOG(LogVredu, Warning, TEXT("AThing::BeginPlay: Found runtestcase1 in the command line"));
	}
	if (FParse::Param(FCommandLine::Get(), TEXT("runtestcase2")))
	{
		UE_LOG(LogVredu, Warning, TEXT("AThing::BeginPlay: Found runtestcase2 in the command line"));
	}
	if (FParse::Param(FCommandLine::Get(), TEXT("runtestcase3")))
	{
		UE_LOG(LogVredu, Warning, TEXT("AThing::BeginPlay: Found runtestcase3 in the command line"));
	}
#endif

	if (doRunATestCase) {

		/*
		//integer
		if (FParse::Value(FCommandLine::Get(), TEXT("startPose"), startPose)) {
			_startPose = startPose;
		}
		*/
		
		if (!calledTestCase) {
			TestLog(FString("Running test case " + FString::FromInt(testCaseNo)));
			CallTestCase(testCaseNo);
			calledTestCase = true;
		}
		else if (numTicks > testCaseNumTicks) {

				//TestLog(TEXT("Finished test case %d"), testCaseNo);
				TestLog(FString("Finished test case " + FString::FromInt(testCaseNo)));

				// Exit the program, because the specified number of ticks have passed
				FGenericPlatformMisc::RequestExit(false);
		}
	}
}

void AGameplayManager::CheckIfTestRun() {

	doRunATestCase = false;
	if (FParse::Value(FCommandLine::Get(), TEXT("testcaseno"), testCaseNo)) {
		doRunATestCase = true;

		if (!FParse::Value(FCommandLine::Get(), TEXT("testcasenumticks"), testCaseNumTicks)) {
			UE_LOG(LogVredu, Warning, TEXT("AThing::CheckIfTestRun: Error: testcasenumticks command line argument missing!"));
		}
	}


	//UE_LOG(LogVredu, Warning,
	//	TEXT("AThing::CheckIfTestRun: test logging: doRunATestCase=%s"), doRunATestCase ? TEXT("true") : TEXT("false"));
	//UE_LOG(LogVredu, Warning, TEXT("AThing::CheckIfTestRun: test logging: testCaseNo=%d"), testCaseNo);
	//UE_LOG(LogVredu, Warning, TEXT("AThing::CheckIfTestRun: test logging: testCaseNumTicks=%d"), testCaseNumTicks);

}


void AGameplayManager::CallTestCase(int testNo) {

	switch (testNo) {
		case 1: TestCase1();
				break;
		case 2: TestCase2();
				break;
		case 3: TestCase3();
				break;
		default:
				UE_LOG(LogVredu,
					   Warning,
					   TEXT("AThing::CallTestCase(): Error: test case %d does not exist"),
					   testCaseNo);
				break;
	}

}

void AGameplayManager::TestCase1() {

	UWorld* const World = GetWorld();
	AThingManager* theThingManager = ((AvreduGameMode*)World->GetAuthGameMode())->theThingManager;

	// Create a test Thing
	AThing* testThing = theThingManager->SpawnThingAtom("TestCase1 Thing");

	// Log the test Thing
	TestLog(testThing ? testThing->ToString() : "Error: testThing is null!");
}

void AGameplayManager::TestCase2() {

	UWorld* const World = GetWorld();
	AThingManager* theThingManager = ((AvreduGameMode*)World->GetAuthGameMode())->theThingManager;

	// Create a test Thing
	AThing* testThing = theThingManager->SpawnThingAtom("TestCase2 Thing");

	AThing* testThing2 = theThingManager->SpawnThingAtom("TestCase2 Thing2");
	AThing* testThing3 = theThingManager->SpawnThingAtom("TestCase2 Thing3");

	FTransform trafo;
	testThing->Add(testThing2, trafo, "Role of testThing2");
	testThing->Add(testThing3, trafo, "Role of testThing3");

	// Log the test Thing
	TestLog(testThing ? testThing->ToString() : "Error: testThing is null!");
}

void AGameplayManager::TestCase3() {

	UWorld* const World = GetWorld();
	AThingManager* theThingManager = ((AvreduGameMode*)World->GetAuthGameMode())->theThingManager;

	// Create a test Thing
	AThing* testThing = theThingManager->SpawnThingAtom("TestCase3 Thing");

	AThing* testThing2 = theThingManager->SpawnThingAtom("TestCase3 Thing2");
	AThing* testThing3 = theThingManager->SpawnThingAtom("TestCase3 Thing3");
	AThing* testThing4 = theThingManager->SpawnThingAtom("TestCase3 Thing4");

	FTransform trafo;
	testThing->Add(testThing2, trafo, "Role of testThing2");
	testThing->Add(testThing3, trafo, "Role of testThing3");
	testThing->Add(testThing3, trafo, "Role of testThing4");

	// Log the test Thing
	TestLog(testThing ? testThing->ToString() : "Error: testThing is null!");
}

void AGameplayManager::TestLog(FString logText) {

	UE_LOG(LogVredu, Warning, TEXT("%s"), *logText)
		
}

