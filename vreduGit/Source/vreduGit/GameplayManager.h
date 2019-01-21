// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayManager.generated.h"

class AThing;
class APop;
class AvreduGameMode;

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

	AvreduGameMode* GetGameMode();

	APop* SpawnRod(FString name, int length, FVector loc);

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

	UFUNCTION()
		void TestLogWrite();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		bool calledTestCase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		FString inEditorTestLogText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		bool doRunATestCase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		int testCaseNo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		int testCaseNumTicks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		int numTicks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		APop* singlePopAtom = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		APop* pop2 = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		APop* pop3 = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		AThing* testThing1 = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		AThing* testThing2 = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		AThing* testThing3 = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		AThing* testThing4 = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		AThing* testThing5 = 0;

#if 0
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VR")
		APop* testPop1 = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VR")
		APop* testPop2 = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VR")
		APop* testPop3 = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VR")
		APop* testPop4 = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VR")
		APop* testPop5 = 0;
#endif

private:

	APop* testPop1 = 0;
	APop* testPop2 = 0;
	APop* testPop3 = 0;
	APop* testPop4 = 0;
	APop* testPop5 = 0;

	APop* clonePop = 0;

	APop* spokePop1 = 0;
	APop* spokePop2 = 0;
	APop* spokePop3 = 0;
	APop* spokePop4 = 0;
	APop* spokePop5 = 0;
	APop* spokePop6 = 0;
	APop* spokePop7 = 0;
	APop* spokePop8 = 0;

	APop* spokeClone2 = 0;
	APop* spokeClone3 = 0;
	APop* spokeClone4 = 0;
	APop* spokeClone5 = 0;
	APop* spokeClone6 = 0;
	APop* spokeClone7 = 0;
	APop* spokeClone8 = 0;

	AThing* spokesThing = 0;
	APop* spokesPop = 0;

	AThing* atomHub = 0;

	AThing* atomHub1 = 0;
	AThing* atomHub2 = 0;
	AThing* atomHub3 = 0;
	AThing* atomHub4 = 0;
	AThing* atomHub5 = 0;
	AThing* atomHub6 = 0;
	AThing* atomHub7 = 0;
	AThing* atomHub8 = 0;
	AThing* atomHub9 = 0;
	AThing* atomHub10 = 0;
	AThing* atomHub11 = 0;
	AThing* atomHub12 = 0;
	AThing* atomHub13 = 0;
	AThing* atomHub14 = 0;
	AThing* atomHub15 = 0;
	AThing* atomHub16 = 0;
	AThing* atomHub17 = 0;
	AThing* atomHub18 = 0;
	AThing* atomHub19 = 0;
	AThing* atomHub20 = 0;
	AThing* atomHub21 = 0;
	AThing* atomHub22 = 0;
	AThing* atomHub23 = 0;
	AThing* atomHub24 = 0;
	AThing* atomHub25 = 0;
	AThing* atomHub26 = 0;
	AThing* atomHub27 = 0;
	AThing* atomHub28 = 0;
	AThing* atomHub29 = 0;
	AThing* atomHub30 = 0;
	AThing* atomHub31 = 0;
	AThing* atomHub32 = 0;
	AThing* atomHub33 = 0;
	AThing* atomHub34 = 0;
	AThing* atomHub35 = 0;
	AThing* atomHub36 = 0;
	AThing* atomHub37 = 0;
	AThing* atomHub38 = 0;
	AThing* atomHub39 = 0;
	AThing* atomHub40 = 0;
	AThing* atomHub41 = 0;
	AThing* atomHub42 = 0;
	AThing* atomHub43 = 0;
	AThing* atomHub44 = 0;
	AThing* atomHub45 = 0;
	AThing* atomHub46 = 0;
	AThing* atomHub47 = 0;
	AThing* atomHub48 = 0;
	AThing* atomHub49 = 0;
	AThing* atomHub50 = 0;
	AThing* atomHub51 = 0;
	AThing* atomHub52 = 0;
	AThing* atomHub53 = 0;
	AThing* atomHub54 = 0;
	AThing* atomHub55 = 0;
	AThing* atomHub56 = 0;
	AThing* atomHub57 = 0;
	AThing* atomHub58 = 0;
	AThing* atomHub59 = 0;
	AThing* atomHub60 = 0;
	AThing* atomHub61 = 0;
	AThing* atomHub62 = 0;
	AThing* atomHub63 = 0;
	AThing* atomHub64 = 0;

	AThing* atomRim1 = 0;
	AThing* atomRim2 = 0;
	AThing* atomRim3 = 0;
	AThing* atomRim4 = 0;
	AThing* atomRim5 = 0;
	AThing* atomRim6 = 0;
	AThing* atomRim7 = 0;
	AThing* atomRim8 = 0;
	AThing* atomRim9 = 0;
	AThing* atomRim10 = 0;
	AThing* atomRim11 = 0;
	AThing* atomRim12 = 0;
	AThing* atomRim13 = 0;
	AThing* atomRim14 = 0;
	AThing* atomRim15 = 0;
	AThing* atomRim16 = 0;
	AThing* atomRim17 = 0;
	AThing* atomRim18 = 0;
	AThing* atomRim19 = 0;
	AThing* atomRim20 = 0;
	AThing* atomRim21 = 0;
	AThing* atomRim22 = 0;
	AThing* atomRim23 = 0;
	AThing* atomRim24 = 0;
	AThing* atomRim25 = 0;
	AThing* atomRim26 = 0;
	AThing* atomRim27 = 0;
	AThing* atomRim28 = 0;
	AThing* atomRim29 = 0;
	AThing* atomRim30 = 0;
	AThing* atomRim31 = 0;
	AThing* atomRim32 = 0;
	AThing* atomRim33 = 0;
	AThing* atomRim34 = 0;
	AThing* atomRim35 = 0;
	AThing* atomRim36 = 0;
	AThing* atomRim37 = 0;
	AThing* atomRim38 = 0;
	AThing* atomRim39 = 0;
	AThing* atomRim40 = 0;
	AThing* atomRim41 = 0;
	AThing* atomRim42 = 0;
	AThing* atomRim43 = 0;
	AThing* atomRim44 = 0;
	AThing* atomRim45 = 0;
	AThing* atomRim46 = 0;
	AThing* atomRim47 = 0;
	AThing* atomRim48 = 0;
	AThing* atomRim49 = 0;
	AThing* atomRim50 = 0;
	AThing* atomRim51 = 0;
	AThing* atomRim52 = 0;
	AThing* atomRim53 = 0;
	AThing* atomRim54 = 0;
	AThing* atomRim55 = 0;
	AThing* atomRim56 = 0;
	AThing* atomRim57 = 0;
	AThing* atomRim58 = 0;
	AThing* atomRim59 = 0;
	AThing* atomRim60 = 0;
	AThing* atomRim61 = 0;
	AThing* atomRim62 = 0;
	AThing* atomRim63 = 0;
	AThing* atomRim64 = 0;

	APop* hubPop = 0;
	APop* hubPop1 = 0;
	APop* hubPop2 = 0;
	APop* hubPop3 = 0;
	APop* hubPop4 = 0;
	APop* hubPop5 = 0;
	APop* hubPop6 = 0;
	APop* hubPop7 = 0;
	APop* hubPop8 = 0;
	APop* hubPop9 = 0;
	APop* hubPop10 = 0;
	APop* hubPop11 = 0;
	APop* hubPop12 = 0;
	APop* hubPop13 = 0;
	APop* hubPop14 = 0;
	APop* hubPop15 = 0;
	APop* hubPop16 = 0;
	APop* hubPop17 = 0;
	APop* hubPop18 = 0;
	APop* hubPop19 = 0;
	APop* hubPop20 = 0;
	APop* hubPop21 = 0;
	APop* hubPop22 = 0;
	APop* hubPop23 = 0;
	APop* hubPop24 = 0;
	APop* hubPop25 = 0;
	APop* hubPop26 = 0;
	APop* hubPop27 = 0;
	APop* hubPop28 = 0;
	APop* hubPop29 = 0;
	APop* hubPop30 = 0;
	APop* hubPop31 = 0;
	APop* hubPop32 = 0;
	APop* hubPop33 = 0;
	APop* hubPop34 = 0;
	APop* hubPop35 = 0;
	APop* hubPop36 = 0;
	APop* hubPop37 = 0;
	APop* hubPop38 = 0;
	APop* hubPop39 = 0;
	APop* hubPop40 = 0;
	APop* hubPop41 = 0;
	APop* hubPop42 = 0;
	APop* hubPop43 = 0;
	APop* hubPop44 = 0;
	APop* hubPop45 = 0;
	APop* hubPop46 = 0;
	APop* hubPop47 = 0;
	APop* hubPop48 = 0;
	APop* hubPop49 = 0;
	APop* hubPop50 = 0;
	APop* hubPop51 = 0;
	APop* hubPop52 = 0;
	APop* hubPop53 = 0;
	APop* hubPop54 = 0;
	APop* hubPop55 = 0;
	APop* hubPop56 = 0;
	APop* hubPop57 = 0;
	APop* hubPop58 = 0;
	APop* hubPop59 = 0;
	APop* hubPop60 = 0;
	APop* hubPop61 = 0;
	APop* hubPop62 = 0;
	APop* hubPop63 = 0;
	APop* hubPop64 = 0;

	APop* rimPop1 = 0;
	APop* rimPop2 = 0;
	APop* rimPop3 = 0;
	APop* rimPop4 = 0;
	APop* rimPop5 = 0;
	APop* rimPop6 = 0;
	APop* rimPop7 = 0;
	APop* rimPop8 = 0;
	APop* rimPop9 = 0;
	APop* rimPop10 = 0;
	APop* rimPop11 = 0;
	APop* rimPop12 = 0;
	APop* rimPop13 = 0;
	APop* rimPop14 = 0;
	APop* rimPop15 = 0;
	APop* rimPop16 = 0;
	APop* rimPop17 = 0;
	APop* rimPop18 = 0;
	APop* rimPop19 = 0;
	APop* rimPop20 = 0;
	APop* rimPop21 = 0;
	APop* rimPop22 = 0;
	APop* rimPop23 = 0;
	APop* rimPop24 = 0;
	APop* rimPop25 = 0;
	APop* rimPop26 = 0;
	APop* rimPop27 = 0;
	APop* rimPop28 = 0;
	APop* rimPop29 = 0;
	APop* rimPop30 = 0;
	APop* rimPop31 = 0;
	APop* rimPop32 = 0;
	APop* rimPop33 = 0;
	APop* rimPop34 = 0;
	APop* rimPop35 = 0;
	APop* rimPop36 = 0;
	APop* rimPop37 = 0;
	APop* rimPop38 = 0;
	APop* rimPop39 = 0;
	APop* rimPop40 = 0;
	APop* rimPop41 = 0;
	APop* rimPop42 = 0;
	APop* rimPop43 = 0;
	APop* rimPop44 = 0;
	APop* rimPop45 = 0;
	APop* rimPop46 = 0;
	APop* rimPop47 = 0;
	APop* rimPop48 = 0;
	APop* rimPop49 = 0;
	APop* rimPop50 = 0;
	APop* rimPop51 = 0;
	APop* rimPop52 = 0;
	APop* rimPop53 = 0;
	APop* rimPop54 = 0;
	APop* rimPop55 = 0;
	APop* rimPop56 = 0;
	APop* rimPop57 = 0;
	APop* rimPop58 = 0;
	APop* rimPop59 = 0;
	APop* rimPop60 = 0;
	APop* rimPop61 = 0;
	APop* rimPop62 = 0;
	APop* rimPop63 = 0;
	APop* rimPop64 = 0;

	AThing* wheelThing = 0;
	APop* wheelPop = 0;

	AThing* wheel2Thing = 0;
	APop* wheel2Pop = 0;

	AThing* bikeThing = 0;
	APop* bikePop = 0;
};

