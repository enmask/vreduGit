// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayManager.h"
#include "vreduGameMode.h"
#include "Util.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

//#define HARDCODE_TEST_CASE_1
//#define HARDCODE_TEST_CASE_2
//#define HARDCODE_TEST_CASE_3


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
	UE_LOG(LogVredu, Warning, TEXT("AGameplayManager::Tick called"));
	Super::Tick(DeltaTime);
	numTicks++;

	if (doRunATestCase) {
	
		if (!calledTestCase) {
			TestLog(FString("Running test case " + FString::FromInt(testCaseNo)));
			CallTestCase(testCaseNo);
			calledTestCase = true;
		}
		else if (numTicks > testCaseNumTicks) {

				//TestLog(TEXT("Finished test case %d"), testCaseNo);
				TestLog(FString("Finished test case " + FString::FromInt(testCaseNo)));

				TestLogWrite();

				// Exit the program, because the specified number of ticks have passed
				FGenericPlatformMisc::RequestExit(false);
		}
	}

	//
	// Do things like spawning some things/pops in the first call to Tick()
	//
	if (numTicks == 1) {
		// Create a test Pop
		//AThing* AThingManager::SpawnThingAtom(FString name) {
		UWorld* const World = GetWorld();
		AThingManager* theThingManager = ((AvreduGameMode*)World->GetAuthGameMode())->theThingManager;
		APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;
		AThing* Atom = theThingManager->SpawnThingAtom("ATOM");
		FTransform trafoX0Y0Z1(FQuat(0, 0, 0, 1), FVector(0, 0, 100), FVector(1, 1, 1));
		FTransform trafoX5YM10Z1(FQuat(0, 0, 0, 1), FVector(500, -1000, 100), FVector(1, 1, 1));
		APop* PSinglePopAtom = thePopManager->Spawn(Atom, trafoX5YM10Z1);
	}



}

void AGameplayManager::CheckIfTestRun() {

	UE_LOG(LogVredu, Warning, TEXT("AGameplayManager::CheckIfTestRun called"));


#ifdef HARDCODE_TEST_CASE_1
	doRunATestCase = true;
	testCaseNo = 1;
	testCaseNumTicks = 100;
	UE_LOG(LogVredu, Warning, TEXT("CheckIfTestRun: test logging: Hard coded testCaseNo %d"), testCaseNo);
	return;
#endif

#ifdef HARDCODE_TEST_CASE_2
	doRunATestCase = true;
	testCaseNo = 2;
	testCaseNumTicks = 1000; // Was 200
	UE_LOG(LogVredu, Warning, TEXT("CheckIfTestRun: test logging: Hard coded testCaseNo %d"), testCaseNo);
	return;
#endif

#ifdef HARDCODE_TEST_CASE_3
	doRunATestCase = true;
	testCaseNo = 3;
	testCaseNumTicks = 300;
	UE_LOG(LogVredu, Warning, TEXT("CheckIfTestRun: test logging: Hard coded testCaseNo %d"), testCaseNo);
	return;
#endif


//#define HARDCODE_TEST_CASE 2
#ifdef HARDCODE_TEST_CASE
	doRunATestCase = true;
#if HARD_CODE_TEST_CASE == 1
	testCaseNo = 1;
#elif HARD_CODE_TEST_CASE == 2
	testCaseNo = 2;
#else
	testCaseNo = 3;
#endif
	testCaseNumTicks = 100;
	UE_LOG(LogVredu, Warning, TEXT("CheckIfTestRun: test logging: Hard coded testCaseNo %d"), testCaseNo);
	return;
#endif

	doRunATestCase = false;

	// 	AThingManager* theThingManager = ((AvreduGameMode*)World->GetAuthGameMode())->theThingManager;

	UWorld* const World = GetWorld();
	AvreduGameMode* gameMode = (AvreduGameMode*)World->GetAuthGameMode();

	if (gameMode->autotestInEditor) {
		UE_LOG(LogVredu,
			   Warning,
			   TEXT("CheckIfTestRun: gameMode->autotestInEditor is true, gameMode->autotestNo=%d"),
			   gameMode->autotestNo);
	}
	else {
		UE_LOG(LogVredu, Warning, TEXT("CheckIfTestRun: gameMode->autotestInEditor is false, gameMode->autotestNo=%d"),
			   gameMode->autotestNo);
	}



	if (gameMode->autotestInEditor) {

		//
		// Setup autotesting in-editor
		//

		doRunATestCase = true;
		testCaseNo = gameMode->autotestNo;
		testCaseNumTicks = gameMode->autotestNumTicks;

		UE_LOG(LogVredu,
			   Warning,
			   TEXT("CheckIfTestRun: WE WILL AUTOTEST IN-EDITOR. testCaseNo=%d, testCaseNumTicks=%d"),
			   testCaseNo, testCaseNumTicks);

	} else if (FParse::Value(FCommandLine::Get(), TEXT("testcaseno"), testCaseNo)) {

		//
		// Setup autotesting for texttest
		//

		doRunATestCase = true;

		if (!FParse::Value(FCommandLine::Get(), TEXT("testcasenumticks"), testCaseNumTicks)) {
			UE_LOG(LogVredu, Warning, TEXT("CheckIfTestRun: Error: testcasenumticks command line argument missing!"));
		}
	}
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
					   TEXT("CallTestCase(): Error: test case %d does not exist"),
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
	APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;

	// Create a test Thing
	AThing* testThing = theThingManager->SpawnThingAtom("TestCase2 Thing");
	FTransform trafo(FVector(0.0f, 0.0f, 1000.0f));

	UE_LOG(LogTemp, Warning, TEXT("AGameplayManager::TestCase2: will call thePopManager->Spawn"));
	UE_LOG(LogVredu, Warning, TEXT("AGameplayManager::TestCase2: will call thePopManager->Spawn"));

	APop* testPop = thePopManager->Spawn(testThing, trafo);

	// Log the test Thing
	TestLog(testThing ? testThing->ToString() : "Error: testThing is null!");

	// Log the test Pop
	TestLog(testPop ? testPop->ToString() : "Error: testPop is null!");

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

	UE_LOG(LogVredu, Warning, TEXT("%s"), *logText);
	inEditorTestLogText += logText + "\n";

	UE_LOG(LogVredu, Warning, TEXT("Full inEditorTestLogText is now: %s"), *inEditorTestLogText);

}


void AGameplayManager::TestLogWrite() {

	// TEST, write a text file after test
	FString SaveDirectory = FString("C:/Users/Magnus/tmp");

	//FString FileName = FString(TEXT("LogVredu_test_%d.txt"), testCaseNo);

	FString FileName = FString::Printf(TEXT("LogVredu_test_%d.txt"), testCaseNo);



	//FString TextToSave = FString("Lorem ipsum");

	bool AllowOverwriting = true;
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	// CreateDirectoryTree returns true if the destination
	// directory existed prior to call or has been created
	// during the call.
	if (PlatformFile.CreateDirectoryTree(*SaveDirectory)) {
		// Get absolute file path
		FString AbsoluteFilePath = SaveDirectory + "/" + FileName;
		// Allow overwriting or file doesn't already exist
		if (AllowOverwriting || !PlatformFile.FileExists(*AbsoluteFilePath)) {
			FFileHelper::SaveStringToFile(inEditorTestLogText, *AbsoluteFilePath);
		}
	}

}