// Fill out your copyright notice in the Description page of Project Settings.

#include "PopManager.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "vreduGameMode.h"
#include "Thing.h"
#include "Pop.h"


// Sets default values
APopManager::APopManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APopManager::BeginPlay()
{
	Super::BeginPlay();
	
	numTicks = 0;
	numPops = 0;
	pickedPop = nullptr;
	brightPop = nullptr;
	ghostPop = nullptr;

	pickModeEnum = EPickModeEnum::M_Pick;
	dropModeEnum = EDropModeEnum::M_Drop;
}

// Called every frame
void APopManager::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("APopManager::Tick called"));

	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("APopManager::Tick: pickedPop=%p"),
		   pickedPop);
	if (pickedPop != nullptr) {
		UE_LOG(LogTemp, Warning,
			   TEXT("APopManager::Tick: pickedPop is not null, so log pickedPop root parent=%p"),
			   pickedPop->GetRootComponent()->GetAttachParent());
	}

	AvreduGameMode* theGameMode = GetGameMode();

	PickupThoseWhoWant();
	//DropChildToThoseWhoWant();

	int highlightUpdatePeriod = theGameMode->highlightUpdatePeriod;

	if (numTicks % highlightUpdatePeriod == 0)
		HighlightCloseTopChildren(nullptr);

	numTicks++;
}


AvreduGameMode* APopManager::GetGameMode() {
	UWorld* const theWorld = GetWorld();

	verify(theWorld != nullptr);

	return Cast<AvreduGameMode>(theWorld->GetAuthGameMode());
}


bool APopManager::IsPickMode() {
	return (pickModeEnum == EPickModeEnum::M_Pick);
}

bool APopManager::IsPickChildMode() {
	return (pickModeEnum == EPickModeEnum::M_PickChild);
}

bool APopManager::IsCloneMode() {
	return (pickModeEnum == EPickModeEnum::M_Clone);
}

bool APopManager::IsCloneChildMode() {
	return (pickModeEnum == EPickModeEnum::M_CloneChild);
}

bool APopManager::IsDropMode() {
	return (dropModeEnum == EDropModeEnum::M_Drop);
}

bool APopManager::IsDropChildMode() {
	return (dropModeEnum == EDropModeEnum::M_DropChild);
}

bool APopManager::IsDropSiblingMode() {
	return (dropModeEnum == EDropModeEnum::M_DropSibling);
}


void APopManager::TogglePickDropMode() {

	if (pickedPop == nullptr) {
		// Nothing is picked, toggle pick mode
		if (pickModeEnum == EPickModeEnum::M_Pick)
			pickModeEnum = EPickModeEnum::M_PickChild;
		else if (pickModeEnum == EPickModeEnum::M_PickChild)
			pickModeEnum = EPickModeEnum::M_Clone;
		else if (pickModeEnum == EPickModeEnum::M_Clone)
			pickModeEnum = EPickModeEnum::M_CloneChild;
		else
			pickModeEnum = EPickModeEnum::M_Pick;

		///UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::TogglePickDropMode: Pick mode toggled to %s"),
		///	   *GetPickModeEnumAsString(pickModeEnum));
	}
	else {
		// Something is picked, toggle drop mode
		if (dropModeEnum == EDropModeEnum::M_Drop)
			dropModeEnum = EDropModeEnum::M_DropChild;
		else if (dropModeEnum == EDropModeEnum::M_DropChild)
			dropModeEnum = EDropModeEnum::M_DropSibling;
		else
			dropModeEnum = EDropModeEnum::M_Drop;

		///UE_LOG(LogTemp, Warning, TEXT("AMyRunebergVR_Pawn::TogglePickDropMode: Drop mode toggled to %s"),
		///	   *GetDropModeEnumAsString(dropModeEnum));
	}
}

void APopManager::PickupThoseWhoWant() {

	AvreduGameMode* theGameMode = GetGameMode();
	TArray< APop* > wantsPicking = theGameMode->GetWantsPicking();

	for (APop* pop : wantsPicking) {

		UE_LOG(LogTemp, Warning, TEXT("APopManager::Tick: pop %p wants PICKING. pop->picked=%s"),
			   pop, (pop->picked)?TEXT("true"):TEXT("false"));

		//pop->picked ? Drop(pop) : Pickup(pop);
		//pop->picked ? DropAndAddChild(pop) : Pickup(pop);

		if (pop->picked) {
			if (IsDropMode())
				Drop(pop);
			else if (IsDropChildMode())
				DropAndAddChild(pop);
			else
				DropSibling(pop);
		}
		else {
			if (IsPickMode())
				Pickup(pop);
			else if (IsPickChildMode())
				PickChild(pop);
			else if (IsCloneMode())
				ClonePick(pop, "A CLONE");
			else
				CloneChild(pop, "A CLONE");
		}

		theGameMode->RemoveWantsPicking(pop);
		UpdateControllerModeColor();
	}
}

#if 0
void APopManager::DropChildToThoseWhoWant() {

	AvreduGameMode* theGameMode = GetGameMode();
	APop* wantsChild = theGameMode->GetWantsPicking();
	
	if (wantsChild != nullptr && pickedPop != nullptr) {

		Drop(pickedPop);
		AddChild(wantsChild, pickedPop);

	}
}
#endif


void APopManager::Pickup(APop* pop) {

	UE_LOG(LogTemp, Warning, TEXT("APopManager::Pickup called, pop=%p, root parent=%p"),
		   pop, pop->GetRootComponent()->GetAttachParent());

	UActorComponent* motCon = GetRightMotionController();
	pop->DisableComponentsSimulatePhysics();
	pop->AttachToComponent(Cast<USceneComponent>(motCon),
						   FAttachmentTransformRules::SnapToTargetIncludingScale,
						   NAME_None);

	UE_LOG(LogTemp, Warning, TEXT("APopManager::Pickup: Directly after AttachToComponent, pop=%p, root parent=%p"),
		pop, pop->GetRootComponent()->GetAttachParent());


	// Move the picked pop forward a bit so that it doesn't get too close to camera
	/*
		FTransform cloneTrafo = p->GetActorTransform();
	FVector cloneLoc = cloneTrafo.GetLocation();
	cloneLoc.X += 60.0;
	cloneLoc.Z += 30.0;
	cloneTrafo.SetLocation(cloneLoc);
	*/
	FVector popLoc = pop->GetActorLocation();
#if 0
	popLoc.Y = popLoc.Y + 400.0f;  // Was 100.0
	pop->SetActorLocation(popLoc);
#else
	/* */
	//FTransform subThingRelTrafo = UKismetMathLibrary::ConvertTransformToRelative(parent->GetTransform(), toBeChild->GetTransform());
	FTransform popAbsTrafo(FVector(0.0, 400.0, 0.0));
	USceneComponent* motConSC = Cast<USceneComponent>(motCon);
	FTransform motConRelTrafo = motConSC->GetRelativeTransform();
	//USceneComponent::GetComponentLocation
	FTransform motConAbsTrafo = motConSC->GetComponentTransform();
	FTransform popRelTrafo = UKismetMathLibrary::ConvertTransformToRelative(motConAbsTrafo, popAbsTrafo);
	/**
	pop->SetActorTransform(popRelTrafo);
	**/
	UE_LOG(LogTemp, Warning,
		   TEXT("APopManager::Pickup trafos:  popAbsTrafo=%s,  motConRelTrafo=%s, motConAbsTrafo=%s,  popRelTrafo=%s"),
		   *popAbsTrafo.ToHumanReadableString(), *motConRelTrafo.ToHumanReadableString(), *motConAbsTrafo.ToHumanReadableString(), *popRelTrafo.ToHumanReadableString());
	/* */

	FTransform popTrafo(FVector(100, 0, 0));
	//pop->SetActorTransform(popTrafo);
	pop->SetActorTransform(popTrafo * motConAbsTrafo);

#endif
	pop->picked = true;
	pickedPop = pop;

	HighlightCloseTopChildren(pop);

	///SpawnGhostPop();

	UE_LOG(LogTemp, Warning, TEXT("APopManager::Pickup end:  pop=%p, root parent=%p"),
		   pop, pop->GetRootComponent()->GetAttachParent());

	//UE_LOG(LogTemp, Warning, TEXT("APopManager::Pickup end"), pop);
}


void APopManager::PickChild(APop* pop) {
	UE_LOG(LogTemp, Warning, TEXT("***NYI!  NUI!  NYI!  APopManager::PickChild called, pop=%p. NYI!  NYI!  NYI!***"), pop);
}

// Deep copy a Pop and all its Thing:s.
// Return the clone Pop.
// TODO: Shouldn't Clone() increase numPops? (Except in the shadow-pop case)
APop* APopManager::Clone(APop* p, FString cloneName) {

	UWorld* const World = GetWorld();
	AThingManager* theThingManager = ((AvreduGameMode*)World->GetAuthGameMode())->theThingManager;

	AThing* cloneThing = theThingManager->Clone(p->thingRef, cloneName);

	// HACK: Temporary hack, move the clone along x so that it doesn't collide with the original
	FTransform cloneTrafo = p->GetActorTransform();
#if 0
	FVector cloneLoc = cloneTrafo.GetLocation();

	UE_LOG(LogTemp,
		Warning,
		TEXT("APopManager::Clone: orig loc X=%f Y=%f Z=%f,  cloneLoc: X=%f Y=%f Z=%f"),
		p->GetActorTransform().GetLocation().X, p->GetActorTransform().GetLocation().Y, p->GetActorTransform().GetLocation().Z,
		cloneLoc.X, cloneLoc.Y, cloneLoc.Z);
#endif

	APop* clonePop = Spawn(cloneThing, cloneTrafo);
	return clonePop;
}


#if 1
// Deep copy origPop and give the thing of the copy the name <cloneName>
// Return the copy
void APopManager::ClonePick(APop* origPop, FString cloneName) {
	UE_LOG(LogTemp, Warning,
		   TEXT("APopManager::Clone called, origPop=%p, cloneName=%s"),
		   origPop, (cloneName != "") ? *cloneName : TEXT("<empty string>"));

	APop* clonePop = Clone(origPop, cloneName);
	Pickup(clonePop);
}
#endif


// Deep copy one child of origPop and give the thing of the copy the name <cloneName> or
// , if cloneName is "", original name with "_cloneName" appended
// ***NYI. TODO: Add parameter that specifies which child to clone
APop* APopManager::CloneChild(APop* origPop, FString cloneName) {
	UE_LOG(LogTemp, Warning,
		   TEXT("***NYI!  NUI!  NYI!  APopManager::CloneChild called, origPop=%p, cloneName=%s. NYI!  NYI!  NYI!***"),
		   origPop, (cloneName != "") ? *cloneName : TEXT("<empty string>"));
	return nullptr;
}

void APopManager::Drop(APop* pop) {
	UE_LOG(LogTemp, Warning, TEXT("APopManager::Drop called, pop=%p"), pop);

	pop->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	pop->mesh->SetSimulatePhysics(true);
	pop->picked = false;
	pickedPop = nullptr;

	UE_LOG(LogTemp, Warning, TEXT("APopManager::Drop end"));
}


// Drop and insert as child to Pop
// TODO: Change name from DropAndAddChild to DropChild
void APopManager::DropAndAddChild(APop* pop) {
	UE_LOG(LogTemp, Warning, TEXT("APopManager::DropAndAddChild called, pop=%p. Will call LogComponentHierarchy for pop"), pop);
	pop->LogComponentHierarchy(pop->GetRootComponent());

	if (brightPop != nullptr) {

		UE_LOG(LogTemp, Warning, TEXT("APopManager::DropAndAddChild (called), pop=%p. Will call LogComponentHierarchy for brightPop"), pop);
		brightPop->LogComponentHierarchy(brightPop->GetRootComponent());

		verify(brightPop != pop);

		Drop(pop);
		AddChild(brightPop, pop);
	}

	UE_LOG(LogTemp, Warning, TEXT("APopManager::DropAndAddChild end, pop=%p. Will call LogComponentHierarchy for pop"), pop);
	pop->LogComponentHierarchy(pop->GetRootComponent());
	if (brightPop != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("APopManager::DropAndAddChild (end), pop=%p. Will call LogComponentHierarchy for brightPop"), pop);
		brightPop->LogComponentHierarchy(brightPop->GetRootComponent());
	}
}

void APopManager::DropSibling(APop* pop) {
	UE_LOG(LogTemp, Warning, TEXT("***NYI!  NUI!  NYI!  APopManager::DropSibling called, pop=%p. NYI!  NYI!  NYI!***"), pop);
}

void APopManager::UpdateControllerModeColor() {
	AMyRunebergVR_Pawn*	thePawn = ((AvreduGameMode*)GetWorld()->GetAuthGameMode())->thePawn;
	thePawn->UpdateControllerModeColor();
}


UActorComponent* APopManager::GetRightMotionController() {

	AMyRunebergVR_Pawn*	thePawn = ((AvreduGameMode*)GetWorld()->GetAuthGameMode())->thePawn;
	USceneComponent* theRoot = thePawn->PawnRootMesh;
	TArray < USceneComponent* > children;

	theRoot->GetChildrenComponents(true, children);

	UE_LOG(LogTemp, Warning, TEXT("APop::GetRightMotionController: children.Num()=%d"), children.Num());

	for (int ix = 0; ix < children.Num(); ++ix) {

		USceneComponent* child = children[ix];

		UE_LOG(LogTemp, Warning, TEXT("APop::GetRightMotionController: child=%p, name=%s"),
			child, *child->GetName());

		if (child->GetName() == "MotionController_Right") {
			UE_LOG(LogTemp, Warning, TEXT("APop::GetRightMotionController: Returning %p"), child);
			//UMotionControllerComponent* motCon = Cast<UMotionControllerComponent>(child);
			return child;
		}

	}

	return nullptr;
}


APop* APopManager::Spawn(AThing* thing, FTransform transform, ESpawnActorCollisionHandlingMethod collisionHandling) {

	//
	// Start spawning
	//

	UWorld* const World = GetWorld();
	APop* newPop = nullptr;

	newPop = World->SpawnActorDeferred<APop>(APop::StaticClass(), transform, nullptr, nullptr, collisionHandling);

	//
	// Initialize the Pop
	//
	newPop->init(thing, transform);

	//
	// Finish spawning
	//
	newPop->FinishSpawning(transform);

	IncPopsCounter();
	controlPops.Add(newPop);

	UE_LOG(LogTemp, Warning, TEXT("APopManager::Spawn: Will return newPop=%p with name=<%s>, controlPops.Num()=%d, numPops=%d"),
		   newPop, *newPop->GetName(), controlPops.Num(), numPops);

	return newPop;
}


void APopManager::SpawnGhostPop() {

	ghostPop = Clone(pickedPop, "Clone pop");



}



//(AThing* thing,
//	FTransform transform,
//	ESpawnActorCollisionHandlingMethod collisionHandling = ESpawnActorCollisionHandlingMethod::Undefined);





//
// Destroy a Pop
//
void APopManager::DestroyPop(APop* pop) {

	UE_LOG(LogTemp, Warning, TEXT("APopManager::DestroyPop: Will destroy newPop=%p with name=<%s> ..."),
		   pop, *pop->GetName());

	controlPops.Remove(pop);
	UE_LOG(LogTemp, Warning,
		   TEXT("DestroyPop: controlPops.Num() decreased to: %d. numPops will be decreased from %d..."),
		   controlPops.Num(), numPops);
	pop->Destroy();
	DecPopsCounter();
	UE_LOG(LogTemp, Warning, TEXT("... to %d"), numPops);

}


void APopManager::IncPopsCounter() {
	UE_LOG(LogTemp, Warning, TEXT("IncPopsCounter called, numPops=%d (before inc)"), numPops);
	numPops++;
	LogControlPops();
}


void APopManager::DecPopsCounter() {
	UE_LOG(LogTemp, Warning, TEXT("DecPopsCounter called, numPops=%d (before dec)"), numPops);
	numPops--;
	LogControlPops();
}


void APopManager::LogControlPops() {

	UE_LOG(LogTemp, Warning, TEXT("APopManager::LogPopsCounter: numPops=%d. Here come the %d counted pops:"),
		   numPops, controlPops.Num());
	for (auto& currentAct : controlPops) {
		UE_LOG(LogTemp, Warning, TEXT("currentAct=%p, thing name=<%s>"),
			   currentAct, *currentAct->thingRef->name);
	}
}

void APopManager::AddChild(APop* parent, APop* toBeChild) {

	UE_LOG(LogTemp, Warning, TEXT("APopManager::AddChild: parent=%p, name=%s. toBeChild=%p, name=%s"),
		   parent, *parent->thingRef->name, toBeChild, *toBeChild->thingRef->name);

	verify(parent != toBeChild);

	// parent and toBeChild may or may not already have children
	// No new Pop is needed
	// Pop toBeChild will not be needed anymore, so remove it
	// parent Pop will still be parent Pop afterwards

	// parent->thingRef will not change
	// parent->thingRef->subThings (and subThingRelTrafos, and subThingRoles)
	//   will be extended with a thing, namely toBeChild->thingRef
	// toBeChild->thingRef


	// Add toBeChild Thing to array
	parent->thingRef->subThings.Add(toBeChild->thingRef);
	// What should the new relTrafo be? Hm, that would depend on the current relative positions/rotation of
	// parent and toBeChild (see old Join implementation, I guess)

	// TODO: Real trafo implementation (including rotation and scale)
	//parent->thingRef->subThingRelTrafos.Add(...trafo of toBeChild seen relative to parent...);

	// FOR NOW: Only the location part of the trafo. I.e. the distance between parent and toBeChild Pop:s
#if 0
	FVector locParent = parent->GetActorLocation();
	FVector locChild = toBeChild->GetActorLocation();
	FVector locDifference = locChild-locParent;
#endif

#if 0 /* Only location considered */
	parent->thingRef->subThingRelTrafos.Add(FTransform(toBeChild->GetActorLocation() - parent->GetActorLocation()));
#else /* Complete trafo considered */
	FTransform subThingRelTrafo = UKismetMathLibrary::ConvertTransformToRelative(parent->GetTransform(), toBeChild->GetTransform());
	parent->thingRef->subThingRelTrafos.Add(subThingRelTrafo);
#endif

	parent->thingRef->subThingRoles.Add("undefined");

	// Destroy toBeChild Pop
	DestroyPop(toBeChild);

	UE_LOG(LogTemp, Warning, TEXT("APopManager::AddChild will now call BuildMesh"));

	// Rebuild mesh to get the combined mesh
	parent->BuildMesh();
}


void APopManager::RotateAroundLocalY(APop* p, float degrees) {

#if 0
	FRotator theRotator = FRotator(0.0, degrees, 0.0);
#else
	// HACK: Work-around, pop:s seem to be rotated 90 degrees or something...
	FRotator theRotator = FRotator(degrees, 0.0, 0.0);
#endif

	p->AddActorWorldRotation(theRotator);

}

//
// Highlight close-by Pop:s, i.e. close to popParam.
// If popParam is null, use the held Pop, if any.
// TODO: Maybe implement FindCloseTopChildren instead
//
void APopManager::HighlightCloseTopChildren(APop* popParam) {

	/* Sweep solution, will probably not use that...
	FCollisionShape MySphere = FCollisionShape::MakeSphere(500.0f); // 5M Radius
	TArray<FHitResults> OutResults;
	GetWorld()->SweepMultiByChannel(OutResults, SweepStart, SweepEnd, FQuat::Identity, TraceChannel, MySphere);
	*/

	APop* pop;

	brightPop = nullptr;

	if (popParam == nullptr)
		pop = pickedPop;
	else
		pop = popParam;

	if (pop == nullptr)
		return;

	TArray<AActor*> thePops;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APop::StaticClass(), thePops);

	UE_LOG(LogTemp, Warning, TEXT("APopManager::HighlightCloseTopChildren: before verify: thePops.Num()=%d, numPops=%d"),
		   thePops.Num(), numPops);

	for (auto& currentAct : thePops) {
		UE_LOG(LogTemp, Warning, TEXT("APopManager::HighlightCloseTopChildren: currentAct=%p, IsValid=%s, pendingKill=%s"),
			   currentAct, IsValid(currentAct) ? TEXT("true") : TEXT("false"), currentAct->IsPendingKill() ? TEXT("true") : TEXT("false"));

	}

	//TSet < AActor* > thePopsSet = TSet < AActor* >(thePops);
	TSet < AActor* > thePopsSet(thePops);
	for (auto& currentSetAct : thePopsSet) {
		UE_LOG(LogTemp, Warning, TEXT("APopManager::HighlightCloseTopChildren: currentSetAct=%p"),
			   currentSetAct);

	}


	// All Pop:s found in the level should equal the number of Pop:s that the PopManager keeps track of
	verify(thePops.Num() == numPops);

	APop* closestPop = nullptr;

	for (auto& currentAct : thePops) {
		
		APop* currentPop = Cast<APop>(currentAct);
		UE_LOG(LogTemp, Warning, TEXT("APopManager::HighlightCloseTopChildren: currentPop=%p, name=%s, thing name=%s"),
			   currentPop, *currentPop->GetName(), *currentPop->thingRef->name);

		if (currentPop->picked)
			continue;

		if (currentPop == pop)
			continue;

		if (IsClose(currentPop, pop)) {
			UE_LOG(LogTemp, Warning, TEXT("APopManager::HighlightCloseTopChildren: currentPop %p (%s) *IS* close to pop %p (%s), so highlight currentPop. picked=%s"),
				   currentPop, *currentPop->thingRef->name, pop, *pop->thingRef->name, (pop->picked) ? TEXT("true") : TEXT("false"));

			// This currentPop is close, so highlight all its sections
			//currentPop->Highlight(-1, 1);
			currentPop->HighlightWireChild(-1, 1);

			if (IsVeryClose(currentPop, pop) && IsCloser(currentPop, closestPop, pop)) {

				UE_LOG(LogTemp, Warning, TEXT("APopManager::HighlightCloseTopChildren: Setting closestPop = currentPop, %p (%s), picked=%s"),
					   currentPop, *currentPop->thingRef->name, (currentPop->picked) ? TEXT("true") : TEXT("false"));
				closestPop = currentPop;
			}

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("APopManager::HighlightCloseTopChildren: currentPop <%s> is NOT close to pop <%s>"),
				*currentPop->thingRef->name, *pop->thingRef->name);

			// De-highlight all sections of this Pop
			currentPop->Highlight(-1, 0);
		}
	}

	if (closestPop != nullptr) {

		// We found a Pop that is "closest of very close". Brightly highlight it,
		// to notify the player that if dropped, the Thing of the held Pop will become
		// a sibling of the Thing:s corresponding to the bright-highlighed mesh sections

		UE_LOG(LogTemp, Warning, TEXT("APopManager::HighlightCloseTopChildren: Will make closestPop %p (%s) BRIGHT! picked=%s"),
			   closestPop, *closestPop->thingRef->name, (closestPop->picked) ? TEXT("true") : TEXT("false"));

		closestPop->Highlight(-1, 2);

		brightPop = closestPop;

		verify(brightPop != pickedPop);

	}

}


bool APopManager::IsClose(APop* pop, APop* refPop) {
	AvreduGameMode* theGameMode = GetGameMode();
	return IsCloseAux(theGameMode->closeDistanceSquared, pop, refPop);
}



bool APopManager::IsVeryClose(APop* pop, APop* refPop) {
	AvreduGameMode* theGameMode = GetGameMode();
	return IsCloseAux(theGameMode->veryCloseDistanceSquared, pop, refPop);
}

#if 0
bool APopManager::IsClose(APop* pop, APop* refPop) {
	AvreduGameMode* theGameMode = GetGameMode();
	
	FVector loc = pop->GetActorLocation();
	FVector refLoc = refPop->GetActorLocation();
	float distSquared = (refLoc - loc).SizeSquared();

	UE_LOG(LogTemp, Warning, TEXT("APopManager::IsClose: pop1 loc: X=%f  Y=%f  Z=%f,   pop2 loc: X=%f  Y=%f  Z=%f"),
		   loc.X, loc.Y, loc.Z, refLoc.X, refLoc.Y, refLoc.Z);

	UE_LOG(LogTemp, Warning, TEXT("APopManager::IsClose: distSquared=%f, theGameMode->closeDistanceSquared=%f"),
		   distSquared, theGameMode->closeDistanceSquared);

	return (distSquared <= theGameMode->closeDistanceSquared);
}
#endif


bool APopManager::IsCloseAux(float distanceLimit, APop* pop, APop* refPop) {
	AvreduGameMode* theGameMode = GetGameMode();

	FVector loc = pop->GetActorLocation();
	FVector refLoc = refPop->GetActorLocation();
	float distSquared = (refLoc - loc).SizeSquared();

	UE_LOG(LogTemp, Warning, TEXT("APopManager::IsClose: pop1 loc: X=%f  Y=%f  Z=%f,   pop2 loc: X=%f  Y=%f  Z=%f"),
		loc.X, loc.Y, loc.Z, refLoc.X, refLoc.Y, refLoc.Z);

	return (distSquared <= distanceLimit);
}


bool APopManager::IsCloser(APop* pop1, APop* pop2, APop* refPop) {

	if (pop2 == nullptr)
		return true;

	UWorld* const World = GetWorld();
	AvreduGameMode* theGameMode = (AvreduGameMode*)World->GetAuthGameMode();
	FVector loc1 = pop1->GetActorLocation();
	FVector loc2 = pop2->GetActorLocation();
	FVector refLoc = refPop->GetActorLocation();
	float dist1Squared = (refLoc - loc1).SizeSquared();
	float dist2Squared = (refLoc - loc2).SizeSquared();

	UE_LOG(LogTemp, Warning, TEXT("APopManager::IsCloser: pop1 loc: X=%f  Y=%f  Z=%f,   pop2 loc: X=%f  Y=%f  Z=%f,   refPop loc: X=%f  Y=%f  Z=%f"),
		loc1.X, loc1.Y, loc1.Z, loc2.X, loc2.Y, loc2.Z, refLoc.X, refLoc.Y, refLoc.Z);

	return (dist1Squared < dist2Squared);
}
