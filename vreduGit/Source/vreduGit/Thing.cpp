// Fill out your copyright notice in the Description page of Project Settings.

#include "Thing.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Core/Public/Misc/Parse.h"
#include "Util.h"


//DEFINE_LOG_CATEGORY(LogVredu);

// Sets default values
AThing::AThing()
{
	//UE_LOG(LogTemp, Warning, TEXT("AThing::AThing called"));

	//int a = 2;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AThing::init(FString theName) {
	//UE_LOG(LogTemp, Warning, TEXT("AThing::init called"));

	name = theName;
}

// Called when the game starts or when spawned
void AThing::BeginPlay() {
	//UE_LOG(LogTemp, Warning, TEXT("AThing::BeginPlay called"));

	Super::BeginPlay();

#if 0 /* Test command line args */
	FString fileName;
	uint32 startPose;

	//string
	if (FParse::Value(FCommandLine::Get(), TEXT("scb"), fileName)) {
		//fileName = fileName.Replace(TEXT("="), TEXT("")).Replace(TEXT("\""), TEXT("")); // replace quotes
		//_SCBFile = fileName;
		
	}

	//integer
	if (FParse::Value(FCommandLine::Get(), TEXT("startPose"), startPose)) {
		_startPose = startPose;
	}

	//boolean
	if (FParse::Param(FCommandLine::Get(), TEXT("skinByClass"))) {
		_skinByClass = true;
	}
#else
	/* Try 2 */

	if (FParse::Param(FCommandLine::Get(), TEXT("MyFlagPresent")))
	{
		UE_LOG(LogTemp, Warning, TEXT("AThing::BeginPlay: Found MyFlagPresent in the command line"));
	}

#endif


}

// Called every frame
void AThing::Tick(float DeltaTime) {
	//UE_LOG(LogTemp, Warning, TEXT("AThing::Tick called"));

	Super::Tick(DeltaTime);

#if 0
	if (FParse::Param(FCommandLine::Get(), TEXT("MyFlagPresent")))
	{
		UE_LOG(LogTemp, Warning, TEXT("AThing::Tick: Found MyFlagPresent in the command line"));
	}
#endif

}

void AThing::Add(AThing* subThing, FTransform subThingRelTrafo, FString subThingRole) {

	UE_LOG(LogTemp, Warning, TEXT("AThing::Add() called"));

	verify(subThing != this);

	int32 thingIx = subThings.Add(subThing);
	int32 trafoIx = subThingRelTrafos.Add(subThingRelTrafo);
	int32 roleIx = subThingRoles.Add(subThingRole);

	verify(thingIx == trafoIx);
	verify(thingIx == roleIx);
}


int AThing::CountAtoms() {

	if (subThings.Num() == 0) {
		return 1;
	}

	int sum = 0;

	for (AThing* t : subThings)
	{
		sum += t->CountAtoms();
	}

	return sum;
}



void AThing::Log2DimVertsArray(TArray<FVertexArray> verts2Dim) {

	UE_LOG(LogTemp, Warning, TEXT("AThing::Log2DimVertsArray() called"));


	for (int i = 0; i < verts2Dim.Num(); ++i) {
		UE_LOG(LogTemp, Warning, TEXT("AThing::Log2DimVertsArray(), here comes vertArray with ix %d"), i);
		FVertexArray vertArray = verts2Dim[i];
		vertArray.Log();
	}

}


void AThing::Log2DimIntsArray(TArray<FInt32Array> ints2Dim) {

	UE_LOG(LogTemp, Warning, TEXT("AThing::Log2DimIntsArray() called"));


	for (int i = 0; i < ints2Dim.Num(); ++i) {
		UE_LOG(LogTemp, Warning, TEXT("AThing::Log2DimIntsArray(), here comes intArray with ix %d"), i);
		ints2Dim[i].Log();
	}

}


void AThing::Log2DimColorArray(TArray<FColorArray> colors2Dim) {

	UE_LOG(LogTemp, Warning, TEXT("AThing::Log2DimColorArray() called"));


	for (int i = 0; i < colors2Dim.Num(); ++i) {
		UE_LOG(LogTemp, Warning, TEXT("AThing::Log2DimColorArray(), here comes colorArray with ix %d"), i);
		colors2Dim[i].Log();
	}

}


FString AThing::ToString() {

	FString str = FString::Printf(TEXT("Id: %s\n  No. of atoms: %d"), *name, CountAtoms());

	return str;
}



void AThing::ComputeMeshData(TArray<FVertexArray>& verts2Dim, TArray<FInt32Array>& tris2Dim,
	TArray<FColorArray>& colors2Dim, TArray<FTrafoArray>& collisions2Dim,
	TArray<FVector>& vertices, TArray<int32>& Triangles,
	TArray<FVector>& normals, TArray<FVector2D>& UV0,
	TArray<FColor>& vertexColors, TArray<FRuntimeMeshTangent>& tangents,
	TArray<FTransform>& collisionCubePositions) {

	UE_LOG(LogTemp, Warning, TEXT("AThing::ComputeMeshData() called, thing-this=%p, name=%s"),
		   this, *this->name);


	FTransform trafoZero(FQuat(0, 0, 0, 1), FVector(0, 0, 0), FVector(1, 1, 1));



	ComputeMeshDataAux(0, 0, verts2Dim, tris2Dim, colors2Dim, collisions2Dim,
					   trafoZero, vertices, Triangles, normals, UV0, vertexColors, tangents, collisionCubePositions);

	/* Log2DimVertsArray(verts2Dim);
	Log2DimIntsArray(tris2Dim);
	Log2DimColorArray(colors2Dim);
	*/

	UE_LOG(LogTemp, Warning, TEXT("AThing::ComputeMeshData() end, vertices.Num()=%d"), vertices.Num());

}


void AThing::ComputeMeshDataAux(int32 treeLevel, int32 subtreeNo,
	TArray<FVertexArray>& verts2Dim, TArray<FInt32Array>& tris2Dim,
	TArray<FColorArray>& colors2Dim, TArray<FTrafoArray>& collisions2Dim,
	FTransform baseTrafo, TArray<FVector>& vertices, TArray<int32>& Triangles,
	TArray<FVector>& normals, TArray<FVector2D>& UV0,
	TArray<FColor>& vertexColors, TArray<FRuntimeMeshTangent>& tangents,
	TArray<FTransform>& collisionCubePositions) {

	FVector loc = baseTrafo.GetLocation();
	UE_LOG(LogTemp, Warning, TEXT("AThing::ComputeMeshDataAux() called, Thing-this=%p, name=%s, treeLevel=%d, subtreeNo=%d, baseTrafo location is  %f  %f  %f"),
		   this, *name, treeLevel, subtreeNo, loc.X, loc.Y, loc.Z);

	if (subThings.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("AThing::ComputeMeshDataAux() found an ATOM, trafo location is  %f  %f  %f"), loc.X, loc.Y, loc.Z);

		// Add mesh data for this atom
		AddMeshDataForOneAtom(treeLevel, subtreeNo, verts2Dim, tris2Dim, colors2Dim, collisions2Dim, baseTrafo, vertices, Triangles, normals, UV0, vertexColors, tangents);

		// Note where the caller needs to place a grab cube for this atom
		collisionCubePositions.Add(baseTrafo);

		collisions2Dim[subtreeNo].Trafos.Add(baseTrafo);

	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("AThing::ComputeMeshDataAux() found an non-ATOM with %d children, check them recursively"), subThings.Num());


#if 1 /* Pre-logging, debug possible cyclic links */
		for (int32 thingIx = 0; thingIx < subThings.Num(); ++thingIx) {
			AThing* subThing = subThings[thingIx];
			UE_LOG(LogTemp, Warning, TEXT("AThing::ComputeMeshDataAux(): pre-logging: subThing=%p with name=%s"), subThing, *subThing->name);
		}
#endif


		// Build meshes for each sub-tree recursively
		for (int32 thingIx = 0; thingIx < subThings.Num(); ++thingIx) {

			AThing* subThing = subThings[thingIx];

			UE_LOG(LogTemp, Warning, TEXT("AThing::ComputeMeshDataAux(): subThing=%p with name=%s"), subThing, *subThing->name);

			int32 trafoIx = thingIx;
			FTransform subThingTrafo = subThingRelTrafos[trafoIx];

			FTransform accumulatedTrafo = subThingTrafo * baseTrafo;

			// What baseTrafo should we pass here?
			// Well, we already have a baseTrafo that says how this (parent) thing is placed relative the ROOT
			// (yes, that's right, because I cram all atoms into one mesh section, all relative to one base point).
			// The baseTrafo for this child should say how the child shall be placed relative to the ROOT.
			// So I should use composition, baseTrafo * 
			subThing->ComputeMeshDataAux(treeLevel + 1, (treeLevel == 0) ? thingIx : subtreeNo,
										 verts2Dim, tris2Dim, colors2Dim, collisions2Dim,
										 accumulatedTrafo, vertices, Triangles, normals,
										 UV0, vertexColors, tangents, collisionCubePositions);
		}
	}
}

// Add vertex to vertices and remember the nex vertex index in an array so that the tris can refer to it correctly
void AThing::AddVertex(int32 treeLevel, int32 subtreeNo,
					   TArray<FVertexArray>& verts2Dim, TArray<FColorArray>& colors2Dim, TArray<FTrafoArray>& collisions2Dim,
					   FTransform baseTrafo, FVector origLocation, TArray<FVector>& vertices, TArray<int32>& newIndices) {

	//UE_LOG(LogTemp, Warning, TEXT("AThing::AddVertex called, treeLevel=%d, subtreeNo=%d"), treeLevel, subtreeNo);


	//FVector baseLoc = baseTrafo.GetLocation();
	//UE_LOG(LogTemp, Warning, TEXT("AThing::AddVertex called, baseTrafo location= %f  %f  %f, origLocation= %f  %f  %f"), baseLoc.X, baseLoc.Y, baseLoc.Z, origLocation.X, origLocation.Y, origLocation.Z);

	FTransform origTrafo(FQuat(0, 0, 0, 1), origLocation, FVector(1, 1, 1));

	// ConvertTransformToRelative returns the given transform, converted to be relative to the given ParentTransform.
	// Example: AToB = ConvertTransformToRelative(AToWorld, BToWorld) to compute A relative to B.
	// *** NOTE: There seems to be a bug in UE4. The parameters are swapped.
	// So we must send ParentTransform as first parameter and Transform as the second!
	//FTransform relTrafo = UKismetMathLibrary::ConvertTransformToRelative(baseTrafo, origTrafo);

	// TEST: Try to swap args, the above didn't work
	//FTransform relTrafo = UKismetMathLibrary::ConvertTransformToRelative(origTrafo, baseTrafo);

	// Try 2, MULTIPLY
	//FTransform relTrafo = baseTrafo * origTrafo;

	// Try 3, MULTIPLY with reversed ORDER
	FTransform relTrafo = origTrafo * baseTrafo;

	FVector relLoc = relTrafo.GetLocation();
	//UE_LOG(LogTemp, Warning, TEXT("AThing::AddVertex, relLoc became= %f  %f  %f"), relLoc.X, relLoc.Y, relLoc.Z);

	int32 newIndex = vertices.Add(relTrafo.GetLocation());

	//
	// Now add to the 2-dim verts array
	// 
	if (verts2Dim.Num() <= subtreeNo) {

		// It should never happen that verts2Dim.Num() < subtreeNo
		verify(verts2Dim.Num() == subtreeNo);

		// There is no verts array for this tree level, so we need to create a new empty one
		FVertexArray emptyVertArray;
		verts2Dim.Add(emptyVertArray);

		// We need a color array for each vert array, so create a new empty color array too
		FColorArray emptyColorArray;
		colors2Dim.Add(emptyColorArray);

		// We need a transform array (for the colliders) for each vert array, so create a new empty transform array too
		FTrafoArray emptyTrafoArray;
		collisions2Dim.Add(emptyTrafoArray);

	}

	int32 newIndex2 = verts2Dim[subtreeNo].Verts.Add(relTrafo.GetLocation());

	newIndices.Add(newIndex2);
	
	int32 newColorIndex = colors2Dim[subtreeNo].Colors.Add(FColor::Blue);

}

void AThing::AddMeshDataForOneAtom(int32 treeLevel, int32 subtreeNo,
	TArray<FVertexArray>& verts2Dim, TArray<FInt32Array>& tris2Dim,
	TArray<FColorArray>& colors2Dim, TArray<FTrafoArray>& collisions2Dim,
	FTransform baseTrafo,
	TArray<FVector>& vertices, TArray<int32>& Triangles,
	TArray<FVector>& normals, TArray<FVector2D>& UV0,
	TArray<FColor>& vertexColors, TArray<FRuntimeMeshTangent>& tangents) {

	TArray<int32> newIndices;

	// Cube from Blender
	FVector vertx0(1.000000, -1.000000, -1.000000);
	FVector vertx1(1.000000, -1.000000, 1.000000);
	FVector vertx2(-1.000000, -1.000000, 1.000000);
	FVector vertx3(-1.000000, -1.000000, -1.000000);
	FVector vertx4(1.000000, 1.000000, -0.999999);
	FVector vertx5(0.999999, 1.000000, 1.000001);
	FVector vertx6(-1.000000, 1.000000, 1.000000);
	FVector vertx7(-1.000000, 1.000000, -1.000000);

	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, collisions2Dim, baseTrafo, 30.0f * vertx0, vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, collisions2Dim, baseTrafo, 30.0f * vertx1, vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, collisions2Dim, baseTrafo, 30.0f * vertx2, vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, collisions2Dim, baseTrafo, 30.0f * vertx3, vertices, newIndices);

	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, collisions2Dim, baseTrafo, 30.0f * vertx4, vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, collisions2Dim, baseTrafo, 30.0f * vertx5, vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, collisions2Dim, baseTrafo, 30.0f * vertx6, vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, collisions2Dim, baseTrafo, 30.0f * vertx7, vertices, newIndices);

	//
	// Now add to the 2-dim tris array
	// 
	if (tris2Dim.Num() <= subtreeNo) {

		if (tris2Dim.Num() < subtreeNo) {
			UE_LOG(LogTemp, Error,
				TEXT("ERROR: tris2Dim.Num()=%d and subtreeNo=%d. It should never happen that tris2Dim.Num() < subtreeNo!!! < (By the way, treeLevel=%d)"),
				tris2Dim.Num(), subtreeNo, treeLevel);
			return;
		}

		// There is no verts array for this tree level, so we need to create a new empty one
		FInt32Array emptyTri;
		tris2Dim.Add(emptyTri);
	}

	// Seems to be left (or right) side bot-triangle
	tris2Dim[subtreeNo].Ints.Add(newIndices[1]); // Was 1 3 0, try 1 0 3
	tris2Dim[subtreeNo].Ints.Add(newIndices[0]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[3]);

	// Seems to be right (or left) side bot-triangle
	tris2Dim[subtreeNo].Ints.Add(newIndices[7]); // Was 7 5 4, try 7 4 5
	tris2Dim[subtreeNo].Ints.Add(newIndices[4]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[5]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[4]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[0]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[1]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[5]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[1]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[2]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[2]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[3]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[7]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[0]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[4]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[7]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[1]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[3]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[2]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[7]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[5]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[6]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[4]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[1]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[5]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[5]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[2]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[6]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[2]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[7]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[6]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[0]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[7]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[3]);

	// Vertical texture
	UV0.Add(FVector2D(0.0f, 1.0f));
	UV0.Add(FVector2D(0.0f, 1.0f));
	UV0.Add(FVector2D(0.0f, 1.0f));
	UV0.Add(FVector2D(0.0f, 1.0f));

	UV0.Add(FVector2D(0.0f, 0.0f));
	UV0.Add(FVector2D(0.0f, 0.0f));
	UV0.Add(FVector2D(0.0f, 0.0f));
	UV0.Add(FVector2D(0.0f, 0.0f));

}


/*
void AThing::Add(TArray<FTransform> trafos) {

	UE_LOG(LogTemp, Warning, TEXT("AThing::Add(...Trafos...) called, add %d stuff"), trafos.Num());

	// TODO: Add to EXISTING group, if there is one!
	group.Append(trafos);
}
*/



