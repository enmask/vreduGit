// Fill out your copyright notice in the Description page of Project Settings.

#include "MyRunebergVR_Pawn.h"
#include "Components/InputComponent.h"
#include "Thing.h"    // Probably just temporary, Thing should be handled in ThingManager instead

/*
AMyRunebergVR_Pawn::AMyRunebergVR_Pawn(const class FObjectInitializer& PCIP)
{
	UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn CONSTRUCTOR called"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	PrimaryActorTick.bCanEverTick = true;
}
*/

void AMyRunebergVR_Pawn::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::BeginPlay called"));

	Super::BeginPlay();

	// 2 lines originally from constructor
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	PrimaryActorTick.bCanEverTick = true;



	// TEST: Spawn some Things

	UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::BeginPlay: Will spawn Thing"));

	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	FTransform trafo(Location);

	AThing* newThing = GetWorld()->SpawnActorDeferred<AThing>(AThing::StaticClass(), trafo);

	//
	// Initialize the Thing
	//
	newThing->init("Just a thing");

	newThing->FinishSpawning(trafo);

	UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::BeginPlay: Finished spawning Thing"));


	//	return newThing;




}


void AMyRunebergVR_Pawn::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::Tick called"));

	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

}

void AMyRunebergVR_Pawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::SetupPlayerInputComponent called"));

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AMyRunebergVR_Pawn::MoveForwardBackward);
}

void AMyRunebergVR_Pawn::MoveForwardBackward(float AxisValue) {

	UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::MoveForwardBackward called, AxisValue=%f"), AxisValue);

	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}


