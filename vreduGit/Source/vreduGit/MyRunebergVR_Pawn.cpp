// Fill out your copyright notice in the Description page of Project Settings.

#include "MyRunebergVR_Pawn.h"
#include "Components/InputComponent.h"
#include "Thing.h"    // Probably just temporary, Thing should be handled in ThingManager instead
#include "RunebergVR_Movement.h"

/*
AMyRunebergVR_Pawn::AMyRunebergVR_Pawn(const class FObjectInitializer& PCIP)
{
	UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn CONSTRUCTOR called"));

	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	//PrimaryActorTick.bCanEverTick = true;

}
*/

void AMyRunebergVR_Pawn::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::BeginPlay called"));

	Super::BeginPlay();

	// 2 lines originally from constructor
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	PrimaryActorTick.bCanEverTick = true;

	//vrMovement = CreateDefaultSubobject<URunebergVR_Movement>(TEXT("vrMovement"));
	vrMovement = NewObject<URunebergVR_Movement>(this, TEXT("vrMovement"));


	if (vrMovement) {
		UE_LOG(LogTemp, Warning, TEXT("vrMovement is NOT null"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("vrMovement IS null"));
	}


#if 0 /* Obsolete. Instead, GameplayManager should tell ThingManager to spawn a Thing  */
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
#endif


}


void AMyRunebergVR_Pawn::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::Tick called, currentVelocity = (%f %f %f)"),
	//	   CurrentVelocity.X, CurrentVelocity.Y, CurrentVelocity.Z);

	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

}

void AMyRunebergVR_Pawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	//UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::SetupPlayerInputComponent called"));

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::SetupPlayerInputComponent: will bind action"));

	// Works
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyRunebergVR_Pawn::MoveForwardBackward);

	PlayerInputComponent->BindAxis("Turn", this, &AMyRunebergVR_Pawn::TurnAtRate);


	PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &AMyRunebergVR_Pawn::MoveForwardKeyb);
	PlayerInputComponent->BindAction("MoveBackward", IE_Pressed, this, &AMyRunebergVR_Pawn::MoveBackwardKeyb);

}

void AMyRunebergVR_Pawn::MoveForwardKeyb()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("MoveForwardKeyb called")));
	//AddMovementInput(GetActorForwardVector(), 10.0);

}


void AMyRunebergVR_Pawn::MoveBackwardKeyb()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("MoveBackwardKeyb called")));
}


void AMyRunebergVR_Pawn::MoveForwardBackward(float AxisValue) {

	//UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::MoveForwardBackward called, AxisValue=%f"), AxisValue);

	//CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;

	//FVector actorForw = GetActorForwardVector();
	FVector pawnMeshForw = PawnRootMesh->GetForwardVector();

	CurrentVelocity.X = pawnMeshForw.X * FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
	CurrentVelocity.Y = pawnMeshForw.Y * FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyRunebergVR_Pawn::TurnAtRate(float Rate)
{
	const float BaseTurnRate = 10.0f;

	UWorld* const World = GetWorld();
	FRotator viewRot = this->GetViewRotation();

	// This seems to only set view rotation, not pawn rotation
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

	// HACK: Set pawn rotation to the same as view rotation
	SetActorRotation(viewRot);

}

