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
	
	numPops = 0;
}

// Called every frame
void APopManager::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("APopManager::Tick called"));

	Super::Tick(DeltaTime);

	UWorld* const World = GetWorld();
	AvreduGameMode* theGameMode = (AvreduGameMode*)World->GetAuthGameMode();
	TSet< APop* > wantsPicking = theGameMode->GetWantsPicking();

	for (APop* pop : wantsPicking) {

		UE_LOG(LogTemp, Warning, TEXT("APopManager::Tick: pop %p wants picking"), pop);

		pop->picked ? Drop(pop) : Pickup(pop);
		theGameMode->RemoveWantsPicking(pop);
	}

}

void APopManager::Pickup(APop* pop) {

	UE_LOG(LogTemp, Warning, TEXT("APopManager::Pickup called, pop=%p"), pop);

	UActorComponent* motCon = GetRightMotionController();
	pop->DisableComponentsSimulatePhysics();
	pop->AttachToComponent(Cast<USceneComponent>(motCon),
						   FAttachmentTransformRules::SnapToTargetIncludingScale,
						   NAME_None);

	HighlightCloseTopChildren(pop);

	pop->picked = true;

}

#if 1 /* Just drop, don't join */
void APopManager::Drop(APop* pop) {
	pop->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	pop->mesh->SetSimulatePhysics(true);
	pop->picked = false;
}
#endif

#if 0 /* Drop and insert as child to Pop */
void APop::Drop() {
	GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	mesh->SetSimulatePhysics(true);
	picked = false;

	// thePopManager->AddChild(...);
}
#endif


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


APop* APopManager::Spawn(AThing* thing, FTransform transform) {

	//
	// Start spawning
	//

	UWorld* const World = GetWorld();

	APop* newPop = World->SpawnActorDeferred<APop>(APop::StaticClass(), transform);

	//
	// Initialize the Pop
	//
	newPop->init(thing, transform);

	//
	// Finish spawning
	//
	newPop->FinishSpawning(transform);

	numPops++;

	UE_LOG(LogTemp, Warning, TEXT("APopManager::Spawn: Will return newPop=%p with name=<%s>, numPops=%d"),
		   newPop, *newPop->GetName(), numPops);
	return newPop;
}

//
// Destroy a Pop
//
void APopManager::DestroyPop(APop* pop) {

	UE_LOG(LogTemp, Warning, TEXT("APopManager::DestroyPop: Will return newPop=%p with name=<%s> ..."),
		   pop, *pop->GetName());

	pop->Destroy();
	numPops--;

	UE_LOG(LogTemp, Warning, TEXT("...  After DestroyPop, numPops=%d"), numPops);

}




void APopManager::AddChild(APop* parent, APop* toBeChild) {

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

	// Rebuild mesh to get the combined mesh
	parent->BuildMesh();
}


// Deep copy a Pop and all its Thing:s.
// Return the clone Pop.
//APop* APopManager::Clone(APop* origPop, FString cloneName) {
APop* APopManager::Clone(APop* p, FString cloneName) {

	// Pseudo code:
	//
	/// Clone the Pop
	// clonePop = new APop
	// cloneThing = new AThing
	// cloneThing.name = cloneName
	// origThing = origPop.thingRef
	//
	// for (child in origThing.subThings) {
	//		p = new APop
	//		origPop.subThing
	//
	//		Clone(
	//
	
	//
	//  Pop PopManager::Clone(Pop p, FString cloneName)
	//

	UWorld* const World = GetWorld();
	AThingManager* theThingManager = ((AvreduGameMode*)World->GetAuthGameMode())->theThingManager;

	AThing* cloneThing = theThingManager->Clone(p->thingRef, cloneName);

	// HACK: Temporary hack, move the clone along x so that it doesn't collide with the original
	FTransform cloneTrafo = p->GetActorTransform();
	FVector cloneLoc = cloneTrafo.GetLocation();
#if 0 /* Deactivated the hack */
	cloneLoc.X += 60.0;
	cloneLoc.Z += 30.0;
	cloneTrafo.SetLocation(cloneLoc);
#endif

	UE_LOG(LogTemp,
		   Warning,
		   TEXT("APopManager::Clone: orig loc X=%f Y=%f Z=%f,  cloneLoc: X=%f Y=%f Z=%f"),
		   p->GetActorTransform().GetLocation().X, p->GetActorTransform().GetLocation().Y, p->GetActorTransform().GetLocation().Z,
		   cloneLoc.X, cloneLoc.Y, cloneLoc.Z);

	APop* clonePop = Spawn(cloneThing, cloneTrafo);

	//		clonePop->thingRef = theThingManager->Clone(p->thingRef, cloneName)
	//
	//
	//  Thing ThingManager::Clone(Thing t, FString cloneName)
	//
	//		cloneThing = new AThing
	//		cloneThing->name = cloneName
	//		
	//		for (child in t->subThings,  childRelTrafo in t->subThingRelTrafos,  childRole in t->subThingRoles) {
	//			cloneThing->subThings.Add(Clone(child))
	//			cloneThing->subThingRelTrafos.Add(FTransform(childRelTrafo))
	//			cloneThing->subThingRoles.Add(childRole)
	//
	//      

	return clonePop;
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
// TODO: Maybe implement FindCloseTopChildren instead
//
void APopManager::HighlightCloseTopChildren(APop* pop) {

	/* Sweep solution, will probably not use that...
	FCollisionShape MySphere = FCollisionShape::MakeSphere(500.0f); // 5M Radius
	TArray<FHitResults> OutResults;
	GetWorld()->SweepMultiByChannel(OutResults, SweepStart, SweepEnd, FQuat::Identity, TraceChannel, MySphere);
	*/

	TArray<AActor*> thePops;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APop::StaticClass(), thePops);

	// All Pop:s found in the level should equal the number of Pop:s that the PopManager keeps track of
	verify(thePops.Num() == numPops);

	for (auto& currentAct : thePops) {    //For example lets set the actors location to (0,0,0)
		//currentPop->SetActorLocation(FVector(0, 0, 0), false, 0, ETeleportType::None);
		
		APop* currentPop = Cast<APop>(currentAct);
		UE_LOG(LogTemp, Warning, TEXT("APopManager::HighlightCloseTopChildren: currentPop=%p, name=%s, thing name=%s"),
			   currentPop, *currentPop->GetName(), *currentPop->thingRef->name);

		if (currentPop == pop)
			continue;

		if (IsClose(currentPop, pop)) {
			UE_LOG(LogTemp, Warning, TEXT("APopManager::HighlightCloseTopChildren: currentPop <%s> *IS* close to pop <%s>"),
				   *currentPop->thingRef->name, *pop->thingRef->name);

			// Hightlight all sections of this Pop
			currentPop->Highlight(-1, 1);

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("APopManager::HighlightCloseTopChildren: currentPop <%s> is NOT close to pop <%s>"),
				*currentPop->thingRef->name, *pop->thingRef->name);
		}
	}

}


bool APopManager::IsClose(APop* pop1, APop* pop2) {
	UWorld* const World = GetWorld();
	AvreduGameMode* theGameMode = (AvreduGameMode*)World->GetAuthGameMode();
	FVector loc1 = pop1->GetActorLocation();
	FVector loc2 = pop2->GetActorLocation();
	float distSquared = (loc2 - loc1).SizeSquared();

	UE_LOG(LogTemp, Warning, TEXT("APopManager::IsClose: pop1 loc: X=%f  Y=%f  Z=%f,   pop2 loc: X=%f  Y=%f  Z=%f"),
		   loc1.X, loc1.Y, loc1.Z, loc2.X, loc2.Y, loc2.Z);


	UE_LOG(LogTemp, Warning, TEXT("APopManager::IsClose: distSquared=%f, theGameMode->closeDistanceSquared=%f"),
		   distSquared, theGameMode->closeDistanceSquared);

	return (distSquared <= theGameMode->closeDistanceSquared);

}