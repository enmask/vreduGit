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
	
}

// Called every frame
void APopManager::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("APopManager::Tick called"));

	Super::Tick(DeltaTime);

}


APop* APopManager::Spawn(AThing* thing, FTransform transform) {

	UE_LOG(LogTemp, Warning, TEXT("APopManager::Spawn called"));

	/*
	// Dummy transform data
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	FTransform trafo(Location);
	*/

	//
	// Start spawning
	//

	UWorld* const World = GetWorld();
	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("APopManager::Spawn: World exists"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("APopManager::Spawn: World does NOT exist"));
	}

	APop* newPop = World->SpawnActorDeferred<APop>(APop::StaticClass(), transform);

	//
	// Initialize the Pop
	//
	newPop->init(thing, transform);

	//
	// Finish spawning
	//
	newPop->FinishSpawning(transform);

	UE_LOG(LogTemp, Warning, TEXT("APopManager::Spawn: Will return newPop=%p"), newPop);
	return newPop;
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

	FVector locParent = parent->GetActorLocation();
	FVector locChild = toBeChild->GetActorLocation();
	FVector locDifference = locChild-locParent;

	UE_LOG(LogTemp,
		   Warning,
		   TEXT("APopManager::AddChild: locParent: X=%f Y=%f Z=%f,  locChild: X=%f Y=%f Z=%f,  locDiff: X=%f Y=%f Z=%f,"),
		   locParent.X, locParent.Y, locParent.Z, locChild.X, locChild.Y, locChild.Z, locDifference.X, locDifference.Y, locDifference.Z);

#if 0 /* Only location considered */
	parent->thingRef->subThingRelTrafos.Add(FTransform(toBeChild->GetActorLocation() - parent->GetActorLocation()));
#else /* Complete trafo considered */
	FTransform subThingRelTrafo = UKismetMathLibrary::ConvertTransformToRelative(parent->GetTransform(), toBeChild->GetTransform());
	parent->thingRef->subThingRelTrafos.Add(subThingRelTrafo);
#endif



	parent->thingRef->subThingRoles.Add("undefined");

	// Destroy toBeChild Pop
	toBeChild->Destroy();

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
