// Fill out your copyright notice in the Description page of Project Settings.

#include "MyRunebergVR_Pawn.h"
#include "vreduGameMode.h"
#include "Components/InputComponent.h"
#include "Thing.h"    // Probably just temporary, Thing should be handled in ThingManager instead
//#include "vreduGameMode.h"
#include "PopManager.h"
#include "RunebergVR_Movement.h"

/* 
AMyRunebergVR_Pawn::AMyRunebergVR_Pawn(const class FObjectInitializer& PCIP)
{
	UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn CONSTRUCTOR called"));

	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	//PrimaryActorTick.bCanEverTick = true;

}
 */

/*
AMyRunebergVR_Pawn::AMyRunebergVR_Pawn()
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

	//rightHandMesh = NewObject<UStaticMeshComponent>(this, TEXT("rightHandMesh"));
	//rightHandMesh->AttachTo(MotionController_Right);

	//vrMovement = CreateDefaultSubobject<URunebergVR_Movement>(TEXT("vrMovement"));
	vrMovement = NewObject<URunebergVR_Movement>(this, TEXT("vrMovement"));

	if (vrMovement) {
		UE_LOG(LogTemp, Warning, TEXT("vrMovement is NOT null"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("vrMovement IS null"));
	}

	// Place the right motion controller (for grabbed Pop:s)
	//MotionController_Right->SetRelativeLocation(FVector(0.f, 0.f, 110.f));
	
#if 0 /* Commenting out to be able to edit value in editor instead */
	MotionController_Right->SetRelativeLocation(FVector(200.f, 200.f, -50.f));   // (Far, Right, High)
#endif

	SetupMaterial();

	// Set global pawn
	UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::BeginPlay: Setting global thePawn to %p"), this);
	((AvreduGameMode*)GetWorld()->GetAuthGameMode())->thePawn = this;


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
	//UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::Tick called, this=%p"), this);

	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

}


void AMyRunebergVR_Pawn::SetupMaterial() {


	AvreduGameMode* theGameMode = GetGameMode();
	MIHandPick = UMaterialInstanceDynamic::Create(theGameMode->MHandPick, theGameMode->MHandPick);
	MIHandPickChild = UMaterialInstanceDynamic::Create(theGameMode->MHandPickChild, theGameMode->MHandPickChild);
	MIHandClone = UMaterialInstanceDynamic::Create(theGameMode->MHandClone, theGameMode->MHandClone);
	MIHandCloneChild = UMaterialInstanceDynamic::Create(theGameMode->MHandCloneChild, theGameMode->MHandCloneChild);
	MIHandDrop = UMaterialInstanceDynamic::Create(theGameMode->MHandDrop, theGameMode->MHandDrop);
	MIHandDropChild = UMaterialInstanceDynamic::Create(theGameMode->MHandDropChild, theGameMode->MHandDropChild);
	MIHandDropSibling = UMaterialInstanceDynamic::Create(theGameMode->MHandDropSibling, theGameMode->MHandDropSibling);

#if 0
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialPink(TEXT("Material'/Game/Materials/M_Atom3'"));
	if (MaterialPink.Succeeded()) {
		MaterialInstancePink = UMaterialInstanceDynamic::Create(MaterialPink.Object, MaterialPink.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: MaterialPink failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialYellow(TEXT("Material'/Game/Materials/M_Atom6'"));
	if (MaterialYellow.Succeeded()) {
		MaterialInstanceYellow = UMaterialInstanceDynamic::Create(MaterialYellow.Object, MaterialYellow.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: MaterialYellow failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialGreen(TEXT("Material'/Game/Materials/M_Atom1'"));
	if (MaterialGreen.Succeeded()) {
		MaterialInstanceGreen = UMaterialInstanceDynamic::Create(MaterialGreen.Object, MaterialGreen.Object);
		UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::SetupMaterial(), MaterialInstanceGreen=%p"),
			   MaterialInstanceGreen);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: MaterialGreen failed"));
	}
#endif
}


AvreduGameMode* AMyRunebergVR_Pawn::GetGameMode() {
	UWorld* const theWorld = GetWorld();

	verify(theWorld != nullptr);

	return Cast<AvreduGameMode>(theWorld->GetAuthGameMode());
}


void AMyRunebergVR_Pawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	//UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::SetupPlayerInputComponent called"));

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::SetupPlayerInputComponent: will bind action"));

	// Works
	PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AMyRunebergVR_Pawn::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveUpDown", this, &AMyRunebergVR_Pawn::MoveUpDown);

	PlayerInputComponent->BindAxis("TurnSide", this, &AMyRunebergVR_Pawn::TurnSideAtRate);

	//PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &AMyRunebergVR_Pawn::MoveForwardKeyb);
	//PlayerInputComponent->BindAction("MoveBackward", IE_Pressed, this, &AMyRunebergVR_Pawn::MoveBackwardKeyb);

	PlayerInputComponent->BindAxis("TurnUpDown", this, &AMyRunebergVR_Pawn::TurnUpDownAtRate);
	PlayerInputComponent->BindAxis("MoveRForward", this, &AMyRunebergVR_Pawn::MoveRControllerForwardBackward);
	PlayerInputComponent->BindAxis("MoveRSide", this, &AMyRunebergVR_Pawn::MoveRControllerSide);
	PlayerInputComponent->BindAxis("MoveRUpDown", this, &AMyRunebergVR_Pawn::MoveRControllerUpDown);

	PlayerInputComponent->BindAction("TogglePickDropMode", IE_Pressed, this, &AMyRunebergVR_Pawn::TogglePickDropMode);

	PlayerInputComponent->BindAction("SpawnAtom", IE_Pressed, this, &AMyRunebergVR_Pawn::SpawnAtom);
	PlayerInputComponent->BindAction("SpawnRod", IE_Pressed, this, &AMyRunebergVR_Pawn::SpawnRod);
	PlayerInputComponent->BindAction("Experimental1", IE_Pressed, this, &AMyRunebergVR_Pawn::SpawnAtomInTheMiddleOfNowhere);
	PlayerInputComponent->BindAction("Experimental2", IE_Pressed, this, &AMyRunebergVR_Pawn::SpawnAtomInTheMiddleOfNowhere2);

	PlayerInputComponent->BindAction("DiceRotX", IE_Pressed, this, &AMyRunebergVR_Pawn::DiceRotX);
	PlayerInputComponent->BindAction("DiceRotY", IE_Pressed, this, &AMyRunebergVR_Pawn::DiceRotY);
	PlayerInputComponent->BindAction("DiceRotZ", IE_Pressed, this, &AMyRunebergVR_Pawn::DiceRotZ);
}


void AMyRunebergVR_Pawn::MoveForwardBackward(float AxisValue) {

	//UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::MoveForwardBackward called, AxisValue=%f"), AxisValue);

	//CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;

	//FVector actorForw = GetActorForwardVector();
	FVector pawnMeshForw = PawnRootMesh->GetForwardVector();

	float pawnSpeed = 300.0f;

	CurrentVelocity.X = pawnMeshForw.X * FMath::Clamp(AxisValue, -1.0f, 1.0f) * pawnSpeed;
	CurrentVelocity.Y = pawnMeshForw.Y * FMath::Clamp(AxisValue, -1.0f, 1.0f) * pawnSpeed;
}

void AMyRunebergVR_Pawn::MoveUpDown(float AxisValue) {

	FVector pawnMeshForw = PawnRootMesh->GetForwardVector();

	float pawnUpDownSpeed = 300.0f;

	CurrentVelocity.Z = FMath::Clamp(AxisValue, -1.0f, 1.0f) * pawnUpDownSpeed;
}

void AMyRunebergVR_Pawn::TurnSideAtRate(float Rate)
{
	const float BaseTurnRate = 30.0f;

	UWorld* const World = GetWorld();
	FRotator viewRot = this->GetViewRotation();

	// This seems to only set view rotation, not pawn rotation
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

	// HACK: Set pawn rotation to the same as view rotation
	SetActorRotation(viewRot);

	float yaw = viewRot.Yaw;
	// Reinsert this when I want to have fine control over pawn yaw angle again..........
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan,
	//								 FString::Printf(TEXT("Pawn rot: %f"), yaw));


	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
	//			FString::Printf(TEXT("Some variable values: x: %f, y: %f"), x, y));
}

void AMyRunebergVR_Pawn::TurnUpDownAtRate(float rate)
{
	//UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::TurnUpDownAtRate called, rate=%f"), rate);

	const float BaseTurnRate = 30.0f;

	UWorld* const World = GetWorld();
	FRotator viewRot = this->GetViewRotation();

	// This seems to only set view rotation, not pawn rotation
	AddControllerPitchInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

	// HACK: Set pawn rotation to the same as view rotation
	SetActorRotation(viewRot);

}

void AMyRunebergVR_Pawn::MoveRControllerForwardBackward(float AxisValue) {
	//UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::MoveRControllerForwardBackward called, AxisValue=%f"), AxisValue);

	UActorComponent* motCon = GetRightMotionController();
	USceneComponent* motConSceneComp = Cast<USceneComponent>(motCon);
	FTransform rTrafo = motConSceneComp->GetRelativeTransform();
	FVector rLoc = rTrafo.GetLocation();
	rLoc.X = rLoc.X + controllerSpeed * AxisValue;
	motConSceneComp->SetRelativeLocation(rLoc);

}

void AMyRunebergVR_Pawn::MoveRControllerSide(float AxisValue) {
	//UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::MoveRControllerSide called, AxisValue=%f"), AxisValue);

	UActorComponent* motCon = GetRightMotionController();
	USceneComponent* motConSceneComp = Cast<USceneComponent>(motCon);
	FTransform rTrafo = motConSceneComp->GetRelativeTransform();
	FVector rLoc = rTrafo.GetLocation();
	rLoc.Y = rLoc.Y - controllerSpeed * AxisValue;
	motConSceneComp->SetRelativeLocation(rLoc);
}


void AMyRunebergVR_Pawn::MoveRControllerUpDown(float AxisValue) {
	//UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::MoveRControllerUpDown called, AxisValue=%f"), AxisValue);

	UActorComponent* motCon = GetRightMotionController();
	USceneComponent* motConSceneComp = Cast<USceneComponent>(motCon);
	FTransform rTrafo = motConSceneComp->GetRelativeTransform();
	FVector rLoc = rTrafo.GetLocation();
	rLoc.Z = rLoc.Z - controllerSpeed * AxisValue;
	motConSceneComp->SetRelativeLocation(rLoc);
}


void AMyRunebergVR_Pawn::TogglePickDropMode() {
	UE_LOG(LogTemp, Warning, TEXT("MyRunebergVR_Pawn::TogglePickDropMode called"));

	AvreduGameMode* theGameMode = GetGameMode();
	theGameMode->thePopManager->TogglePickDropMode();
	UpdateControllerModeColor();
}


void AMyRunebergVR_Pawn::SpawnAtom() {
	UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::SpawnAtom: called"));

	//
	// Spawn pop
	//
	AvreduGameMode* theGameMode = GetGameMode();
	AThingManager* theThingManager = theGameMode->theThingManager;
	APopManager* thePopManager = theGameMode->thePopManager;
	verify(theThingManager != nullptr);
	verify(thePopManager != nullptr);
	FVector loc(4000.0f, 200.0f, 100.0f); // Don't care?
	FTransform dummyTrafo(loc);

	AThing* t = theThingManager->SpawnThingAtom("AN ATOM");
	APop* p = thePopManager->Spawn(t, dummyTrafo, false);

	//
	// Pickup the new pop, since it should start in hand
	//
	///////////////
	UE_LOG(LogTemp, Warning,
		   TEXT("AMyRunebergVR_Pawn::SpawnAtom: will NOT call Pickup to start in hand, p=%p, meshLoc:  X=%f  Y=%f  Z=%f"),
		   p,
		   loc.X, loc.Y, loc.Z);

#if 0
	thePopManager->Pickup(p);
#else
	theGameMode->AddWantsPicking(p);
#endif

	UBoxComponent* grabBox = p->grabBoxes[0];
	FTransform grabBoxTrafo = grabBox->GetRelativeTransform();
	FVector grabBoxLoc = grabBoxTrafo.GetLocation();
	UE_LOG(LogTemp, Warning,
		TEXT("AMyRunebergVR_Pawn::SpawnAtom: after NON-call to Pickup, p=%p, meshLoc:  X=%f  Y=%f  Z=%f,  grabLoc:  X=%f  Y=%f  Z=%f"),
		p,
		loc.X, loc.Y, loc.Z,
		grabBoxLoc.X, grabBoxLoc.Y, grabBoxLoc.Z);

}




void AMyRunebergVR_Pawn::SpawnRod() {
	UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::SpawnRod: called"));

	AvreduGameMode* theGameMode = GetGameMode();
	AGameplayManager* theGameplayManager = theGameMode->theGameplayManager;
	verify(theGameplayManager != nullptr);
	FVector loc(4000.0f, 200.0f, 100.0f); // Don't care?

	APop* p = theGameplayManager->SpawnRod("Rod", 7, loc);

	//
	// Pickup the new pop, since it should start in hand
	//
	///////////////
	UE_LOG(LogTemp, Warning,
		TEXT("AMyRunebergVR_Pawn::SpawnRod: will NOT call Pickup to start in hand, p=%p, meshLoc:  X=%f  Y=%f  Z=%f"),
		p,
		loc.X, loc.Y, loc.Z);

#if 0
	thePopManager->Pickup(p);
#else
	theGameMode->AddWantsPicking(p);
#endif

	UBoxComponent* grabBox = p->grabBoxes[0];
	FTransform grabBoxTrafo = grabBox->GetRelativeTransform();
	FVector grabBoxLoc = grabBoxTrafo.GetLocation();
	UE_LOG(LogTemp, Warning,
		   TEXT("AMyRunebergVR_Pawn::SpawnRod: after NON-call to Pickup, p=%p, meshLoc:  X=%f  Y=%f  Z=%f,  grabLoc:  X=%f  Y=%f  Z=%f"),
		   p,
		   loc.X, loc.Y, loc.Z,
		   grabBoxLoc.X, grabBoxLoc.Y, grabBoxLoc.Z);

}


void AMyRunebergVR_Pawn::SpawnAtomInTheMiddleOfNowhere() {
	UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::SpawnAtomInTheMiddleOfNowhere: called"));

	//
	// Spawn pop
	//
	AvreduGameMode* theGameMode = GetGameMode();
	AThingManager* theThingManager = theGameMode->theThingManager;
	APopManager* thePopManager = theGameMode->thePopManager;
	verify(theThingManager != nullptr);
	verify(thePopManager != nullptr);
	FVector loc(500.0f, 500.0f, 250.0f); // In the middle of nowhere
	FTransform dummyTrafo(loc);

	AThing* t = theThingManager->SpawnThingAtom("AN ATOM IN THE MIDDLE OF NOWHERE");
	APop* p = thePopManager->Spawn(t, dummyTrafo, false);

}

void AMyRunebergVR_Pawn::SpawnAtomInTheMiddleOfNowhere2() {
	UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::SpawnAtomInTheMiddleOfNowhere: called"));

	//
	// Spawn pop
	//
	AvreduGameMode* theGameMode = GetGameMode();
	AThingManager* theThingManager = theGameMode->theThingManager;
	APopManager* thePopManager = theGameMode->thePopManager;
	verify(theThingManager != nullptr);
	verify(thePopManager != nullptr);
	FVector loc(520.0f, 520.0f, 270.0f); // In the middle of nowhere
	FTransform dummyTrafo(loc);

	AThing* t = theThingManager->SpawnThingAtom("ANOTHER ATOM IN THE MIDDLE OF NOWHERE");
	//APop* p = thePopManager->Spawn(t, dummyTrafo, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	APop* p = thePopManager->Spawn(t, dummyTrafo, false, ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding);

}


void AMyRunebergVR_Pawn::DiceRotX() {
	AvreduGameMode* theGameMode = GetGameMode();
	AGameplayManager* theGameplayManager = theGameMode->theGameplayManager;
	FQuat quat(0.707107f, 0, 0, 0.707107f);
	theGameplayManager->DiceRot(quat);
}

void AMyRunebergVR_Pawn::DiceRotY() {
	AvreduGameMode* theGameMode = GetGameMode();
	AGameplayManager* theGameplayManager = theGameMode->theGameplayManager;
	FQuat quat(0, 0.707107f, 0, 0.707107f);
	theGameplayManager->DiceRot(quat);
}

void AMyRunebergVR_Pawn::DiceRotZ() {
	AvreduGameMode* theGameMode = GetGameMode();
	AGameplayManager* theGameplayManager = theGameMode->theGameplayManager;
	FQuat quat(0, 0, 0.707107f, 0.707107f);
	theGameplayManager->DiceRot(quat);
}

void AMyRunebergVR_Pawn::UpdateControllerModeColor() {

	//UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::UpdateControllerModeColor: called"));
	AvreduGameMode* theGameMode = GetGameMode();

	if (theGameMode->thePopManager->pickedPop == nullptr)
		UpdateControllerPickModeColor();
	else
		UpdateControllerDropModeColor();
}


void AMyRunebergVR_Pawn::UpdateControllerPickModeColor() {

	//UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::UpdateControllerPickModeColor: called"));

	AvreduGameMode* theGameMode = GetGameMode();
	UActorComponent* rMeshAC = GetRightMotionControllerMesh();
	UStaticMeshComponent* rMesh = Cast<UStaticMeshComponent>(rMeshAC);

	if (theGameMode->thePopManager->IsPickMode())
		rMesh->SetMaterial(0, MIHandPick);
	else if (theGameMode->thePopManager->IsPickChildMode())
		rMesh->SetMaterial(0, MIHandPickChild);
	else if (theGameMode->thePopManager->IsCloneMode())
		rMesh->SetMaterial(0, MIHandClone);
	else
		rMesh->SetMaterial(0, MIHandCloneChild);

}


void AMyRunebergVR_Pawn::UpdateControllerDropModeColor() {
	AvreduGameMode* theGameMode = GetGameMode();
	UActorComponent* rMeshAC = GetRightMotionControllerMesh();
	UStaticMeshComponent* rMesh = Cast<UStaticMeshComponent>(rMeshAC);

	if (theGameMode->thePopManager->IsDropMode()) {
		//UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::UpdateControllerDropModeColor: Will set MIHandDrop material <%p>"),
		//	   MIHandDrop);

		rMesh->SetMaterial(0, MIHandDrop);
	}
	else if (theGameMode->thePopManager->IsDropChildMode()) {
		//UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::UpdateControllerDropModeColor: Will set MIHandDropChild material <%p>"),
		//	   MIHandDropChild);

		rMesh->SetMaterial(0, MIHandDropChild);
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::UpdateControllerDropModeColor: Will set MIHandDropSibling material <%p>"),
		//	   MIHandDropSibling);

		rMesh->SetMaterial(0, MIHandDropSibling);
	}

	//UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::UpdateControllerDropModeColor: After update, material is: <%p>"),
	//	   rMesh->GetMaterial(0));

}

UActorComponent* AMyRunebergVR_Pawn::GetRightMotionController() {

	AvreduGameMode* theGameMode = GetGameMode();
	AMyRunebergVR_Pawn*	thePawn = theGameMode->thePawn;
	USceneComponent* theRoot = thePawn->PawnRootMesh;
	TArray < USceneComponent* > children;

	theRoot->GetChildrenComponents(true, children);

	//UE_LOG(LogTemp, Warning, TEXT("APop::GetRightMotionController: children.Num()=%d"), children.Num());


#if 0
	// Extra pre-loop just for logging
	for (int ix = 0; ix < children.Num(); ++ix) {

		USceneComponent* child = children[ix];

		UE_LOG(LogTemp, Warning, TEXT("APop::GetRightMotionController PRE-LOOP: child=%p, name=%s"),
			child, *child->GetName());
	}
#endif



	for (int ix = 0; ix < children.Num(); ++ix) {

		USceneComponent* child = children[ix];

		//UE_LOG(LogTemp, Warning, TEXT("APop::GetRightMotionController: child=%p, name=%s"),
		//	child, *child->GetName());

		if (child->GetName() == "MotionController_Right") {
			//UE_LOG(LogTemp, Warning, TEXT("APop::GetRightMotionController: Returning %p"), child);
			//UMotionControllerComponent* motCon = Cast<UMotionControllerComponent>(child);
			return child;
		}

	}

	return nullptr;
}


UActorComponent* AMyRunebergVR_Pawn::GetRightMotionControllerMesh() {

	AvreduGameMode* theGameMode = GetGameMode();
	AMyRunebergVR_Pawn*	thePawn = theGameMode->thePawn;
	USceneComponent* theRoot = thePawn->PawnRootMesh;
	TArray < USceneComponent* > children;

	theRoot->GetChildrenComponents(true, children);

	//UE_LOG(LogTemp, Warning, TEXT("APop::GetRightMotionControllerMesh: children.Num()=%d"), children.Num());

	for (int ix = 0; ix < children.Num(); ++ix) {

		USceneComponent* child = children[ix];

		//UE_LOG(LogTemp, Warning, TEXT("APop::GetRightMotionControllerMesh: child=%p, name=%s"),
		//	child, *child->GetName());

		if (child->GetName() == "rightMesh") {
			//UE_LOG(LogTemp, Warning, TEXT("APop::GetRightMotionControllerMesh: Returning %p"), child);
			//UMotionControllerComponent* motCon = Cast<UMotionControllerComponent>(child);
			return child;
		}

	}

	return nullptr;
}