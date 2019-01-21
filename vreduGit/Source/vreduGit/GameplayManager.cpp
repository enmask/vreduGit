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
	UE_LOG(LogTemp, Warning, TEXT("AGameplayManager::BeginPlay called, this=%p"), this);

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
	//UE_LOG(LogVredu, Warning, TEXT("AGameplayManager::Tick called, this=%p"), this);
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

	//APop* singlePopAtom = 0;
	//APop* pop2 = 0;

	UWorld* const World = GetWorld();
	AThingManager* theThingManager = ((AvreduGameMode*)World->GetAuthGameMode())->theThingManager;
	APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;


	// Return now, to skip all about the wheels
	//return;


	//
	// Do things like spawning some things/pops in the first call to Tick()
	//
	if (numTicks == 1) {

		// Create a test Pop
		//AThing* AThingManager::SpawnThingAtom(FString name) {
		///UWorld* const World = GetWorld();
		///AThingManager* theThingManager = ((AvreduGameMode*)World->GetAuthGameMode())->theThingManager;
		///APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;
#if 0
		AThing* Atom1 = theThingManager->SpawnThingAtom("ATOM1");
		AThing* Atom2 = theThingManager->SpawnThingAtom("ATOM2");
		AThing* Atom3 = theThingManager->SpawnThingAtom("ATOM3");

		FTransform trafoX0Y0Z1(FQuat(0, 0, 0, 1), FVector(0, 0, 100), FVector(1, 1, 1));

		FTransform trafoX3Y0Z2_2(FQuat(0, 0, 0, 1), FVector(300, 0, 220), FVector(1, 1, 1));
		FTransform trafoX2Y0Z2_1(FQuat(0, 0, 0, 1), FVector(200, 0, 210), FVector(1, 1, 1));
		FTransform trafoX1Y0Z2(FQuat(0, 0, 0, 1), FVector(100, 0, 200), FVector(1, 1, 1));


		//FTransform trafoX1Y0Z2(FQuat(0, 0, 0, 1), FVector(100, 0, 200), FVector(1, 1, 1));
		//FTransform trafoX2Y0Z2_2(FQuat(0, 0, 0, 1), FVector(200, 0, 220), FVector(1, 1, 1));
		//FTransform trafoX3Y0Z2_1(FQuat(0, 0, 0, 1), FVector(300, 0, 210), FVector(1, 1, 1));

		FTransform trafoX5YM10Z1(FQuat(0, 0, 0, 1), FVector(500, -1000, 100), FVector(1, 1, 1));
		singlePopAtom = thePopManager->Spawn(Atom1, trafoX3Y0Z2_2);
		pop2 = thePopManager->Spawn(Atom2, trafoX2Y0Z2_1);
		pop3 = thePopManager->Spawn(Atom3, trafoX1Y0Z2);

		UE_LOG(LogVredu, Warning, TEXT("AGameplayManager::Tick, directly after creation: singlePopAtom=%p, pop2=%p, pop3=%p"),
			   singlePopAtom, pop2, pop3);
#endif

#if 1 /* Hard coded bike */
		AThing* atomSpoke1 = theThingManager->SpawnThingAtom("ATOMSPOKE1");
		AThing* atomSpoke2 = theThingManager->SpawnThingAtom("ATOMSPOKE2");
		AThing* atomSpoke3 = theThingManager->SpawnThingAtom("ATOMSPOKE3");
		AThing* atomSpoke4 = theThingManager->SpawnThingAtom("ATOMSPOKE4");
		AThing* atomSpoke5 = theThingManager->SpawnThingAtom("ATOMSPOKE5");
		AThing* atomSpoke6 = theThingManager->SpawnThingAtom("ATOMSPOKE6");
		AThing* atomSpoke7 = theThingManager->SpawnThingAtom("ATOMSPOKE7");
		AThing* atomSpoke8 = theThingManager->SpawnThingAtom("ATOMSPOKE8");

		AvreduGameMode* theGameMode = GetGameMode();

		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, theGameMode->spoke1Pos), FVector(1, 1, 1));
		FTransform trafoX0_2Y0Z2(FQuat(0, 0, 0, 1), FVector(80, 0, theGameMode->spoke2Pos), FVector(1, 1, 1));
		FTransform trafoX0_3Y0Z2(FQuat(0, 0, 0, 1), FVector(160, 0, theGameMode->spoke3Pos), FVector(1, 1, 1));
		FTransform trafoX0_4Y0Z2(FQuat(0, 0, 0, 1), FVector(240, 0, theGameMode->spoke4Pos), FVector(1, 1, 1));
		FTransform trafoX0_5Y0Z2(FQuat(0, 0, 0, 1), FVector(320, 0, theGameMode->spoke5Pos), FVector(1, 1, 1));
		FTransform trafoX0_6Y0Z2(FQuat(0, 0, 0, 1), FVector(400, 0, theGameMode->spoke6Pos), FVector(1, 1, 1));
		FTransform trafoX0_7Y0Z2(FQuat(0, 0, 0, 1), FVector(480, 0, theGameMode->spoke7Pos), FVector(1, 1, 1));
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(560, 0, theGameMode->spoke8Pos), FVector(1, 1, 1));

		spokePop1 = thePopManager->Spawn(atomSpoke1, trafoX0_1Y0Z2);
		spokePop2 = thePopManager->Spawn(atomSpoke2, trafoX0_2Y0Z2);
		spokePop3 = thePopManager->Spawn(atomSpoke3, trafoX0_3Y0Z2);
		spokePop4 = thePopManager->Spawn(atomSpoke4, trafoX0_4Y0Z2);
		spokePop5 = thePopManager->Spawn(atomSpoke5, trafoX0_5Y0Z2);
		spokePop6 = thePopManager->Spawn(atomSpoke6, trafoX0_6Y0Z2);
		spokePop7 = thePopManager->Spawn(atomSpoke7, trafoX0_7Y0Z2);
		spokePop8 = thePopManager->Spawn(atomSpoke8, trafoX0_8Y0Z2);

#else
	// Create a test Thing
	testThing1 = theThingManager->SpawnThingAtom("Top Thing to clone");
	testThing2 = theThingManager->SpawnThingAtom("Thing 2");
	testThing3 = theThingManager->SpawnThingAtom("Thing 3");
	testThing4 = theThingManager->SpawnThingAtom("Thing 4");
	testThing5 = theThingManager->SpawnThingAtom("Thing 5");

	FTransform trafoX0Y0Z2_4(FQuat(0, 0, 0, 1), FVector(0, 0, 240), FVector(1, 1, 1));
	FTransform trafoX1Y0Z2_3(FQuat(0, 0, 0, 1), FVector(100, 0, 230), FVector(1, 1, 1));
	FTransform trafoX2Y0Z2_2(FQuat(0, 0, 0, 1), FVector(200, 0, 220), FVector(1, 1, 1));
	FTransform trafoX3Y0Z2_1(FQuat(0, 0, 0, 1), FVector(300, 0, 210), FVector(1, 1, 1));
	FTransform trafoX4Y0Z2(FQuat(0, 0, 0, 1), FVector(400, 0, 200), FVector(1, 1, 1));

	testPop1 = thePopManager->Spawn(testThing1, trafoX0Y0Z2_4);

	UE_LOG(LogVredu, Warning, TEXT("\nAGameplayManager::Tick: Got testPop=%p from Spawn!\n"), testPop1);

	testPop2 = thePopManager->Spawn(testThing2, trafoX1Y0Z2_3);
	testPop3 = thePopManager->Spawn(testThing3, trafoX2Y0Z2_2);
	testPop4 = thePopManager->Spawn(testThing4, trafoX3Y0Z2_1);
	testPop5 = thePopManager->Spawn(testThing5, trafoX4Y0Z2);

	UE_LOG(LogVredu, Warning,
		   TEXT("AGameplayManager::Tick, directly after creation: testPop1=%p, testPop2=%p, testPop3=%p, testPop4=%p, testPop5=%p"),
		   testPop1, testPop2, testPop3, testPop4, testPop5);

	UE_LOG(LogVredu, Warning,
		TEXT("AGameplayManager::Tick, directly after creation (2): testPop1=%p, testPop2=%p, testPop3=%p, testPop4=%p, testPop5=%p"),
		testPop1, testPop2, testPop3, testPop4, testPop5);

#endif



	}

	void* ptr1 = testPop1;
	void* ptr2 = testPop2;
	void* ptr3 = testPop3;
	void* ptr4 = testPop4;
	void* ptr5 = testPop5;

	/*
	UE_LOG(LogVredu, Warning,
		TEXT("AGameplayManager::Tick, log every tick, numTicks=%d: testPop1=%p, testPop2=%p, testPop3=%p, testPop4=%p, testPop5=%p, ptr1=%p, ptr2=%p, ptr3=%p, ptr4=%p, ptr5=%p"),
		numTicks, testPop1, testPop2, testPop3, testPop4, testPop5, ptr1, ptr2, ptr3, ptr4, ptr5);

	UE_LOG(LogVredu, Warning,
		TEXT("AGameplayManager::Tick, log every tick (TWO): testPop1=%p, testPop2=%p, testPop3=%p, testPop4=%p, testPop5=%p, ptr1=%p, ptr2=%p, ptr3=%p, ptr4=%p, ptr5=%p"),
		testPop1, testPop2, testPop3, testPop4, testPop5, ptr1, ptr2, ptr3, ptr4, ptr5);

	UE_LOG(LogVredu, Warning,
		TEXT("AGameplayManager::Tick, log every tick (THREE): testPop1=%p, testPop2=%p, testPop3=%p, testPop4=%p, testPop5=%p, ptr1=%p, ptr2=%p, ptr3=%p, ptr4=%p, ptr5=%p"),
		testPop1, testPop2, testPop3, testPop4, testPop5, ptr1, ptr2, ptr3, ptr4, ptr5);
		*/

	AvreduGameMode* theGameMode = GetGameMode();

	if (numTicks == theGameMode->numTicksAddChild) {

		// Add Pop2 as child of Pop1
		///UWorld* const World = GetWorld();
		///AThingManager* theThingManager = ((AvreduGameMode*)World->GetAuthGameMode())->theThingManager;
		///APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;

#if 1

		thePopManager->AddChild(spokePop1, spokePop2);
		thePopManager->AddChild(spokePop1, spokePop3);
		thePopManager->AddChild(spokePop1, spokePop4);
		thePopManager->AddChild(spokePop1, spokePop5);
		thePopManager->AddChild(spokePop1, spokePop6);
		thePopManager->AddChild(spokePop1, spokePop7);
		thePopManager->AddChild(spokePop1, spokePop8);


#else
		//          1
		//        2   5
		//       3 4
		thePopManager->AddChild(testPop2, testPop3);
		thePopManager->AddChild(testPop2, testPop4);
		thePopManager->AddChild(testPop1, testPop2);
		thePopManager->AddChild(testPop1, testPop5);

		// Log the top Pop
		TestLog(testPop1 ? testPop1->ToString() : "Error: testPop1 is null!");
#endif
	}

	if (numTicks == theGameMode->numTicksAddChild + 20) {

		SpawnRod("arod", 3, FVector(100.0, 100.0, 100.0));

	}


#if 0 /* Comment out all rim stuff, partly bc perfomance */

	if (numTicks == 70) {

		///UWorld* const World = GetWorld();
		///AThingManager* theThingManager = ((AvreduGameMode*)World->GetAuthGameMode())->theThingManager;
		///APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;

		//clonePop = thePopManager->Clone(testPop1, "Clone of testPop1");

		spokeClone2 = thePopManager->Clone(spokePop1, "Spoke clone 2");
		spokeClone3 = thePopManager->Clone(spokePop1, "Spoke clone 3");
		spokeClone4 = thePopManager->Clone(spokePop1, "Spoke clone 4");
		spokeClone5 = thePopManager->Clone(spokePop1, "Spoke clone 5");
		spokeClone6 = thePopManager->Clone(spokePop1, "Spoke clone 6");
		spokeClone7 = thePopManager->Clone(spokePop1, "Spoke clone 7");
		spokeClone8 = thePopManager->Clone(spokePop1, "Spoke clone 8");

	}

	//
	// Build a wheel
	//
	if (numTicks == 80) {
		///UWorld* const World = GetWorld();
		///APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;
		thePopManager->RotateAroundLocalY(spokeClone2, 45.0);
	}

	if (numTicks == 85) {
		///UWorld* const World = GetWorld();
		///APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;
		thePopManager->RotateAroundLocalY(spokeClone3, 90.0);
	}

	if (numTicks == 90) {
		///UWorld* const World = GetWorld();
		///APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;
		thePopManager->RotateAroundLocalY(spokeClone4, 135.0);
	}

	if (numTicks == 95) {
		///UWorld* const World = GetWorld();
		///APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;
		thePopManager->RotateAroundLocalY(spokeClone5, 180.0);
	}

	if (numTicks == 100) {
		///UWorld* const World = GetWorld();
		///APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;
		thePopManager->RotateAroundLocalY(spokeClone6, 225.0);
	}

	if (numTicks == 105) {
		///UWorld* const World = GetWorld();
		///APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;
		thePopManager->RotateAroundLocalY(spokeClone7, 270.0);
	}

	if (numTicks == 108) {
		///UWorld* const World = GetWorld();
		///APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;
		thePopManager->RotateAroundLocalY(spokeClone8, 315.0);
	}


#if 0 /* Only one hub thing */
	if (numTicks == 1500) {

		//
		// Build a rim
		//
		atomHub = theThingManager->SpawnThingAtom("ATOMHUB");
		atomRim1 = theThingManager->SpawnThingAtom("ATOMRIM1");
		atomRim2 = theThingManager->SpawnThingAtom("ATOMRIM2");
		atomRim3 = theThingManager->SpawnThingAtom("ATOMRIM3");
		atomRim4 = theThingManager->SpawnThingAtom("ATOMRIM4");
		atomRim5 = theThingManager->SpawnThingAtom("ATOMRIM5");
		atomRim6 = theThingManager->SpawnThingAtom("ATOMRIM6");
		atomRim7 = theThingManager->SpawnThingAtom("ATOMRIM7");
		atomRim8 = theThingManager->SpawnThingAtom("ATOMRIM8");

		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(760, 0, 200), FVector(1, 1, 1));

		hubPop = thePopManager->Spawn(atomHub, trafoX0_1Y0Z2);
		rimPop1 = thePopManager->Spawn(atomRim1, trafoX0_8Y0Z2);
	}

	if (numTicks == 1550) {
		thePopManager->AddChild(hubPop, rimPop1);
	}

	if (numTicks == 1650) {
		thePopManager->RotateAroundLocalY(hubPop, 22.5);
	}

	if (numTicks == 1650) {
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(760, 0, 200), FVector(1, 1, 1));
		rimPop2 = thePopManager->Spawn(atomRim2, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop, rimPop2);
	}
	if (numTicks == 1700) {
		thePopManager->RotateAroundLocalY(hubPop, 22.5);
	}

	if (numTicks == 1750) {
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(760, 0, 200), FVector(1, 1, 1));
		rimPop3 = thePopManager->Spawn(atomRim3, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop, rimPop3);
	}

	if (numTicks == 1800) {
		thePopManager->RotateAroundLocalY(hubPop, 22.5);
	}

	if (numTicks == 1850) {
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(760, 0, 200), FVector(1, 1, 1));
		rimPop4 = thePopManager->Spawn(atomRim4, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop, rimPop4);
	}

	if (numTicks == 1900) {
		thePopManager->RotateAroundLocalY(hubPop, 22.5);
	}

	if (numTicks == 1950) {
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(760, 0, 200), FVector(1, 1, 1));
		rimPop5 = thePopManager->Spawn(atomRim5, trafoX0_8Y0Z2);
	}

	if (numTicks == 2000) {
		thePopManager->RotateAroundLocalY(hubPop, 22.5);
	}
#else /* One hub thing for each rim thing */

	if (numTicks == 110) {

		//
		// Build a rim
		//
		atomHub1 = theThingManager->SpawnThingAtom("ATOMHUB1");
		atomHub2 = theThingManager->SpawnThingAtom("ATOMHUB2");
		atomHub3 = theThingManager->SpawnThingAtom("ATOMHUB3");
		atomHub4 = theThingManager->SpawnThingAtom("ATOMHUB4");
		atomHub5 = theThingManager->SpawnThingAtom("ATOMHUB5");
		atomHub6 = theThingManager->SpawnThingAtom("ATOMHUB6");
		atomHub7 = theThingManager->SpawnThingAtom("ATOMHUB7");
		atomHub8 = theThingManager->SpawnThingAtom("ATOMHUB8");
		atomHub9 = theThingManager->SpawnThingAtom("ATOMHUB9");
		atomHub10 = theThingManager->SpawnThingAtom("ATOMHUB10");
		atomHub11 = theThingManager->SpawnThingAtom("ATOMHUB11");
		atomHub12 = theThingManager->SpawnThingAtom("ATOMHUB12");
		atomHub13 = theThingManager->SpawnThingAtom("ATOMHUB13");
		atomHub14 = theThingManager->SpawnThingAtom("ATOMHUB14");
		atomHub15 = theThingManager->SpawnThingAtom("ATOMHUB15");
		atomHub16 = theThingManager->SpawnThingAtom("ATOMHUB16");
		atomHub17 = theThingManager->SpawnThingAtom("ATOMHUB17");
		atomHub18 = theThingManager->SpawnThingAtom("ATOMHUB18");
		atomHub19 = theThingManager->SpawnThingAtom("ATOMHUB19");
		atomHub20 = theThingManager->SpawnThingAtom("ATOMHUB20");
		atomHub21 = theThingManager->SpawnThingAtom("ATOMHUB21");
		atomHub22 = theThingManager->SpawnThingAtom("ATOMHUB22");
		atomHub23 = theThingManager->SpawnThingAtom("ATOMHUB23");
		atomHub24 = theThingManager->SpawnThingAtom("ATOMHUB24");
		atomHub25 = theThingManager->SpawnThingAtom("ATOMHUB25");
		atomHub26 = theThingManager->SpawnThingAtom("ATOMHUB26");
		atomHub27 = theThingManager->SpawnThingAtom("ATOMHUB27");
		atomHub28 = theThingManager->SpawnThingAtom("ATOMHUB28");
		atomHub29 = theThingManager->SpawnThingAtom("ATOMHUB29");
		atomHub30 = theThingManager->SpawnThingAtom("ATOMHUB30");
		atomHub31 = theThingManager->SpawnThingAtom("ATOMHUB31");
		atomHub32 = theThingManager->SpawnThingAtom("ATOMHUB32");
		atomHub33 = theThingManager->SpawnThingAtom("ATOMHUB33");
		atomHub34 = theThingManager->SpawnThingAtom("ATOMHUB34");
		atomHub35 = theThingManager->SpawnThingAtom("ATOMHUB35");
		atomHub36 = theThingManager->SpawnThingAtom("ATOMHUB36");
		atomHub37 = theThingManager->SpawnThingAtom("ATOMHUB37");
		atomHub38 = theThingManager->SpawnThingAtom("ATOMHUB38");
		atomHub39 = theThingManager->SpawnThingAtom("ATOMHUB39");
		atomHub40 = theThingManager->SpawnThingAtom("ATOMHUB40");
		atomHub41 = theThingManager->SpawnThingAtom("ATOMHUB41");
		atomHub42 = theThingManager->SpawnThingAtom("ATOMHUB42");
		atomHub43 = theThingManager->SpawnThingAtom("ATOMHUB43");
		atomHub44 = theThingManager->SpawnThingAtom("ATOMHUB44");
		atomHub45 = theThingManager->SpawnThingAtom("ATOMHUB45");
		atomHub46 = theThingManager->SpawnThingAtom("ATOMHUB46");
		atomHub47 = theThingManager->SpawnThingAtom("ATOMHUB47");
		atomHub48 = theThingManager->SpawnThingAtom("ATOMHUB48");
		atomHub49 = theThingManager->SpawnThingAtom("ATOMHUB49");
		atomHub50 = theThingManager->SpawnThingAtom("ATOMHUB50");
		atomHub51 = theThingManager->SpawnThingAtom("ATOMHUB51");
		atomHub52 = theThingManager->SpawnThingAtom("ATOMHUB52");
		atomHub53 = theThingManager->SpawnThingAtom("ATOMHUB53");
		atomHub54 = theThingManager->SpawnThingAtom("ATOMHUB54");
		atomHub55 = theThingManager->SpawnThingAtom("ATOMHUB55");
		atomHub56 = theThingManager->SpawnThingAtom("ATOMHUB56");
		atomHub57 = theThingManager->SpawnThingAtom("ATOMHUB57");
		atomHub58 = theThingManager->SpawnThingAtom("ATOMHUB58");
		atomHub59 = theThingManager->SpawnThingAtom("ATOMHUB59");
		atomHub60 = theThingManager->SpawnThingAtom("ATOMHUB60");
		atomHub61 = theThingManager->SpawnThingAtom("ATOMHUB61");
		atomHub62 = theThingManager->SpawnThingAtom("ATOMHUB62");
		atomHub63 = theThingManager->SpawnThingAtom("ATOMHUB63");
		atomHub64 = theThingManager->SpawnThingAtom("ATOMHUB64");

		atomRim1 = theThingManager->SpawnThingAtom("ATOMRIM1");
		atomRim2 = theThingManager->SpawnThingAtom("ATOMRIM2");
		atomRim3 = theThingManager->SpawnThingAtom("ATOMRIM3");
		atomRim4 = theThingManager->SpawnThingAtom("ATOMRIM4");
		atomRim5 = theThingManager->SpawnThingAtom("ATOMRIM5");
		atomRim6 = theThingManager->SpawnThingAtom("ATOMRIM6");
		atomRim7 = theThingManager->SpawnThingAtom("ATOMRIM7");
		atomRim8 = theThingManager->SpawnThingAtom("ATOMRIM8");
		atomRim9 = theThingManager->SpawnThingAtom("ATOMRIM9");
		atomRim10 = theThingManager->SpawnThingAtom("ATOMRIM10");
		atomRim11 = theThingManager->SpawnThingAtom("ATOMRIM11");
		atomRim12 = theThingManager->SpawnThingAtom("ATOMRIM12");
		atomRim13 = theThingManager->SpawnThingAtom("ATOMRIM13");
		atomRim14 = theThingManager->SpawnThingAtom("ATOMRIM14");
		atomRim15 = theThingManager->SpawnThingAtom("ATOMRIM15");
		atomRim16 = theThingManager->SpawnThingAtom("ATOMRIM16");
		atomRim17 = theThingManager->SpawnThingAtom("ATOMRIM17");
		atomRim18 = theThingManager->SpawnThingAtom("ATOMRIM18");
		atomRim19 = theThingManager->SpawnThingAtom("ATOMRIM19");
		atomRim20 = theThingManager->SpawnThingAtom("ATOMRIM20");
		atomRim21 = theThingManager->SpawnThingAtom("ATOMRIM21");
		atomRim22 = theThingManager->SpawnThingAtom("ATOMRIM22");
		atomRim23 = theThingManager->SpawnThingAtom("ATOMRIM23");
		atomRim24 = theThingManager->SpawnThingAtom("ATOMRIM24");
		atomRim25 = theThingManager->SpawnThingAtom("ATOMRIM25");
		atomRim26 = theThingManager->SpawnThingAtom("ATOMRIM26");
		atomRim27 = theThingManager->SpawnThingAtom("ATOMRIM27");
		atomRim28 = theThingManager->SpawnThingAtom("ATOMRIM28");
		atomRim29 = theThingManager->SpawnThingAtom("ATOMRIM29");
		atomRim30 = theThingManager->SpawnThingAtom("ATOMRIM30");
		atomRim31 = theThingManager->SpawnThingAtom("ATOMRIM31");
		atomRim32 = theThingManager->SpawnThingAtom("ATOMRIM32");
		atomRim33 = theThingManager->SpawnThingAtom("ATOMRIM33");
		atomRim34 = theThingManager->SpawnThingAtom("ATOMRIM34");
		atomRim35 = theThingManager->SpawnThingAtom("ATOMRIM35");
		atomRim36 = theThingManager->SpawnThingAtom("ATOMRIM36");
		atomRim37 = theThingManager->SpawnThingAtom("ATOMRIM37");
		atomRim38 = theThingManager->SpawnThingAtom("ATOMRIM38");
		atomRim39 = theThingManager->SpawnThingAtom("ATOMRIM39");
		atomRim40 = theThingManager->SpawnThingAtom("ATOMRIM40");
		atomRim41 = theThingManager->SpawnThingAtom("ATOMRIM41");
		atomRim42 = theThingManager->SpawnThingAtom("ATOMRIM42");
		atomRim43 = theThingManager->SpawnThingAtom("ATOMRIM43");
		atomRim44 = theThingManager->SpawnThingAtom("ATOMRIM44");
		atomRim45 = theThingManager->SpawnThingAtom("ATOMRIM45");
		atomRim46 = theThingManager->SpawnThingAtom("ATOMRIM46");
		atomRim47 = theThingManager->SpawnThingAtom("ATOMRIM47");
		atomRim48 = theThingManager->SpawnThingAtom("ATOMRIM48");
		atomRim49 = theThingManager->SpawnThingAtom("ATOMRIM49");
		atomRim50 = theThingManager->SpawnThingAtom("ATOMRIM50");
		atomRim51 = theThingManager->SpawnThingAtom("ATOMRIM51");
		atomRim52 = theThingManager->SpawnThingAtom("ATOMRIM52");
		atomRim53 = theThingManager->SpawnThingAtom("ATOMRIM53");
		atomRim54 = theThingManager->SpawnThingAtom("ATOMRIM54");
		atomRim55 = theThingManager->SpawnThingAtom("ATOMRIM55");
		atomRim56 = theThingManager->SpawnThingAtom("ATOMRIM56");
		atomRim57 = theThingManager->SpawnThingAtom("ATOMRIM57");
		atomRim58 = theThingManager->SpawnThingAtom("ATOMRIM58");
		atomRim59 = theThingManager->SpawnThingAtom("ATOMRIM59");
		atomRim60 = theThingManager->SpawnThingAtom("ATOMRIM60");
		atomRim61 = theThingManager->SpawnThingAtom("ATOMRIM61");
		atomRim62 = theThingManager->SpawnThingAtom("ATOMRIM62");
		atomRim63 = theThingManager->SpawnThingAtom("ATOMRIM63");
		atomRim64 = theThingManager->SpawnThingAtom("ATOMRIM64");
	
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));

		//
		// Rim parts 1-8. Part 1 rotates 0 degrees
		//

		hubPop1 = thePopManager->Spawn(atomHub1, trafoX0_1Y0Z2);
		rimPop1 = thePopManager->Spawn(atomRim1, trafoX0_8Y0Z2);
	}

	if (numTicks == 112) {
		thePopManager->AddChild(hubPop1, rimPop1);
	}

	if (numTicks == 114) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop2 = thePopManager->Spawn(atomHub2, trafoX0_1Y0Z2);
		rimPop2 = thePopManager->Spawn(atomRim2, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop2, rimPop2);
	}

	if (numTicks == 116) {
		thePopManager->RotateAroundLocalY(hubPop2, 22.5/4.0);
	}

	if (numTicks == 118) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop3 = thePopManager->Spawn(atomHub3, trafoX0_1Y0Z2);
		rimPop3 = thePopManager->Spawn(atomRim3, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop3, rimPop3);
	}

	if (numTicks == 120) {
		thePopManager->RotateAroundLocalY(hubPop3, 45.0/4.0);
	}

	if (numTicks == 122) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop4 = thePopManager->Spawn(atomHub4, trafoX0_1Y0Z2);
		rimPop4 = thePopManager->Spawn(atomRim4, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop4, rimPop4);
	}

	if (numTicks == 124) {
		thePopManager->RotateAroundLocalY(hubPop4, 67.5/4.0);
	}

	if (numTicks == 126) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop5 = thePopManager->Spawn(atomHub5, trafoX0_1Y0Z2);
		rimPop5 = thePopManager->Spawn(atomRim5, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop5, rimPop5);
	}

	if (numTicks == 128) {
		thePopManager->RotateAroundLocalY(hubPop5, 90.0/4.0);
	}

	if (numTicks == 130) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop6 = thePopManager->Spawn(atomHub6, trafoX0_1Y0Z2);
		rimPop6 = thePopManager->Spawn(atomRim6, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop6, rimPop6);
	}

	if (numTicks == 132) {
		thePopManager->RotateAroundLocalY(hubPop6, 112.5/4.0);
	}

	if (numTicks == 134) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop7 = thePopManager->Spawn(atomHub7, trafoX0_1Y0Z2);
		rimPop7 = thePopManager->Spawn(atomRim7, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop7, rimPop7);
	}

	if (numTicks == 136) {
		thePopManager->RotateAroundLocalY(hubPop7, 135.0/4.0);
	}

	if (numTicks == 138) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop8 = thePopManager->Spawn(atomHub8, trafoX0_1Y0Z2);
		rimPop8 = thePopManager->Spawn(atomRim8, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop8, rimPop8);
	}

	if (numTicks == 140) {
		thePopManager->RotateAroundLocalY(hubPop8, 157.5/4.0);
	}

	// Rim parts 9-16. Part 9 rotates 0+180/4=45 degrees
	if (numTicks == 142) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop9 = thePopManager->Spawn(atomHub9, trafoX0_1Y0Z2);
		rimPop9 = thePopManager->Spawn(atomRim9, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop9, rimPop9);
	}

	if (numTicks == 144) {
		thePopManager->RotateAroundLocalY(hubPop9, 180.0/4.0);
	}

	if (numTicks == 146) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop10 = thePopManager->Spawn(atomHub10, trafoX0_1Y0Z2);
		rimPop10 = thePopManager->Spawn(atomRim10, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop10, rimPop10);
	}

	if (numTicks == 148) {
		thePopManager->RotateAroundLocalY(hubPop10, 202.5/4.0);
	}

	if (numTicks == 150) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop11 = thePopManager->Spawn(atomHub11, trafoX0_1Y0Z2);
		rimPop11 = thePopManager->Spawn(atomRim11, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop11, rimPop11);
	}

	if (numTicks == 152) {
		thePopManager->RotateAroundLocalY(hubPop11, 225.0/4.0);
	}

	if (numTicks == 154) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop12 = thePopManager->Spawn(atomHub12, trafoX0_1Y0Z2);
		rimPop12 = thePopManager->Spawn(atomRim12, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop12, rimPop12);
	}

	if (numTicks == 156) {
		thePopManager->RotateAroundLocalY(hubPop12, 247.5/4.0);
	}

	if (numTicks == 158) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop13 = thePopManager->Spawn(atomHub13, trafoX0_1Y0Z2);
		rimPop13 = thePopManager->Spawn(atomRim13, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop13, rimPop13);
	}

	if (numTicks == 160) {
		thePopManager->RotateAroundLocalY(hubPop13, 270.0/4.0);
	}

	if (numTicks == 162) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop14 = thePopManager->Spawn(atomHub14, trafoX0_1Y0Z2);
		rimPop14 = thePopManager->Spawn(atomRim14, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop14, rimPop14);
	}

	if (numTicks == 164) {
		thePopManager->RotateAroundLocalY(hubPop14, 292.5/4.0);
	}

	if (numTicks == 166) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop15 = thePopManager->Spawn(atomHub15, trafoX0_1Y0Z2);
		rimPop15 = thePopManager->Spawn(atomRim15, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop15, rimPop15);
	}

	if (numTicks == 168) {
		thePopManager->RotateAroundLocalY(hubPop15, 315.0/4.0);
	}

	if (numTicks == 170) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop16 = thePopManager->Spawn(atomHub16, trafoX0_1Y0Z2);
		rimPop16 = thePopManager->Spawn(atomRim16, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop16, rimPop16);
	}

	if (numTicks == 172) {
		thePopManager->RotateAroundLocalY(hubPop16, 337.5/4.0);
	}

	//
	// [ok]Rim parts 17-24. Part 17 rotates 45+180/4=45+45=90 degrees
	//
	if (numTicks == 174) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop17 = thePopManager->Spawn(atomHub17, trafoX0_1Y0Z2);
		rimPop17 = thePopManager->Spawn(atomRim17, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop17, rimPop17);
	}

	if (numTicks == 176) {
		thePopManager->RotateAroundLocalY(hubPop17, 360.0/4.0);
	}

	if (numTicks == 178) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop18 = thePopManager->Spawn(atomHub18, trafoX0_1Y0Z2);
		rimPop18 = thePopManager->Spawn(atomRim18, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop18, rimPop18);
	}

	if (numTicks == 180) {
		thePopManager->RotateAroundLocalY(hubPop18, 382.5/4.0);
	}

	if (numTicks == 182) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop19 = thePopManager->Spawn(atomHub19, trafoX0_1Y0Z2);
		rimPop19 = thePopManager->Spawn(atomRim19, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop19, rimPop19);
	}

	if (numTicks == 184) {
		thePopManager->RotateAroundLocalY(hubPop19, 405.0/4.0);
	}

	if (numTicks == 186) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop20 = thePopManager->Spawn(atomHub20, trafoX0_1Y0Z2);
		rimPop20 = thePopManager->Spawn(atomRim20, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop20, rimPop20);
	}

	if (numTicks == 188) {
		thePopManager->RotateAroundLocalY(hubPop20, 427.5/4.0);
	}

	if (numTicks == 190) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop21 = thePopManager->Spawn(atomHub21, trafoX0_1Y0Z2);
		rimPop21 = thePopManager->Spawn(atomRim21, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop21, rimPop21);
	}

	if (numTicks == 192) {
		thePopManager->RotateAroundLocalY(hubPop21, 450.0/4.0);
	}

	if (numTicks == 194) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop22 = thePopManager->Spawn(atomHub22, trafoX0_1Y0Z2);
		rimPop22 = thePopManager->Spawn(atomRim22, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop22, rimPop22);
	}

	if (numTicks == 196) {
		thePopManager->RotateAroundLocalY(hubPop22, 472.5/4.0);
	}

	if (numTicks == 198) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop23 = thePopManager->Spawn(atomHub23, trafoX0_1Y0Z2);
		rimPop23 = thePopManager->Spawn(atomRim23, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop23, rimPop23);
	}

	if (numTicks == 200) {
		thePopManager->RotateAroundLocalY(hubPop23, 495.0/4.0);
	}

	if (numTicks == 202) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop24 = thePopManager->Spawn(atomHub24, trafoX0_1Y0Z2);
		rimPop24 = thePopManager->Spawn(atomRim24, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop24, rimPop24);
	}

	if (numTicks == 204) {
		thePopManager->RotateAroundLocalY(hubPop24, 517.5/4.0);
	}

	//
	// [ok]Rim parts 25-32. Part 25 rotates 90+180/4=90+45=135 degrees
	//
	if (numTicks == 206) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop25 = thePopManager->Spawn(atomHub25, trafoX0_1Y0Z2);
		rimPop25 = thePopManager->Spawn(atomRim25, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop25, rimPop25);
	}

	if (numTicks == 208) {
		thePopManager->RotateAroundLocalY(hubPop25, 540.0/4.0);
	}

	if (numTicks == 210) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop26 = thePopManager->Spawn(atomHub26, trafoX0_1Y0Z2);
		rimPop26 = thePopManager->Spawn(atomRim26, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop26, rimPop26);
	}

	if (numTicks == 212) {
		thePopManager->RotateAroundLocalY(hubPop26, 562.5/4.0);
	}

	if (numTicks == 214) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop27 = thePopManager->Spawn(atomHub27, trafoX0_1Y0Z2);
		rimPop27 = thePopManager->Spawn(atomRim27, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop27, rimPop27);
	}

	if (numTicks == 216) {
		thePopManager->RotateAroundLocalY(hubPop27, 585.0/4.0);
	}

	if (numTicks == 218) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop28 = thePopManager->Spawn(atomHub28, trafoX0_1Y0Z2);
		rimPop28 = thePopManager->Spawn(atomRim28, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop28, rimPop28);
	}

	if (numTicks == 220) {
		thePopManager->RotateAroundLocalY(hubPop28, 607.5/4.0);
	}

	if (numTicks == 222) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop29 = thePopManager->Spawn(atomHub29, trafoX0_1Y0Z2);
		rimPop29 = thePopManager->Spawn(atomRim29, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop29, rimPop29);
	}

	if (numTicks == 224) {
		thePopManager->RotateAroundLocalY(hubPop29, 630.0/4.0);
	}

	if (numTicks == 226) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop30 = thePopManager->Spawn(atomHub30, trafoX0_1Y0Z2);
		rimPop30 = thePopManager->Spawn(atomRim30, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop30, rimPop30);
	}

	if (numTicks == 228) {
		thePopManager->RotateAroundLocalY(hubPop30, 652.5/4.0);
	}

	if (numTicks == 230) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop31 = thePopManager->Spawn(atomHub31, trafoX0_1Y0Z2);
		rimPop31 = thePopManager->Spawn(atomRim31, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop31, rimPop31);
	}

	if (numTicks == 232) {
		thePopManager->RotateAroundLocalY(hubPop31, 675.0/4.0);
	}

	if (numTicks == 234) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop32 = thePopManager->Spawn(atomHub32, trafoX0_1Y0Z2);
		rimPop32 = thePopManager->Spawn(atomRim32, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop32, rimPop32);
	}

	if (numTicks == 236) {
		thePopManager->RotateAroundLocalY(hubPop32, 697.5/4.0);
	}

	//
	// [ok]Rim parts 33-48. Part 33 rotates 135+180/4=135+45=180 degrees
	//
	if (numTicks == 238) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop33 = thePopManager->Spawn(atomHub33, trafoX0_1Y0Z2);
		rimPop33 = thePopManager->Spawn(atomRim33, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop33, rimPop33);
	}

	if (numTicks == 240) {
		thePopManager->RotateAroundLocalY(hubPop33, 720.0/4.0);
	}

	if (numTicks == 242) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop34 = thePopManager->Spawn(atomHub34, trafoX0_1Y0Z2);
		rimPop34 = thePopManager->Spawn(atomRim34, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop34, rimPop34);
	}

	if (numTicks == 244) {
		thePopManager->RotateAroundLocalY(hubPop34, 742.5/4.0);
	}

	if (numTicks == 246) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop35 = thePopManager->Spawn(atomHub35, trafoX0_1Y0Z2);
		rimPop35 = thePopManager->Spawn(atomRim35, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop35, rimPop35);
	}

	if (numTicks == 248) {
		thePopManager->RotateAroundLocalY(hubPop35, 765.0/4.0);
	}

	if (numTicks == 250) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop36 = thePopManager->Spawn(atomHub36, trafoX0_1Y0Z2);
		rimPop36 = thePopManager->Spawn(atomRim36, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop36, rimPop36);
	}

	if (numTicks == 252) {
		thePopManager->RotateAroundLocalY(hubPop36, 787.5/4.0);
	}

	if (numTicks == 254) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop37 = thePopManager->Spawn(atomHub37, trafoX0_1Y0Z2);
		rimPop37 = thePopManager->Spawn(atomRim37, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop37, rimPop37);
	}

	if (numTicks == 256) {
		thePopManager->RotateAroundLocalY(hubPop37, 810.0/4.0);
	}

	if (numTicks == 258) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop38 = thePopManager->Spawn(atomHub38, trafoX0_1Y0Z2);
		rimPop38 = thePopManager->Spawn(atomRim38, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop38, rimPop38);
	}

	if (numTicks == 260) {
		thePopManager->RotateAroundLocalY(hubPop38, 832.5/4.0);
	}

	if (numTicks == 262) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop39 = thePopManager->Spawn(atomHub39, trafoX0_1Y0Z2);
		rimPop39 = thePopManager->Spawn(atomRim39, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop39, rimPop39);
	}

	if (numTicks == 264) {
		thePopManager->RotateAroundLocalY(hubPop39, 855.0/4.0);
	}

	if (numTicks == 268) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop40 = thePopManager->Spawn(atomHub40, trafoX0_1Y0Z2);
		rimPop40 = thePopManager->Spawn(atomRim40, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop40, rimPop40);
	}

	if (numTicks == 270) {
		thePopManager->RotateAroundLocalY(hubPop40, 877.5/4.0);
	}

	//
	// [ok]Rim parts 41-48. Part 41 rotates 180+180/4=180+45=225 degrees
	//
	if (numTicks == 272) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop41 = thePopManager->Spawn(atomHub41, trafoX0_1Y0Z2);
		rimPop41 = thePopManager->Spawn(atomRim41, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop41, rimPop41);
	}

	if (numTicks == 274) {
		thePopManager->RotateAroundLocalY(hubPop41, 900.0/4.0);
	}

	if (numTicks == 276) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop42 = thePopManager->Spawn(atomHub42, trafoX0_1Y0Z2);
		rimPop42 = thePopManager->Spawn(atomRim42, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop42, rimPop42);
	}
	
	if (numTicks == 278) {
		thePopManager->RotateAroundLocalY(hubPop42, 922.5/4.0);
	}

	if (numTicks == 280) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop43 = thePopManager->Spawn(atomHub43, trafoX0_1Y0Z2);
		rimPop43 = thePopManager->Spawn(atomRim43, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop43, rimPop43);
	}

	if (numTicks == 282) {
		thePopManager->RotateAroundLocalY(hubPop43, 945.0/4.0);
	}

	if (numTicks == 284) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop44 = thePopManager->Spawn(atomHub44, trafoX0_1Y0Z2);
		rimPop44 = thePopManager->Spawn(atomRim44, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop44, rimPop44);
	}

	if (numTicks == 286) {
		thePopManager->RotateAroundLocalY(hubPop44, 967.5/4.0);
	}

	if (numTicks == 288) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop45 = thePopManager->Spawn(atomHub45, trafoX0_1Y0Z2);
		rimPop45 = thePopManager->Spawn(atomRim45, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop45, rimPop45);
	}

	if (numTicks == 290) {
		thePopManager->RotateAroundLocalY(hubPop45, 990.0/4.0);
	}

	if (numTicks == 292) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop46 = thePopManager->Spawn(atomHub46, trafoX0_1Y0Z2);
		rimPop46 = thePopManager->Spawn(atomRim46, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop46, rimPop46);
	}

	if (numTicks == 294) {
		thePopManager->RotateAroundLocalY(hubPop46, 1012.5/4.0);
	}

	if (numTicks == 296) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop47 = thePopManager->Spawn(atomHub47, trafoX0_1Y0Z2);
		rimPop47 = thePopManager->Spawn(atomRim47, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop47, rimPop47);
	}

	if (numTicks == 298) {
		thePopManager->RotateAroundLocalY(hubPop47, 1035.0/4.0);
	}

	if (numTicks == 300) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop48 = thePopManager->Spawn(atomHub48, trafoX0_1Y0Z2);
		rimPop48 = thePopManager->Spawn(atomRim48, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop48, rimPop48);
	}

	if (numTicks == 302) {
		thePopManager->RotateAroundLocalY(hubPop48, 1057.5/4.0);
	}

	//
	// [ok]Rim parts 49-56. Part 49 rotates 225+180/4=225+45=270 degrees
	//
	if (numTicks == 304) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop49 = thePopManager->Spawn(atomHub49, trafoX0_1Y0Z2);
		rimPop49 = thePopManager->Spawn(atomRim49, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop49, rimPop49);
	}

	if (numTicks == 306) {
		thePopManager->RotateAroundLocalY(hubPop49, 1080.0/4.0);
	}

	if (numTicks == 308) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop50 = thePopManager->Spawn(atomHub50, trafoX0_1Y0Z2);
		rimPop50 = thePopManager->Spawn(atomRim50, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop50, rimPop50);
	}

	if (numTicks == 310) {
		thePopManager->RotateAroundLocalY(hubPop50, 1102.5/4.0);
	}

	if (numTicks == 312) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop51 = thePopManager->Spawn(atomHub51, trafoX0_1Y0Z2);
		rimPop51 = thePopManager->Spawn(atomRim51, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop51, rimPop51);
	}

	if (numTicks == 314) {
		thePopManager->RotateAroundLocalY(hubPop51, 1125.0/4.0);
	}

	if (numTicks == 316) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop52 = thePopManager->Spawn(atomHub52, trafoX0_1Y0Z2);
		rimPop52 = thePopManager->Spawn(atomRim52, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop52, rimPop52);
	}

	if (numTicks == 318) {
		thePopManager->RotateAroundLocalY(hubPop52, 1147.5/4.0);
	}

	if (numTicks == 320) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop53 = thePopManager->Spawn(atomHub53, trafoX0_1Y0Z2);
		rimPop53 = thePopManager->Spawn(atomRim53, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop53, rimPop53);
	}

	if (numTicks == 322) {
		thePopManager->RotateAroundLocalY(hubPop53, 1170.0/4.0);
	}

	if (numTicks == 324) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop54 = thePopManager->Spawn(atomHub54, trafoX0_1Y0Z2);
		rimPop54 = thePopManager->Spawn(atomRim54, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop54, rimPop54);
	}

	if (numTicks == 326) {
		thePopManager->RotateAroundLocalY(hubPop54, 1192.5/4.0);
	}

	if (numTicks == 328) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop55 = thePopManager->Spawn(atomHub55, trafoX0_1Y0Z2);
		rimPop55 = thePopManager->Spawn(atomRim55, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop55, rimPop55);
	}

	if (numTicks == 330) {
		thePopManager->RotateAroundLocalY(hubPop55, 1215.0/4.0);
	}

	if (numTicks == 332) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop56 = thePopManager->Spawn(atomHub56, trafoX0_1Y0Z2);
		rimPop56 = thePopManager->Spawn(atomRim56, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop56, rimPop56);
	}

	if (numTicks == 334) {
		thePopManager->RotateAroundLocalY(hubPop56, 1237.5/4.0);
	}

	if (numTicks == 336) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop57 = thePopManager->Spawn(atomHub57, trafoX0_1Y0Z2);
		rimPop57 = thePopManager->Spawn(atomRim57, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop57, rimPop57);
	}

	if (numTicks == 338) {
		thePopManager->RotateAroundLocalY(hubPop57, 1260.0/4.0);
	}

	if (numTicks == 340) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop58 = thePopManager->Spawn(atomHub58, trafoX0_1Y0Z2);
		rimPop58 = thePopManager->Spawn(atomRim58, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop58, rimPop58);
	}

	if (numTicks == 342) {
		thePopManager->RotateAroundLocalY(hubPop58, 1282.5/4.0);
	}

	//
	// Rim parts 57-64. Part 57 rotates 270+180/4=270+45=315 degrees
	//
	if (numTicks == 344) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop59 = thePopManager->Spawn(atomHub59, trafoX0_1Y0Z2);
		rimPop59 = thePopManager->Spawn(atomRim59, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop59, rimPop59);
	}

	if (numTicks == 346) {
		thePopManager->RotateAroundLocalY(hubPop59, 1305.0/4.0);
	}

	if (numTicks == 348) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop60 = thePopManager->Spawn(atomHub60, trafoX0_1Y0Z2);
		rimPop60 = thePopManager->Spawn(atomRim60, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop60, rimPop60);
	}

	if (numTicks == 350) {
		thePopManager->RotateAroundLocalY(hubPop60, 1327.5/4.0);
	}

	if (numTicks == 352) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop61 = thePopManager->Spawn(atomHub61, trafoX0_1Y0Z2);
		rimPop61 = thePopManager->Spawn(atomRim61, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop61, rimPop61);
	}

	if (numTicks == 354) {
		thePopManager->RotateAroundLocalY(hubPop61, 1350.0/4.0);
	}

	if (numTicks == 356) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop62 = thePopManager->Spawn(atomHub62, trafoX0_1Y0Z2);
		rimPop62 = thePopManager->Spawn(atomRim62, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop62, rimPop62);
	}

	if (numTicks == 358) {
		thePopManager->RotateAroundLocalY(hubPop62, 1372.5/4.0);
	}

	if (numTicks == 360) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop63 = thePopManager->Spawn(atomHub63, trafoX0_1Y0Z2);
		rimPop63 = thePopManager->Spawn(atomRim63, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop63, rimPop63);
	}

	if (numTicks == 362) {
		thePopManager->RotateAroundLocalY(hubPop63, 1395.0/4.0);
	}

	if (numTicks == 364) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		//                                       Return to (560, 0, 200)
		FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(640, 0, 200), FVector(1, 1, 1));
		hubPop64 = thePopManager->Spawn(atomHub64, trafoX0_1Y0Z2);
		rimPop64 = thePopManager->Spawn(atomRim64, trafoX0_8Y0Z2);
		thePopManager->AddChild(hubPop64, rimPop64);
	}

	if (numTicks == 366) {
		thePopManager->RotateAroundLocalY(hubPop64, 1417.5/4.0);
	}


	//
	// Make each hubPopXX child of a single hubPop
	//

	if (numTicks == 380) {

		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		atomHub = theThingManager->SpawnThingAtom("ATOMHUB AND RIM THING");
		hubPop = thePopManager->Spawn(atomHub, trafoX0_1Y0Z2);

		thePopManager->AddChild(hubPop, hubPop1);
		thePopManager->AddChild(hubPop, hubPop2);
		thePopManager->AddChild(hubPop, hubPop3);
		thePopManager->AddChild(hubPop, hubPop4);
		thePopManager->AddChild(hubPop, hubPop5);
		thePopManager->AddChild(hubPop, hubPop6);
		thePopManager->AddChild(hubPop, hubPop7);
		thePopManager->AddChild(hubPop, hubPop8);
		thePopManager->AddChild(hubPop, hubPop9);
		thePopManager->AddChild(hubPop, hubPop10);
		thePopManager->AddChild(hubPop, hubPop11);
		thePopManager->AddChild(hubPop, hubPop12);
		thePopManager->AddChild(hubPop, hubPop13);
		thePopManager->AddChild(hubPop, hubPop14);
		thePopManager->AddChild(hubPop, hubPop15);
		thePopManager->AddChild(hubPop, hubPop16);
		thePopManager->AddChild(hubPop, hubPop17);
		thePopManager->AddChild(hubPop, hubPop18);
		thePopManager->AddChild(hubPop, hubPop19);
		thePopManager->AddChild(hubPop, hubPop20);
		thePopManager->AddChild(hubPop, hubPop21);
		thePopManager->AddChild(hubPop, hubPop22);
		thePopManager->AddChild(hubPop, hubPop23);
		thePopManager->AddChild(hubPop, hubPop24);
		thePopManager->AddChild(hubPop, hubPop25);
		thePopManager->AddChild(hubPop, hubPop26);
		thePopManager->AddChild(hubPop, hubPop27);
		thePopManager->AddChild(hubPop, hubPop28);
		thePopManager->AddChild(hubPop, hubPop29);
		thePopManager->AddChild(hubPop, hubPop30);
		thePopManager->AddChild(hubPop, hubPop31);
		thePopManager->AddChild(hubPop, hubPop32);
		thePopManager->AddChild(hubPop, hubPop33);
		thePopManager->AddChild(hubPop, hubPop34);
		thePopManager->AddChild(hubPop, hubPop35);
		thePopManager->AddChild(hubPop, hubPop36);
		thePopManager->AddChild(hubPop, hubPop37);
		thePopManager->AddChild(hubPop, hubPop38);
		thePopManager->AddChild(hubPop, hubPop39);
		thePopManager->AddChild(hubPop, hubPop40);
		thePopManager->AddChild(hubPop, hubPop41);
		thePopManager->AddChild(hubPop, hubPop42);
		thePopManager->AddChild(hubPop, hubPop43);
		thePopManager->AddChild(hubPop, hubPop44);
		thePopManager->AddChild(hubPop, hubPop45);
		thePopManager->AddChild(hubPop, hubPop46);
		thePopManager->AddChild(hubPop, hubPop47);
		thePopManager->AddChild(hubPop, hubPop48);
		thePopManager->AddChild(hubPop, hubPop49);
		thePopManager->AddChild(hubPop, hubPop50);
		thePopManager->AddChild(hubPop, hubPop51);
		thePopManager->AddChild(hubPop, hubPop52);
		thePopManager->AddChild(hubPop, hubPop53);
		thePopManager->AddChild(hubPop, hubPop54);
		thePopManager->AddChild(hubPop, hubPop55);
		thePopManager->AddChild(hubPop, hubPop56);
		thePopManager->AddChild(hubPop, hubPop57);
		thePopManager->AddChild(hubPop, hubPop58);
		thePopManager->AddChild(hubPop, hubPop59);
		thePopManager->AddChild(hubPop, hubPop60);
		thePopManager->AddChild(hubPop, hubPop61);
		thePopManager->AddChild(hubPop, hubPop62);
		thePopManager->AddChild(hubPop, hubPop63);
		thePopManager->AddChild(hubPop, hubPop64);

	}

#endif

#if 0 /* Comment out to let spokes stay separate from the rim */
	//
	// Make the spokes children of a single spokesPop
	//
	if (numTicks == 390) {

		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		spokesThing = theThingManager->SpawnThingAtom("SPOKES THING");
		spokesPop = thePopManager->Spawn(spokesThing, trafoX0_1Y0Z2);

		thePopManager->AddChild(spokesPop, spokePop1);
		thePopManager->AddChild(spokesPop, spokeClone2);
		thePopManager->AddChild(spokesPop, spokeClone3);
		thePopManager->AddChild(spokesPop, spokeClone4);
		thePopManager->AddChild(spokesPop, spokeClone5);
		thePopManager->AddChild(spokesPop, spokeClone6);
		thePopManager->AddChild(spokesPop, spokeClone7);
		thePopManager->AddChild(spokesPop, spokeClone8);
	}

	//
	// Make the spokesPop and hubPop children of a wheelPop
	//
	if (numTicks == 395) {
		FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, 200), FVector(1, 1, 1));
		wheelThing = theThingManager->SpawnThingAtom("WHEEL THING");
		wheelPop = thePopManager->Spawn(wheelThing, trafoX0_1Y0Z2);

		thePopManager->AddChild(wheelPop, spokesPop);
		thePopManager->AddChild(wheelPop, hubPop);
	}

	//
	// Make another wheel
	//
	if (numTicks == 400) {
		FTransform trafoX9Y0Z2(FQuat(0, 0, 0, 1), FVector(900, 0, 200), FVector(1, 1, 1));

		wheel2Thing = theThingManager->SpawnThingAtom("WHEEL 2 THING");
		//wheel2Pop = thePopManager->Spawn(wheel2Thing, trafoX9Y0Z2);

		//spokeClone2 = thePopManager->Clone(spokePop1, "Spoke clone 2");

		// Clone wheel
		wheel2Pop = thePopManager->Clone(wheelPop, "Wheel 2 Pop");

		// Position clone wheel to one side
		FVector cloneWheelLoc = wheel2Pop->GetActorLocation();
		wheel2Pop->SetActorLocation(FVector(cloneWheelLoc.X + 900.0, cloneWheelLoc.Y, cloneWheelLoc.Z));

		// Make the wheels children of the bike
		FTransform trafoX4Y0Z2(FQuat(0, 0, 0, 1), FVector(400, 0, 200), FVector(1, 1, 1));
		bikeThing = theThingManager->SpawnThingAtom("BIKE POP");
		bikePop = thePopManager->Spawn(bikeThing, trafoX4Y0Z2);
		thePopManager->AddChild(bikePop, wheelPop);
		thePopManager->AddChild(bikePop, wheel2Pop);

	}

	// Rotate one or both wheels...
	//thePopManager->RotateAroundLocalY(spokeClone2, 45.0);


	//
	// Test: Move the bike along the x
	//
	if (numTicks > 420 && numTicks < 600) {
		FVector bikeLoc = bikePop->GetActorLocation();
		bikeLoc.X = bikeLoc.X + 2.0f;
		bikePop->SetActorLocation(bikeLoc);

	}
#endif


#endif

}




APop* AGameplayManager::SpawnRod(FString name, int length, FVector loc) {

	AvreduGameMode* theGameMode = GetGameMode();
	AThingManager* theThingManager = theGameMode->theThingManager;
	APopManager* thePopManager = theGameMode->thePopManager;
	TArray <AThing*> rodThings;
	TArray <APop*> rodPops;

	for (int i = 0; i < length; ++i) {
		rodThings.Add(theThingManager->SpawnThingAtom(name + "atom" + FString::FromInt(i)));

		FVector locI = FVector(loc.X + 50 * i, loc.Y, loc.Z);
		FTransform trafo(FQuat(0, 0, 0, 1), locI, FVector(1, 1, 1));
		rodPops.Add(thePopManager->Spawn(rodThings[i], trafo));
		if (i > 0)
			thePopManager->AddChild(rodPops[0], rodPops[i]);
	}

	return rodPops[0];

#if 0
	AThing* atomSpoke1 = theThingManager->SpawnThingAtom("ATOMSPOKE1");
	AThing* atomSpoke2 = theThingManager->SpawnThingAtom("ATOMSPOKE2");
	AThing* atomSpoke3 = theThingManager->SpawnThingAtom("ATOMSPOKE3");
	AThing* atomSpoke4 = theThingManager->SpawnThingAtom("ATOMSPOKE4");
	AThing* atomSpoke5 = theThingManager->SpawnThingAtom("ATOMSPOKE5");
	AThing* atomSpoke6 = theThingManager->SpawnThingAtom("ATOMSPOKE6");
	AThing* atomSpoke7 = theThingManager->SpawnThingAtom("ATOMSPOKE7");
	AThing* atomSpoke8 = theThingManager->SpawnThingAtom("ATOMSPOKE8");

	AvreduGameMode* theGameMode = GetGameMode();

	FTransform trafoX0_1Y0Z2(FQuat(0, 0, 0, 1), FVector(0, 0, theGameMode->spoke1Pos), FVector(1, 1, 1));
	FTransform trafoX0_2Y0Z2(FQuat(0, 0, 0, 1), FVector(80, 0, theGameMode->spoke2Pos), FVector(1, 1, 1));
	FTransform trafoX0_3Y0Z2(FQuat(0, 0, 0, 1), FVector(160, 0, theGameMode->spoke3Pos), FVector(1, 1, 1));
	FTransform trafoX0_4Y0Z2(FQuat(0, 0, 0, 1), FVector(240, 0, theGameMode->spoke4Pos), FVector(1, 1, 1));
	FTransform trafoX0_5Y0Z2(FQuat(0, 0, 0, 1), FVector(320, 0, theGameMode->spoke5Pos), FVector(1, 1, 1));
	FTransform trafoX0_6Y0Z2(FQuat(0, 0, 0, 1), FVector(400, 0, theGameMode->spoke6Pos), FVector(1, 1, 1));
	FTransform trafoX0_7Y0Z2(FQuat(0, 0, 0, 1), FVector(480, 0, theGameMode->spoke7Pos), FVector(1, 1, 1));
	FTransform trafoX0_8Y0Z2(FQuat(0, 0, 0, 1), FVector(560, 0, theGameMode->spoke8Pos), FVector(1, 1, 1));

	spokePop1 = thePopManager->Spawn(atomSpoke1, trafoX0_1Y0Z2);
	spokePop2 = thePopManager->Spawn(atomSpoke2, trafoX0_2Y0Z2);
	spokePop3 = thePopManager->Spawn(atomSpoke3, trafoX0_3Y0Z2);
	spokePop4 = thePopManager->Spawn(atomSpoke4, trafoX0_4Y0Z2);
	spokePop5 = thePopManager->Spawn(atomSpoke5, trafoX0_5Y0Z2);
	spokePop6 = thePopManager->Spawn(atomSpoke6, trafoX0_6Y0Z2);
	spokePop7 = thePopManager->Spawn(atomSpoke7, trafoX0_7Y0Z2);
	spokePop8 = thePopManager->Spawn(atomSpoke8, trafoX0_8Y0Z2);

	FTransform trafoX0Y0Z2_4(FQuat(0, 0, 0, 1), FVector(0, 0, 240), FVector(1, 1, 1));
	FTransform trafoX1Y0Z2_3(FQuat(0, 0, 0, 1), FVector(100, 0, 230), FVector(1, 1, 1));
	FTransform trafoX2Y0Z2_2(FQuat(0, 0, 0, 1), FVector(200, 0, 220), FVector(1, 1, 1));
	FTransform trafoX3Y0Z2_1(FQuat(0, 0, 0, 1), FVector(300, 0, 210), FVector(1, 1, 1));
	FTransform trafoX4Y0Z2(FQuat(0, 0, 0, 1), FVector(400, 0, 200), FVector(1, 1, 1));

	AvreduGameMode* theGameMode = GetGameMode();

	thePopManager->AddChild(spokePop1, spokePop2);
	thePopManager->AddChild(spokePop1, spokePop3);
	thePopManager->AddChild(spokePop1, spokePop4);
	thePopManager->AddChild(spokePop1, spokePop5);
	thePopManager->AddChild(spokePop1, spokePop6);
	thePopManager->AddChild(spokePop1, spokePop7);
	thePopManager->AddChild(spokePop1, spokePop8);
#endif
}










AvreduGameMode* AGameplayManager::GetGameMode() {
	UWorld* const theWorld = GetWorld();

	verify(theWorld != nullptr);

	return Cast<AvreduGameMode>(theWorld->GetAuthGameMode());
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
	APopManager* thePopManager = ((AvreduGameMode*)World->GetAuthGameMode())->thePopManager;

	// Create a test Thing
	AThing* testThing1 = theThingManager->SpawnThingAtom("Top Thing to clone");
	AThing* testThing2 = theThingManager->SpawnThingAtom("Thing 2");
	AThing* testThing3 = theThingManager->SpawnThingAtom("Thing 3");
	AThing* testThing4 = theThingManager->SpawnThingAtom("Thing 4");
	AThing* testThing5 = theThingManager->SpawnThingAtom("Thing 5");

	FTransform trafoX0Y0Z2_4(FQuat(0, 0, 0, 1), FVector(0, 0, 240), FVector(1, 1, 1));
	FTransform trafoX1Y0Z2_3(FQuat(0, 0, 0, 1), FVector(100, 0, 230), FVector(1, 1, 1));
	FTransform trafoX2Y0Z2_2(FQuat(0, 0, 0, 1), FVector(200, 0, 220), FVector(1, 1, 1));
	FTransform trafoX3Y0Z2_1(FQuat(0, 0, 0, 1), FVector(300, 0, 210), FVector(1, 1, 1));
	FTransform trafoX4Y0Z2(FQuat(0, 0, 0, 1), FVector(400, 0, 200), FVector(1, 1, 1));

	APop* testPop1 = thePopManager->Spawn(testThing1, trafoX0Y0Z2_4);
	APop* testPop2 = thePopManager->Spawn(testThing2, trafoX1Y0Z2_3);
	APop* testPop3 = thePopManager->Spawn(testThing3, trafoX2Y0Z2_2);
	APop* testPop4 = thePopManager->Spawn(testThing4, trafoX3Y0Z2_1);
	APop* testPop5 = thePopManager->Spawn(testThing5, trafoX4Y0Z2);

	//          1
	//        2   5
	//       3 4
	thePopManager->AddChild(testPop2, testPop3);
	thePopManager->AddChild(testPop2, testPop4);
	thePopManager->AddChild(testPop1, testPop2);
	thePopManager->AddChild(testPop1, testPop5);

	// Log the top Pop
	TestLog(testPop1 ? testPop1->ToString() : "Error: testPop1 is null!");
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