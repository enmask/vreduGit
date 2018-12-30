// Fill out your copyright notice in the Description page of Project Settings.

#include "vreduGameMode.h"
#include "MyRunebergVR_Pawn.h"

AvreduGameMode::AvreduGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = AMyRunebergVR_Pawn::StaticClass();

	SetupMaterial();

}


void AvreduGameMode::SetupMaterial() {

	UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial() called, this=%p"), this);

	/*static*/ ConstructorHelpers::FObjectFinder<UMaterial> MHandPickTmp(TEXT("Material'/Game/Materials/M_HandPick'"));
	if (MHandPickTmp.Succeeded()) {

		// Store also the material, not only the dyn.mat.instance (needed for outside-class use)
		// TODO: Store ONLY the material, not the MID
		MHandPick = MHandPickTmp.Object;

		//MIHandPick = UMaterialInstanceDynamic::Create(MHandPickTmp.Object, MHandPickTmp.Object);
		//UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial(): MIHandPick=%p, MHandPick=%p"),
		//	   MIHandPick, MHandPick);

		// TEST
		//MIHandPickTestNumber = 17;

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial: MHandPick failed"));
	}

	/*static*/ ConstructorHelpers::FObjectFinder<UMaterial> MHandPickChildTmp(TEXT("Material'/Game/Materials/M_HandPickChild'"));
	if (MHandPickChildTmp.Succeeded()) {

		MHandPickChild = MHandPickChildTmp.Object;

		//MIHandPickChild = UMaterialInstanceDynamic::Create(MHandPickChildTmp.Object, MHandPickChildTmp.Object);
		//UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial(): MIHandPickChild=%p, MHandPickChild=%p"),
		//	MIHandPickChild, MHandPickChild);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial: MHandPickChild failed"));
	}

	/*static*/ ConstructorHelpers::FObjectFinder<UMaterial> MHandCloneTmp(TEXT("Material'/Game/Materials/M_HandClone'"));
	if (MHandCloneTmp.Succeeded()) {
		MHandClone = MHandCloneTmp.Object;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial: MHandClone failed"));
	}

	/*static*/ ConstructorHelpers::FObjectFinder<UMaterial> MHandCloneChildTmp(TEXT("Material'/Game/Materials/M_HandCloneChild'"));
	if (MHandCloneChildTmp.Succeeded()) {
		MHandCloneChild = MHandCloneChildTmp.Object;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial: MHandPickChild failed"));
	}

	/*static*/ ConstructorHelpers::FObjectFinder<UMaterial> MHandDropTmp(TEXT("Material'/Game/Materials/M_HandDrop'"));
	if (MHandDropTmp.Succeeded()) {

		MHandDrop = MHandDropTmp.Object;

		//MIHandDrop = UMaterialInstanceDynamic::Create(MHandDropTmp.Object, MHandDropTmp.Object);
		//UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial(): MIHandDrop=%p"),
		//	MIHandDrop);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial: MHandDrop failed"));
	}

	/*static*/ ConstructorHelpers::FObjectFinder<UMaterial> MHandDropChildTmp(TEXT("Material'/Game/Materials/M_HandDropChild'"));
	if (MHandDropChildTmp.Succeeded()) {

		MHandDropChild = MHandDropChildTmp.Object;

		//MIHandDropChild = UMaterialInstanceDynamic::Create(MHandDropChildTmp.Object, MHandDropChildTmp.Object);
		//UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial(): MIHandDropChild=%p"),
		//	MIHandDropChild);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial: MHandDropChild failed"));
	}

	/*static*/ ConstructorHelpers::FObjectFinder<UMaterial> MHandDropSiblingTmp(TEXT("Material'/Game/Materials/M_HandDropSibling'"));
	if (MHandDropSiblingTmp.Succeeded()) {

		MHandDropSibling = MHandDropSiblingTmp.Object;

		//MIHandDropSibling = UMaterialInstanceDynamic::Create(MHandDropSiblingTmp.Object, MHandDropSiblingTmp.Object);
		//UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial(): MIHandDropSibling=%p"),
		//	MIHandDropSibling);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AvreduGameMode::SetupMaterial: MHandDropSibling failed"));
	}
}


void AvreduGameMode::StartPlay() {
	UE_LOG(LogTemp, Warning, TEXT("vreduGameMode::StartPlay called"));

	Super::StartPlay();

	UWorld* world = GetWorld();
	theGameplayManager = world->SpawnActor< AGameplayManager >();
	theThingManager = world->SpawnActor< AThingManager >();
	thePopManager = world->SpawnActor< APopManager >();

	//wantsDropping = false;
}


TArray< APop* > AvreduGameMode::GetWantsPicking() {
	return wantsPicking;
}

void AvreduGameMode::AddWantsPicking(APop* pop) {
	wantsPicking.Add(pop);
}

void AvreduGameMode::RemoveWantsPicking(APop* pop) {
	wantsPicking.Remove(pop);
}

void AvreduGameMode::RemoveWantsPickingAt(int ix) {
	wantsPicking.RemoveAt(ix);
}

#if 0
APop* AvreduGameMode::GetWantsDropping() {
	return wantsDropping;
}

void AvreduGameMode::SetWantsDropping(bool value) {
	wantsDropping = value;
}
#endif