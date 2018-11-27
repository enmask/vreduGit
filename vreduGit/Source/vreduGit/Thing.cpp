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
	TArray<FColorArray>& colors2Dim,
	TArray<FVector>& vertices, TArray<int32>& Triangles,
	TArray<FVector>& normals, TArray<FVector2D>& UV0,
	TArray<FColor>& vertexColors, TArray<FRuntimeMeshTangent>& tangents,
	TArray<FTransform>& collisionCubePositions) {

	FTransform trafoZero(FQuat(0, 0, 0, 1), FVector(0, 0, 0), FVector(1, 1, 1));



	ComputeMeshDataAux(0, 0, verts2Dim, tris2Dim, colors2Dim, trafoZero, vertices, Triangles, normals, UV0, vertexColors, tangents, collisionCubePositions);

	Log2DimVertsArray(verts2Dim);
	Log2DimIntsArray(tris2Dim);
	Log2DimColorArray(colors2Dim);

	UE_LOG(LogTemp, Warning, TEXT("AThing::ComputeMeshData() end, vertices.Num()=%d"), vertices.Num());
}


void AThing::ComputeMeshDataAux(int32 treeLevel, int32 subtreeNo,
	TArray<FVertexArray>& verts2Dim, TArray<FInt32Array>& tris2Dim,
	TArray<FColorArray>& colors2Dim, FTransform baseTrafo,
	TArray<FVector>& vertices, TArray<int32>& Triangles,
	TArray<FVector>& normals, TArray<FVector2D>& UV0,
	TArray<FColor>& vertexColors, TArray<FRuntimeMeshTangent>& tangents,
	TArray<FTransform>& collisionCubePositions) {

	FVector loc = baseTrafo.GetLocation();
	//UE_LOG(LogTemp, Warning, TEXT("AThing::ComputeMeshDataAux() called, treeLevel=%d, subtreeNo=%d, baseTrafo location is  %f  %f  %f"),
	//	   treeLevel, subtreeNo, loc.X, loc.Y, loc.Z);

	if (subThings.Num() == 0) {
		//UE_LOG(LogTemp, Warning, TEXT("AThing::ComputeMeshDataAux() found an ATOM, trafo location is  %f  %f  %f"), loc.X, loc.Y, loc.Z);

		// Add mesh data for this atom
		AddMeshDataForOneAtom(treeLevel, subtreeNo, verts2Dim, tris2Dim, colors2Dim, baseTrafo, vertices, Triangles, normals, UV0, vertexColors, tangents);

		// Note where the called needs to place a grab cube for this atom
		collisionCubePositions.Add(baseTrafo);

	}
	else {

		//UE_LOG(LogTemp, Warning, TEXT("AThing::ComputeMeshDataAux() found an non-ATOM with %d children, check them recursively"), subThings.Num());

		// Build meshes for each sub-tree recursively
		for (int32 thingIx = 0; thingIx < subThings.Num(); ++thingIx) {

			AThing* subThing = subThings[thingIx];

			//UE_LOG(LogTemp, Warning, TEXT("AThing::ComputeMeshDataAux(): subThing=%p with name=%s"), subThing, *subThing->name);

			int32 trafoIx = thingIx;
			FTransform subThingTrafo = subThingRelTrafos[trafoIx];

			FTransform accumulatedTrafo = subThingTrafo * baseTrafo;

			/*
			UE_LOG(LogTemp, Warning,
				TEXT("AThing::ComputeMeshDataAux() composed the baseTrafo  %f  %f  %f  with subThingTrafo  %f  %f  %f  to get accumulatedTrafo  %f  %f  %f"),
				baseTrafo.GetLocation().X, baseTrafo.GetLocation().Y, baseTrafo.GetLocation().Z,
				subThingTrafo.GetLocation().X, subThingTrafo.GetLocation().Y, subThingTrafo.GetLocation().Z,
				accumulatedTrafo.GetLocation().X, accumulatedTrafo.GetLocation().Y, accumulatedTrafo.GetLocation().Z);
			*/

			/*
			// START LOGGING
			FVector baseLoc = baseTrafo.GetLocation();
			FQuat baseRotQ(baseTrafo.GetRotation());
			FVector baseRotEul(baseRotQ.Euler());
			FRotator baseRot(baseRotEul.Rotation());

			FVector subLoc = subThingTrafo.GetLocation();
			FQuat subRotQ(subThingTrafo.GetRotation());
			FVector subRotEul(subRotQ.Euler());
			FRotator subRot(subRotEul.Rotation());

			FVector accumLoc = accumulatedTrafo.GetLocation();
			FQuat accumRotQ(accumulatedTrafo.GetRotation());
			FVector accumRotEul(accumRotQ.Euler());
			FRotator acccumRot(accumRotEul.Rotation());

			UE_LOG(LogTemp, Warning,
				TEXT("AThing::...Aux(), more details on the baseTrafo  baseLoc  %f  %f  %f,  baseRotQ   W=%f  X=%f  Y=%f  Z=%f,   baseRotEul  X (yaw?)=%f  Y (pitch?)=%f  Z (roll?)=%f\n"),
				baseLoc.X, baseLoc.Y, baseLoc.Z, baseRotQ.W, baseRotQ.X, baseRotQ.Y, baseRotQ.Z, baseRotEul.X, baseRotEul.Y, baseRotEul.Z);
			UE_LOG(LogTemp, Warning,
				TEXT("AThing::...Aux(), more details on the subThingTrafo  subLoc  %f  %f  %f,  subRotQ   W=%f  X=%f  Y=%f  Z=%f,   subRotEul  X (yaw?)=%f  Y (pitch?)=%f  Z (roll?)=%f\n"),
				subLoc.X, subLoc.Y, subLoc.Z, subRotQ.W, subRotQ.X, subRotQ.Y, subRotQ.Z, subRotEul.X, subRotEul.Y, subRotEul.Z);
			UE_LOG(LogTemp, Warning,
				TEXT("AThing::...Aux(), more details on the accumulatedTrafo  accumLoc  %f  %f  %f,  accumRotQ   W=%f  X=%f  Y=%f  Z=%f,   accumRotEul  X (yaw?)=%f  Y (pitch?)=%f  Z (roll?)=%f\n"),
				accumLoc.X, accumLoc.Y, accumLoc.Z, accumRotQ.W, accumRotQ.X, accumRotQ.Y, accumRotQ.Z, accumRotEul.X, accumRotEul.Y, accumRotEul.Z);

			// END LOGGING
			*/


			// What baseTrafo should we pass here?
			// Well, we already have a baseTrafo that says how this (parent) thing is placed relative the ROOT
			// (yes, that's right, because I cram all atoms into one mesh section, all relative to one base point).
			// The baseTrafo for this child should say how the child shall be placed relative to the ROOT.
			// So I should use composition, baseTrafo * 
			subThing->ComputeMeshDataAux(treeLevel + 1, (treeLevel == 0) ? thingIx : subtreeNo, verts2Dim, tris2Dim, colors2Dim, accumulatedTrafo, vertices, Triangles, normals, UV0, vertexColors, tangents, collisionCubePositions);
		}
	}
}

// Add vertex to vertices and remember the nex vertex index in an array so that the tris can refer to it correctly
void AThing::AddVertex(int32 treeLevel, int32 subtreeNo, TArray<FVertexArray>& verts2Dim, TArray<FColorArray>& colors2Dim,
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

	/*
	// START LOGGING
	FVector baseLoc = baseTrafo.GetLocation();
	FQuat baseRotQ(baseTrafo.GetRotation());
	FVector baseRotEul(baseRotQ.Euler());

	FVector origLoc = origTrafo.GetLocation();
	FQuat origRotQ(origTrafo.GetRotation());
	FVector origRotEul(origRotQ.Euler());

	//FVector relLoc = relTrafo.GetLocation();
	FQuat relRotQ(relTrafo.GetRotation());
	FVector relRotEul(relRotQ.Euler());

	UE_LOG(LogTemp, Warning,
		TEXT("AddVertex(), more details on the baseTrafo  baseLoc  %f  %f  %f,  baseRotQ   W=%f  X=%f  Y=%f  Z=%f,   baseRotEul  X (yaw?)=%f  Y (pitch?)=%f  Z (roll?)=%f\n"),
		baseLoc.X, baseLoc.Y, baseLoc.Z, baseRotQ.W, baseRotQ.X, baseRotQ.Y, baseRotQ.Z, baseRotEul.X, baseRotEul.Y, baseRotEul.Z);
	UE_LOG(LogTemp, Warning,
		TEXT("AddVertex(), more details on the origThingTrafo  origLoc  %f  %f  %f,  origRotQ   W=%f  X=%f  Y=%f  Z=%f,   origRotEul  X (yaw?)=%f  Y (pitch?)=%f  Z (roll?)=%f\n"),
		origLoc.X, origLoc.Y, origLoc.Z, origRotQ.W, origRotQ.X, origRotQ.Y, origRotQ.Z, origRotEul.X, origRotEul.Y, origRotEul.Z);
	UE_LOG(LogTemp, Warning,
		TEXT("AddVertex(), more details on the relTrafo  relLoc  %f  %f  %f,  relRotQ   W=%f  X=%f  Y=%f  Z=%f,   relRotEul  X (yaw?)=%f  Y (pitch?)=%f  Z (roll?)=%f\n"),
		relLoc.X, relLoc.Y, relLoc.Z, relRotQ.W, relRotQ.X, relRotQ.Y, relRotQ.Z, relRotEul.X, relRotEul.Y, relRotEul.Z);

	// END LOGGING
	*/



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

		// We need a color for each vert, so create a new empty color array too
		FColorArray emptyColorArray;
		int32 newColorArrayIndex = colors2Dim.Add(emptyColorArray);

		UE_LOG(LogTemp, Warning,
			   TEXT("AThing::AddVertex: Adding new color ARRAY, newColorArrayIndex = %d"), newColorArrayIndex);

	}

	int32 newIndex2 = verts2Dim[subtreeNo].Verts.Add(relTrafo.GetLocation());

	newIndices.Add(newIndex2);
	
	int32 newColorIndex = colors2Dim[subtreeNo].Colors.Add(FColor::Blue);
	UE_LOG(LogTemp, Warning,
		   TEXT("AThing::AddVertex: Adding new color, newColorIndex = %d, newIndex2 = %d. subtreeNo=%d"), newColorIndex, newIndex2, subtreeNo);

}

void AThing::AddMeshDataForOneAtom(int32 treeLevel, int32 subtreeNo,
	TArray<FVertexArray>& verts2Dim, TArray<FInt32Array>& tris2Dim,
	TArray<FColorArray>& colors2Dim, FTransform baseTrafo,
	TArray<FVector>& vertices, TArray<int32>& Triangles,
	TArray<FVector>& normals, TArray<FVector2D>& UV0,
	TArray<FColor>& vertexColors, TArray<FRuntimeMeshTangent>& tangents) {

	TArray<int32> newIndices;

	// FTransform trafo3 = UKismetMathLibrary::ConvertTransformToRelative(trafo1, trafo2);


#if 0 /* Verts for normal cube, pivot in the centre */
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(-CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2), vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(-CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2), vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2), vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2), vertices, newIndices);

	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(-CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2), vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(-CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2), vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2), vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2), vertices, newIndices);
#else

	/* Cube from Blender */
	FVector vertx0(1.000000, -1.000000, -1.000000);
	FVector vertx1(1.000000, -1.000000, 1.000000);
	FVector vertx2(-1.000000, -1.000000, 1.000000);
	FVector vertx3(-1.000000, -1.000000, -1.000000);
	FVector vertx4(1.000000, 1.000000, -0.999999);
	FVector vertx5(0.999999, 1.000000, 1.000001);
	FVector vertx6(-1.000000, 1.000000, 1.000000);
	FVector vertx7(-1.000000, 1.000000, -1.000000);


	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, baseTrafo, 30.0f * vertx0, vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, baseTrafo, 30.0f * vertx1, vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, baseTrafo, 30.0f * vertx2, vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, baseTrafo, 30.0f * vertx3, vertices, newIndices);

	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, baseTrafo, 30.0f * vertx4, vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, baseTrafo, 30.0f * vertx5, vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, baseTrafo, 30.0f * vertx6, vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, colors2Dim, baseTrafo, 30.0f * vertx7, vertices, newIndices);
	 /**/

	 // Curling stone from Blender
	 /*
	FVector vert0(0.000000, 0.000000, -0.932369);
	FVector vert1(-0.181896, 0.000000, -0.914454);
	FVector vert2(-0.356802, 0.000000, -0.861396);
	FVector vert3(-0.517996, 0.000000, -0.775236);
	FVector vert4(-0.659284, 0.000000, -0.659284);
	FVector vert5(-0.775236, 0.000000, -0.517996);
	FVector vert6(-0.861396, 0.000000, -0.356802);
	FVector vert7(-0.914454, 0.000000, -0.181896);
	FVector vert8(-0.932369, 0.000000, -0.000000);
	FVector vert9(-0.914454, 0.000000, 0.181896);
	FVector vert10(-0.861396, 0.000000, 0.356802);
	FVector vert11(-0.775236, 0.000000, 0.517996);
	FVector vert12(-0.659284, 0.000000, 0.659284);
	FVector vert13(-0.517996, 0.000000, 0.775236);
	FVector vert14(-0.356802, 0.000000, 0.861396);
	FVector vert15(-0.181896, 0.000000, 0.914454);
	FVector vert16(0.000000, 0.000000, 0.932369);
	FVector vert17(0.181896, 0.000000, 0.914453);
	FVector vert18(0.356802, 0.000000, 0.861396);
	FVector vert19(0.517997, 0.000000, 0.775236);
	FVector vert20(0.659285, 0.000000, 0.659284);
	FVector vert21(0.775237, 0.000000, 0.517996);
	FVector vert22(0.861397, 0.000000, 0.356801);
	FVector vert23(0.914454, 0.000000, 0.181895);
	FVector vert24(0.932369, 0.000000, -0.000001);
	FVector vert25(0.914453, 0.000000, -0.181897);
	FVector vert26(0.861396, 0.000000, -0.356803);
	FVector vert27(0.775236, 0.000000, -0.517997);
	FVector vert28(0.659283, 0.000000, -0.659285);
	FVector vert29(0.517995, 0.000000, -0.775237);
	FVector vert30(0.356801, 0.000000, -0.861397);
	FVector vert31(0.181895, 0.000000, -0.914454);
	FVector vert32(0.000000, 0.000000, -1.129705);
	FVector vert33(-0.220394, 0.000000, -1.107998);
	FVector vert34(-0.432319, 0.000000, -1.043711);
	FVector vert35(-0.627630, 0.000000, -0.939315);
	FVector vert36(-0.798822, 0.000000, -0.798822);
	FVector vert37(-0.939315, 0.000000, -0.627630);
	FVector vert38(-1.043711, 0.000000, -0.432319);
	FVector vert39(-1.107998, 0.000000, -0.220394);
	FVector vert40(-1.129705, 0.000000, -0.000000);
	FVector vert41(-1.107998, 0.000000, 0.220394);
	FVector vert42(-1.043711, 0.000000, 0.432319);
	FVector vert43(-0.939315, 0.000000, 0.627630);
	FVector vert44(-0.798822, 0.000000, 0.798822);
	FVector vert45(-0.627630, 0.000000, 0.939315);
	FVector vert46(-0.432319, 0.000000, 1.043711);
	FVector vert47(-0.220394, 0.000000, 1.107998);
	FVector vert48(0.000000, 0.000000, 1.129705);
	FVector vert49(0.220395, 0.000000, 1.107998);
	FVector vert50(0.432320, 0.000000, 1.043711);
	FVector vert51(0.627631, 0.000000, 0.939315);
	FVector vert52(0.798823, 0.000000, 0.798822);
	FVector vert53(0.939316, 0.000000, 0.627630);
	FVector vert54(1.043712, 0.000000, 0.432319);
	FVector vert55(1.107998, 0.000000, 0.220394);
	FVector vert56(1.129705, 0.000000, -0.000001);
	FVector vert57(1.107998, 0.000000, -0.220396);
	FVector vert58(1.043711, 0.000000, -0.432320);
	FVector vert59(0.939315, 0.000000, -0.627631);
	FVector vert60(0.798821, 0.000000, -0.798823);
	FVector vert61(0.627629, 0.000000, -0.939316);
	FVector vert62(0.432318, 0.000000, -1.043712);
	FVector vert63(0.220393, 0.000000, -1.107998);
	FVector vert64(0.000000, 0.349030, -2.815824);
	FVector vert65(-0.549340, 0.349030, -2.761718);
	FVector vert66(-1.077569, 0.349030, -2.601482);
	FVector vert67(-1.564388, 0.349030, -2.341272);
	FVector vert68(-1.991088, 0.349030, -1.991088);
	FVector vert69(-2.341272, 0.349030, -1.564388);
	FVector vert70(-2.601482, 0.349030, -1.077569);
	FVector vert71(-2.761719, 0.349030, -0.549340);
	FVector vert72(-2.815824, 0.349030, 0.000000);
	FVector vert73(-2.761719, 0.349030, 0.549340);
	FVector vert74(-2.601482, 0.349030, 1.077570);
	FVector vert75(-2.341272, 0.349030, 1.564389);
	FVector vert76(-1.991088, 0.349030, 1.991089);
	FVector vert77(-1.564388, 0.349030, 2.341273);
	FVector vert78(-1.077569, 0.349030, 2.601483);
	FVector vert79(-0.549339, 0.349030, 2.761720);
	FVector vert80(0.000001, 0.349030, 2.815825);
	FVector vert81(0.549341, 0.349030, 2.761719);
	FVector vert82(1.077571, 0.349030, 2.601483);
	FVector vert83(1.564390, 0.349030, 2.341272);
	FVector vert84(1.991090, 0.349030, 1.991088);
	FVector vert85(2.341274, 0.349030, 1.564387);
	FVector vert86(2.601484, 0.349030, 1.077568);
	FVector vert87(2.761720, 0.349030, 0.549338);
	FVector vert88(2.815825, 0.349030, -0.000002);
	FVector vert89(2.761719, 0.349030, -0.549342);
	FVector vert90(2.601482, 0.349030, -1.077572);
	FVector vert91(2.341271, 0.349030, -1.564391);
	FVector vert92(1.991086, 0.349030, -1.991090);
	FVector vert93(1.564385, 0.349030, -2.341274);
	FVector vert94(1.077566, 0.349030, -2.601484);
	FVector vert95(0.549336, 0.349030, -2.761719);
	FVector vert96(0.000000, 0.753171, -3.439678);
	FVector vert97(-0.671048, 0.753171, -3.373586);
	FVector vert98(-1.316308, 0.753171, -3.177848);
	FVector vert99(-1.910983, 0.753171, -2.859987);
	FVector vert100(-2.432220, 0.753171, -2.432220);
	FVector vert101(-2.859988, 0.753171, -1.910982);
	FVector vert102(-3.177849, 0.753171, -1.316307);
	FVector vert103(-3.373586, 0.753171, -0.671048);
	FVector vert104(-3.439679, 0.753171, 0.000000);
	FVector vert105(-3.373586, 0.753171, 0.671048);
	FVector vert106(-3.177849, 0.753171, 1.316308);
	FVector vert107(-2.859988, 0.753171, 1.910984);
	FVector vert108(-2.432220, 0.753171, 2.432221);
	FVector vert109(-1.910983, 0.753171, 2.859990);
	FVector vert110(-1.316308, 0.753171, 3.177850);
	FVector vert111(-0.671047, 0.753171, 3.373588);
	FVector vert112(0.000001, 0.753171, 3.439680);
	FVector vert113(0.671050, 0.753171, 3.373587);
	FVector vert114(1.316310, 0.753171, 3.177849);
	FVector vert115(1.910985, 0.753171, 2.859988);
	FVector vert116(2.432222, 0.753171, 2.432220);
	FVector vert117(2.859990, 0.753171, 1.910982);
	FVector vert118(3.177851, 0.753171, 1.316307);
	FVector vert119(3.373587, 0.753171, 0.671046);
	FVector vert120(3.439679, 0.753171, -0.000003);
	FVector vert121(3.373586, 0.753171, -0.671051);
	FVector vert122(3.177848, 0.753171, -1.316311);
	FVector vert123(2.859987, 0.753171, -1.910986);
	FVector vert124(2.432217, 0.753171, -2.432222);
	FVector vert125(1.910980, 0.753171, -2.859990);
	FVector vert126(1.316304, 0.753171, -3.177850);
	FVector vert127(0.671043, 0.753171, -3.373587);
	FVector vert128(0.000000, 0.753171, -3.439678);
	FVector vert129(-0.671048, 0.753171, -3.373586);
	FVector vert130(-1.316308, 0.753171, -3.177848);
	FVector vert131(-1.910983, 0.753171, -2.859987);
	FVector vert132(-2.432220, 0.753171, -2.432220);
	FVector vert133(-2.859988, 0.753171, -1.910982);
	FVector vert134(-3.177849, 0.753171, -1.316307);
	FVector vert135(-3.373586, 0.753171, -0.671048);
	FVector vert136(-3.439679, 0.753171, 0.000000);
	FVector vert137(-3.373586, 0.753171, 0.671048);
	FVector vert138(-3.177849, 0.753171, 1.316308);
	FVector vert139(-2.859988, 0.753171, 1.910984);
	FVector vert140(-2.432220, 0.753171, 2.432221);
	FVector vert141(-1.910983, 0.753171, 2.859990);
	FVector vert142(-1.316308, 0.753171, 3.177850);
	FVector vert143(-0.671047, 0.753171, 3.373588);
	FVector vert144(0.000001, 0.753171, 3.439680);
	FVector vert145(0.671050, 0.753171, 3.373587);
	FVector vert146(1.316310, 0.753171, 3.177849);
	FVector vert147(1.910985, 0.753171, 2.859988);
	FVector vert148(2.432222, 0.753171, 2.432220);
	FVector vert149(2.859990, 0.753171, 1.910982);
	FVector vert150(3.177851, 0.753171, 1.316307);
	FVector vert151(3.373587, 0.753171, 0.671046);
	FVector vert152(3.439679, 0.753171, -0.000003);
	FVector vert153(3.373586, 0.753171, -0.671051);
	FVector vert154(3.177848, 0.753171, -1.316311);
	FVector vert155(2.859987, 0.753171, -1.910986);
	FVector vert156(2.432217, 0.753171, -2.432222);
	FVector vert157(1.910980, 0.753171, -2.859990);
	FVector vert158(1.316304, 0.753171, -3.177850);
	FVector vert159(0.671043, 0.753171, -3.373587);
	FVector vert160(0.000000, 1.249162, -3.705974);
	FVector vert161(-0.723000, 1.249162, -3.634765);
	FVector vert162(-1.418215, 1.249162, -3.423873);
	FVector vert163(-2.058929, 1.249162, -3.081404);
	FVector vert164(-2.620520, 1.249162, -2.620519);
	FVector vert165(-3.081405, 1.249162, -2.058928);
	FVector vert166(-3.423874, 1.249162, -1.418214);
	FVector vert167(-3.634765, 1.249162, -0.722999);
	FVector vert168(-3.705975, 1.249162, 0.000001);
	FVector vert169(-3.634766, 1.249162, 0.723000);
	FVector vert170(-3.423874, 1.249162, 1.418215);
	FVector vert171(-3.081405, 1.249162, 2.058930);
	FVector vert172(-2.620520, 1.249162, 2.620521);
	FVector vert173(-2.058929, 1.249162, 3.081407);
	FVector vert174(-1.418215, 1.249162, 3.423876);
	FVector vert175(-0.722999, 1.249162, 3.634767);
	FVector vert176(0.000001, 1.249162, 3.705976);
	FVector vert177(0.723001, 1.249162, 3.634766);
	FVector vert178(1.418217, 1.249162, 3.423875);
	FVector vert179(2.058931, 1.249162, 3.081405);
	FVector vert180(2.620522, 1.249162, 2.620519);
	FVector vert181(3.081407, 1.249162, 2.058928);
	FVector vert182(3.423876, 1.249162, 1.418213);
	FVector vert183(3.634766, 1.249162, 0.722997);
	FVector vert184(3.705975, 1.249162, -0.000003);
	FVector vert185(3.634766, 1.249162, -0.723003);
	FVector vert186(3.423873, 1.249162, -1.418218);
	FVector vert187(3.081403, 1.249162, -2.058932);
	FVector vert188(2.620517, 1.249162, -2.620522);
	FVector vert189(2.058925, 1.249162, -3.081408);
	FVector vert190(1.418210, 1.249162, -3.423875);
	FVector vert191(0.722994, 1.249162, -3.634766);
	FVector vert192(0.000000, 1.910483, -3.830072);
	FVector vert193(-0.747210, 1.910483, -3.756478);
	FVector vert194(-1.465706, 1.910483, -3.538525);
	FVector vert195(-2.127874, 1.910483, -3.184588);
	FVector vert196(-2.708271, 1.910483, -2.708270);
	FVector vert197(-3.184589, 1.910483, -2.127874);
	FVector vert198(-3.538526, 1.910483, -1.465704);
	FVector vert199(-3.756479, 1.910483, -0.747209);
	FVector vert200(-3.830072, 1.910483, 0.000001);
	FVector vert201(-3.756479, 1.910483, 0.747211);
	FVector vert202(-3.538526, 1.910483, 1.465706);
	FVector vert203(-3.184589, 1.910483, 2.127875);
	FVector vert204(-2.708271, 1.910483, 2.708272);
	FVector vert205(-2.127874, 1.910483, 3.184591);
	FVector vert206(-1.465705, 1.910483, 3.538527);
	FVector vert207(-0.747209, 1.910483, 3.756481);
	FVector vert208(0.000001, 1.910483, 3.830074);
	FVector vert209(0.747212, 1.910483, 3.756480);
	FVector vert210(1.465707, 1.910483, 3.538527);
	FVector vert211(2.127877, 1.910483, 3.184589);
	FVector vert212(2.708273, 1.910483, 2.708270);
	FVector vert213(3.184591, 1.910483, 2.127873);
	FVector vert214(3.538528, 1.910483, 1.465704);
	FVector vert215(3.756480, 1.910483, 0.747208);
	FVector vert216(3.830074, 1.910483, -0.000003);
	FVector vert217(3.756480, 1.910483, -0.747213);
	FVector vert218(3.538525, 1.910483, -1.465708);
	FVector vert219(3.184587, 1.910483, -2.127878);
	FVector vert220(2.708267, 1.910483, -2.708273);
	FVector vert221(2.127871, 1.910483, -3.184592);
	FVector vert222(1.465701, 1.910483, -3.538527);
	FVector vert223(0.747205, 1.910483, -3.756480);
	FVector vert224(0.000000, 2.682025, -3.830072);
	FVector vert225(-0.747210, 2.682025, -3.756478);
	FVector vert226(-1.465706, 2.682025, -3.538525);
	FVector vert227(-2.127874, 2.682025, -3.184588);
	FVector vert228(-2.708271, 2.682025, -2.708270);
	FVector vert229(-3.184589, 2.682025, -2.127874);
	FVector vert230(-3.538526, 2.682025, -1.465704);
	FVector vert231(-3.756479, 2.682025, -0.747209);
	FVector vert232(-3.830072, 2.682025, 0.000001);
	FVector vert233(-3.756479, 2.682025, 0.747211);
	FVector vert234(-3.538526, 2.682025, 1.465706);
	FVector vert235(-3.184589, 2.682025, 2.127875);
	FVector vert236(-2.708271, 2.682025, 2.708272);
	FVector vert237(-2.127874, 2.682025, 3.184591);
	FVector vert238(-1.465705, 2.682025, 3.538527);
	FVector vert239(-0.747209, 2.682025, 3.756481);
	FVector vert240(0.000001, 2.682025, 3.830074);
	FVector vert241(0.747212, 2.682025, 3.756480);
	FVector vert242(1.465707, 2.682025, 3.538527);
	FVector vert243(2.127877, 2.682025, 3.184589);
	FVector vert244(2.708273, 2.682025, 2.708270);
	FVector vert245(3.184591, 2.682025, 2.127873);
	FVector vert246(3.538528, 2.682025, 1.465704);
	FVector vert247(3.756480, 2.682025, 0.747208);
	FVector vert248(3.830074, 2.682025, -0.000003);
	FVector vert249(3.756480, 2.682025, -0.747213);
	FVector vert250(3.538525, 2.682025, -1.465708);
	FVector vert251(3.184587, 2.682025, -2.127878);
	FVector vert252(2.708267, 2.682025, -2.708273);
	FVector vert253(2.127871, 2.682025, -3.184592);
	FVector vert254(1.465701, 2.682025, -3.538527);
	FVector vert255(0.747205, 2.682025, -3.756480);
	FVector vert256(0.000000, 3.453566, -3.520977);
	FVector vert257(-0.686909, 3.453566, -3.453323);
	FVector vert258(-1.347420, 3.453566, -3.252959);
	FVector vert259(-1.956150, 3.453566, -2.927586);
	FVector vert260(-2.489707, 3.453566, -2.489707);
	FVector vert261(-2.927586, 3.453566, -1.956150);
	FVector vert262(-3.252959, 3.453566, -1.347419);
	FVector vert263(-3.453323, 3.453566, -0.686908);
	FVector vert264(-3.520978, 3.453566, 0.000000);
	FVector vert265(-3.453324, 3.453566, 0.686909);
	FVector vert266(-3.252959, 3.453566, 1.347420);
	FVector vert267(-2.927586, 3.453566, 1.956151);
	FVector vert268(-2.489707, 3.453566, 2.489709);
	FVector vert269(-1.956150, 3.453566, 2.927588);
	FVector vert270(-1.347420, 3.453566, 3.252961);
	FVector vert271(-0.686908, 3.453566, 3.453325);
	FVector vert272(0.000001, 3.453566, 3.520979);
	FVector vert273(0.686910, 3.453566, 3.453325);
	FVector vert274(1.347422, 3.453566, 3.252960);
	FVector vert275(1.956153, 3.453566, 2.927586);
	FVector vert276(2.489709, 3.453566, 2.489707);
	FVector vert277(2.927588, 3.453566, 1.956150);
	FVector vert278(3.252962, 3.453566, 1.347419);
	FVector vert279(3.453325, 3.453566, 0.686906);
	FVector vert280(3.520979, 3.453566, -0.000003);
	FVector vert281(3.453324, 3.453566, -0.686912);
	FVector vert282(3.252959, 3.453566, -1.347423);
	FVector vert283(2.927585, 3.453566, -1.956154);
	FVector vert284(2.489704, 3.453566, -2.489710);
	FVector vert285(1.956147, 3.453566, -2.927588);
	FVector vert286(1.347415, 3.453566, -3.252961);
	FVector vert287(0.686904, 3.453566, -3.453324);
	FVector vert288(0.000000, 4.023036, -2.800339);
	FVector vert289(-0.546319, 4.023036, -2.746532);
	FVector vert290(-1.071644, 4.023036, -2.587177);
	FVector vert291(-1.555786, 4.023036, -2.328397);
	FVector vert292(-1.980139, 4.023036, -1.980139);
	FVector vert293(-2.328398, 4.023036, -1.555785);
	FVector vert294(-2.587177, 4.023036, -1.071643);
	FVector vert295(-2.746532, 4.023036, -0.546319);
	FVector vert296(-2.800340, 4.023036, 0.000000);
	FVector vert297(-2.746532, 4.023036, 0.546320);
	FVector vert298(-2.587177, 4.023036, 1.071644);
	FVector vert299(-2.328398, 4.023036, 1.555786);
	FVector vert300(-1.980139, 4.023036, 1.980140);
	FVector vert301(-1.555786, 4.023036, 2.328399);
	FVector vert302(-1.071643, 4.023036, 2.587178);
	FVector vert303(-0.546318, 4.023036, 2.746534);
	FVector vert304(0.000001, 4.023036, 2.800341);
	FVector vert305(0.546321, 4.023036, 2.746533);
	FVector vert306(1.071645, 4.023036, 2.587177);
	FVector vert307(1.555787, 4.023036, 2.328398);
	FVector vert308(1.980141, 4.023036, 1.980139);
	FVector vert309(2.328399, 4.023036, 1.555785);
	FVector vert310(2.587179, 4.023036, 1.071642);
	FVector vert311(2.746533, 4.023036, 0.546317);
	FVector vert312(2.800341, 4.023036, -0.000002);
	FVector vert313(2.746533, 4.023036, -0.546322);
	FVector vert314(2.587176, 4.023036, -1.071646);
	FVector vert315(2.328396, 4.023036, -1.555788);
	FVector vert316(1.980137, 4.023036, -1.980141);
	FVector vert317(1.555783, 4.023036, -2.328399);
	FVector vert318(1.071640, 4.023036, -2.587178);
	FVector vert319(0.546315, 4.023036, -2.746533);
	FVector vert320(0.000000, 4.427177, -1.765171);
	FVector vert321(-0.344368, 4.427177, -1.731254);
	FVector vert322(-0.675502, 4.427177, -1.630806);
	FVector vert323(-0.980677, 4.427177, -1.467686);
	FVector vert324(-1.248165, 4.427177, -1.248165);
	FVector vert325(-1.467687, 4.427177, -0.980677);
	FVector vert326(-1.630806, 4.427177, -0.675502);
	FVector vert327(-1.731254, 4.427177, -0.344368);
	FVector vert328(-1.765171, 4.427177, 0.000000);
	FVector vert329(-1.731254, 4.427177, 0.344368);
	FVector vert330(-1.630806, 4.427177, 0.675502);
	FVector vert331(-1.467687, 4.427177, 0.980677);
	FVector vert332(-1.248165, 4.427177, 1.248165);
	FVector vert333(-0.980677, 4.427177, 1.467687);
	FVector vert334(-0.675502, 4.427177, 1.630807);
	FVector vert335(-0.344367, 4.427177, 1.731255);
	FVector vert336(0.000001, 4.427177, 1.765172);
	FVector vert337(0.344369, 4.427177, 1.731255);
	FVector vert338(0.675503, 4.427177, 1.630806);
	FVector vert339(0.980678, 4.427177, 1.467686);
	FVector vert340(1.248166, 4.427177, 1.248164);
	FVector vert341(1.467687, 4.427177, 0.980676);
	FVector vert342(1.630807, 4.427177, 0.675501);
	FVector vert343(1.731255, 4.427177, 0.344367);
	FVector vert344(1.765172, 4.427177, -0.000001);
	FVector vert345(1.731255, 4.427177, -0.344370);
	FVector vert346(1.630805, 4.427177, -0.675503);
	FVector vert347(1.467686, 4.427177, -0.980678);
	FVector vert348(1.248163, 4.427177, -1.248166);
	FVector vert349(0.980675, 4.427177, -1.467688);
	FVector vert350(0.675500, 4.427177, -1.630807);
	FVector vert351(0.344365, 4.427177, -1.731255);
	FVector vert352(-0.414353, 4.527918, -0.711497);
	FVector vert353(-0.269624, 4.527918, -0.667594);
	FVector vert354(-0.136240, 4.527918, -0.596299);
	FVector vert355(-0.019329, 4.527918, -0.500352);
	FVector vert356(0.076618, 4.527918, -0.383441);
	FVector vert357(0.147913, 4.527918, -0.250058);
	FVector vert358(0.191816, 4.527918, -0.105329);
	FVector vert359(0.206640, 4.527918, 0.045184);
	FVector vert360(0.191816, 4.527918, 0.195697);
	FVector vert361(0.147913, 4.527918, 0.340426);
	FVector vert362(0.076619, 4.527918, 0.473810);
	FVector vert363(-0.019328, 4.527918, 0.590721);
	FVector vert364(-0.136239, 4.527918, 0.686667);
	FVector vert365(-0.269622, 4.527918, 0.757962);
	FVector vert366(-0.414351, 4.527918, 0.801865);
	FVector vert367(-0.564865, 4.527918, 0.816690);
	FVector vert368(-0.715378, 4.527918, 0.801866);
	FVector vert369(-0.860107, 4.527918, 0.757962);
	FVector vert370(-0.993490, 4.527918, 0.686668);
	FVector vert371(-1.110401, 4.527918, 0.590721);
	FVector vert372(-1.206348, 4.527918, 0.473810);
	FVector vert373(-1.277643, 4.527918, 0.340427);
	FVector vert374(-1.321546, 4.527918, 0.195698);
	FVector vert375(-1.336370, 4.527918, 0.045185);
	FVector vert376(-1.321546, 4.527918, -0.105329);
	FVector vert377(-1.277643, 4.527918, -0.250058);
	FVector vert378(-1.206348, 4.527918, -0.383441);
	FVector vert379(-1.110401, 4.527918, -0.500352);
	FVector vert380(-0.993490, 4.527918, -0.596298);
	FVector vert381(-0.860107, 4.527918, -0.667593);
	FVector vert382(-0.715378, 4.527918, -0.711496);
	FVector vert383(-0.564865, 4.527918, -0.726320);
	FVector vert384(-0.491102, 4.730234, -0.430589);
	FVector vert385(-0.404975, 4.730234, -0.404463);
	FVector vert386(-0.325600, 4.730234, -0.362036);
	FVector vert387(-0.256027, 4.730234, -0.304940);
	FVector vert388(-0.198930, 4.730234, -0.235367);
	FVector vert389(-0.156503, 4.730234, -0.155992);
	FVector vert390(-0.130377, 4.730234, -0.069866);
	FVector vert391(-0.121555, 4.730234, 0.019703);
	FVector vert392(-0.130377, 4.730234, 0.109272);
	FVector vert393(-0.156503, 4.730234, 0.195399);
	FVector vert394(-0.198930, 4.730234, 0.274773);
	FVector vert395(-0.256027, 4.730234, 0.344346);
	FVector vert396(-0.325599, 4.730234, 0.401443);
	FVector vert397(-0.404974, 4.730234, 0.443870);
	FVector vert398(-0.491101, 4.730234, 0.469996);
	FVector vert399(-0.580669, 4.730234, 0.478818);
	FVector vert400(-0.670238, 4.730234, 0.469996);
	FVector vert401(-0.756365, 4.730234, 0.443870);
	FVector vert402(-0.835740, 4.730234, 0.401443);
	FVector vert403(-0.905313, 4.730234, 0.344346);
	FVector vert404(-0.962409, 4.730234, 0.274774);
	FVector vert405(-1.004836, 4.730234, 0.195399);
	FVector vert406(-1.030962, 4.730234, 0.109272);
	FVector vert407(-1.039784, 4.730234, 0.019703);
	FVector vert408(-1.030962, 4.730234, -0.069865);
	FVector vert409(-1.004836, 4.730234, -0.155992);
	FVector vert410(-0.962409, 4.730234, -0.235367);
	FVector vert411(-0.905313, 4.730234, -0.304939);
	FVector vert412(-0.835740, 4.730234, -0.362036);
	FVector vert413(-0.756365, 4.730234, -0.404463);
	FVector vert414(-0.670238, 4.730234, -0.430589);
	FVector vert415(-0.580670, 4.730234, -0.439411);
	FVector vert416(-0.509210, 4.906161, -0.352390);
	FVector vert417(-0.442052, 4.906161, -0.332018);
	FVector vert418(-0.380158, 4.906161, -0.298935);
	FVector vert419(-0.325908, 4.906161, -0.254413);
	FVector vert420(-0.281386, 4.906161, -0.200163);
	FVector vert421(-0.248303, 4.906161, -0.138270);
	FVector vert422(-0.227930, 4.906161, -0.071112);
	FVector vert423(-0.221052, 4.906161, -0.001269);
	FVector vert424(-0.227930, 4.906161, 0.068573);
	FVector vert425(-0.248303, 4.906161, 0.135732);
	FVector vert426(-0.281385, 4.906161, 0.197625);
	FVector vert427(-0.325907, 4.906161, 0.251875);
	FVector vert428(-0.380157, 4.906161, 0.296397);
	FVector vert429(-0.442051, 4.906161, 0.329480);
	FVector vert430(-0.509209, 4.906161, 0.349852);
	FVector vert431(-0.579051, 4.906161, 0.356731);
	FVector vert432(-0.648894, 4.906161, 0.349852);
	FVector vert433(-0.716052, 4.906161, 0.329480);
	FVector vert434(-0.777946, 4.906161, 0.296397);
	FVector vert435(-0.832196, 4.906161, 0.251875);
	FVector vert436(-0.876718, 4.906161, 0.197625);
	FVector vert437(-0.909800, 4.906161, 0.135732);
	FVector vert438(-0.930173, 4.906161, 0.068573);
	FVector vert439(-0.937051, 4.906161, -0.001269);
	FVector vert440(-0.930173, 4.906161, -0.071111);
	FVector vert441(-0.909800, 4.906161, -0.138269);
	FVector vert442(-0.876718, 4.906161, -0.200163);
	FVector vert443(-0.832196, 4.906161, -0.254413);
	FVector vert444(-0.777946, 4.906161, -0.298935);
	FVector vert445(-0.716052, 4.906161, -0.332018);
	FVector vert446(-0.648894, 4.906161, -0.352390);
	FVector vert447(-0.579052, 4.906161, -0.359269);
	FVector vert448(-0.516505, 5.073292, -0.372995);
	FVector vert449(-0.449347, 5.073292, -0.352623);
	FVector vert450(-0.387453, 5.073292, -0.319540);
	FVector vert451(-0.333203, 5.073292, -0.275018);
	FVector vert452(-0.288681, 5.073292, -0.220768);
	FVector vert453(-0.255599, 5.073292, -0.158875);
	FVector vert454(-0.235226, 5.073292, -0.091717);
	FVector vert455(-0.228347, 5.073292, -0.021874);
	FVector vert456(-0.235226, 5.073292, 0.047968);
	FVector vert457(-0.255598, 5.073292, 0.115126);
	FVector vert458(-0.288681, 5.073292, 0.177020);
	FVector vert459(-0.333203, 5.073292, 0.231270);
	FVector vert460(-0.387453, 5.073292, 0.275792);
	FVector vert461(-0.449346, 5.073292, 0.308875);
	FVector vert462(-0.516505, 5.073292, 0.329247);
	FVector vert463(-0.586347, 5.073292, 0.336126);
	FVector vert464(-0.656189, 5.073292, 0.329247);
	FVector vert465(-0.723348, 5.073292, 0.308875);
	FVector vert466(-0.785241, 5.073292, 0.275792);
	FVector vert467(-0.839491, 5.073292, 0.231270);
	FVector vert468(-0.884013, 5.073292, 0.177020);
	FVector vert469(-0.917096, 5.073292, 0.115127);
	FVector vert470(-0.937468, 5.073292, 0.047968);
	FVector vert471(-0.944347, 5.073292, -0.021874);
	FVector vert472(-0.937468, 5.073292, -0.091716);
	FVector vert473(-0.917096, 5.073292, -0.158875);
	FVector vert474(-0.884013, 5.073292, -0.220768);
	FVector vert475(-0.839491, 5.073292, -0.275018);
	FVector vert476(-0.785241, 5.073292, -0.319540);
	FVector vert477(-0.723348, 5.073292, -0.352623);
	FVector vert478(-0.656190, 5.073292, -0.372995);
	FVector vert479(-0.586347, 5.073292, -0.379874);
	FVector vert480(-0.512123, 5.123354, -0.372995);
	FVector vert481(-0.445986, 5.111687, -0.352623);
	FVector vert482(-0.385034, 5.100934, -0.319540);
	FVector vert483(-0.331609, 5.091509, -0.275018);
	FVector vert484(-0.287764, 5.083774, -0.220768);
	FVector vert485(-0.255184, 5.078026, -0.158875);
	FVector vert486(-0.235121, 5.074487, -0.091717);
	FVector vert487(-0.228347, 5.073292, -0.021874);
	FVector vert488(-0.235121, 5.074487, 0.047968);
	FVector vert489(-0.255184, 5.078026, 0.115126);
	FVector vert490(-0.287763, 5.083774, 0.177020);
	FVector vert491(-0.331608, 5.091509, 0.231270);
	FVector vert492(-0.385033, 5.100934, 0.275792);
	FVector vert493(-0.445986, 5.111687, 0.308875);
	FVector vert494(-0.512123, 5.123354, 0.329247);
	FVector vert495(-0.580903, 5.135489, 0.336126);
	FVector vert496(-0.649683, 5.147623, 0.329247);
	FVector vert497(-0.715820, 5.159290, 0.308875);
	FVector vert498(-0.776772, 5.170043, 0.275792);
	FVector vert499(-0.830197, 5.179468, 0.231270);
	FVector vert500(-0.874042, 5.187203, 0.177020);
	FVector vert501(-0.906622, 5.192950, 0.115127);
	FVector vert502(-0.926684, 5.196490, 0.047968);
	FVector vert503(-0.933458, 5.197685, -0.021874);
	FVector vert504(-0.926684, 5.196490, -0.091716);
	FVector vert505(-0.906622, 5.192950, -0.158875);
	FVector vert506(-0.874042, 5.187203, -0.220768);
	FVector vert507(-0.830197, 5.179468, -0.275018);
	FVector vert508(-0.776772, 5.170043, -0.319540);
	FVector vert509(-0.715820, 5.159290, -0.352623);
	FVector vert510(-0.649683, 5.147623, -0.372995);
	FVector vert511(-0.580903, 5.135489, -0.379874);
	FVector vert512(-0.486635, 5.201050, -0.372995);
	FVector vert513(-0.426438, 5.171275, -0.352623);
	FVector vert514(-0.370961, 5.143834, -0.319540);
	FVector vert515(-0.322334, 5.119781, -0.275018);
	FVector vert516(-0.282427, 5.100042, -0.220768);
	FVector vert517(-0.252774, 5.085374, -0.158875);
	FVector vert518(-0.234513, 5.076342, -0.091717);
	FVector vert519(-0.228347, 5.073292, -0.021874);
	FVector vert520(-0.234513, 5.076342, 0.047968);
	FVector vert521(-0.252773, 5.085374, 0.115126);
	FVector vert522(-0.282427, 5.100042, 0.177020);
	FVector vert523(-0.322333, 5.119781, 0.231270);
	FVector vert524(-0.370960, 5.143833, 0.275792);
	FVector vert525(-0.426438, 5.171275, 0.308875);
	FVector vert526(-0.486635, 5.201050, 0.329247);
	FVector vert527(-0.549237, 5.232016, 0.336126);
	FVector vert528(-0.611840, 5.262981, 0.329247);
	FVector vert529(-0.672037, 5.292757, 0.308875);
	FVector vert530(-0.727515, 5.320198, 0.275792);
	FVector vert531(-0.776141, 5.344251, 0.231270);
	FVector vert532(-0.816048, 5.363990, 0.177020);
	FVector vert533(-0.845701, 5.378657, 0.115127);
	FVector vert534(-0.863962, 5.387690, 0.047968);
	FVector vert535(-0.870128, 5.390740, -0.021874);
	FVector vert536(-0.863962, 5.387690, -0.091716);
	FVector vert537(-0.845701, 5.378657, -0.158875);
	FVector vert538(-0.816048, 5.363990, -0.220768);
	FVector vert539(-0.776141, 5.344251, -0.275018);
	FVector vert540(-0.727515, 5.320198, -0.319540);
	FVector vert541(-0.672037, 5.292757, -0.352623);
	FVector vert542(-0.611840, 5.262981, -0.372995);
	FVector vert543(-0.549237, 5.232016, -0.379874);
	FVector vert544(-0.421621, 5.287021, -0.372995);
	FVector vert545(-0.376576, 5.237209, -0.352623);
	FVector vert546(-0.335063, 5.191302, -0.319540);
	FVector vert547(-0.298676, 5.151064, -0.275018);
	FVector vert548(-0.268814, 5.118042, -0.220768);
	FVector vert549(-0.246625, 5.093504, -0.158875);
	FVector vert550(-0.232961, 5.078394, -0.091717);
	FVector vert551(-0.228347, 5.073292, -0.021874);
	FVector vert552(-0.232961, 5.078394, 0.047968);
	FVector vert553(-0.246625, 5.093504, 0.115126);
	FVector vert554(-0.268814, 5.118042, 0.177020);
	FVector vert555(-0.298676, 5.151064, 0.231270);
	FVector vert556(-0.335063, 5.191301, 0.275792);
	FVector vert557(-0.376576, 5.237208, 0.308875);
	FVector vert558(-0.421620, 5.287021, 0.329247);
	FVector vert559(-0.468465, 5.338823, 0.336126);
	FVector vert560(-0.515310, 5.390626, 0.329247);
	FVector vert561(-0.560355, 5.440438, 0.308875);
	FVector vert562(-0.601868, 5.486345, 0.275792);
	FVector vert563(-0.638255, 5.526582, 0.231270);
	FVector vert564(-0.668116, 5.559605, 0.177020);
	FVector vert565(-0.690306, 5.584142, 0.115127);
	FVector vert566(-0.703970, 5.599252, 0.047968);
	FVector vert567(-0.708584, 5.604354, -0.021874);
	FVector vert568(-0.703970, 5.599252, -0.091716);
	FVector vert569(-0.690306, 5.584142, -0.158875);
	FVector vert570(-0.668116, 5.559605, -0.220768);
	FVector vert571(-0.638255, 5.526582, -0.275018);
	FVector vert572(-0.601868, 5.486345, -0.319540);
	FVector vert573(-0.560355, 5.440438, -0.352623);
	FVector vert574(-0.515310, 5.390626, -0.372995);
	FVector vert575(-0.468466, 5.338823, -0.379874);
	FVector vert576(-0.343989, 5.337227, -0.372995);
	FVector vert577(-0.317037, 5.275714, -0.352623);
	FVector vert578(-0.292199, 5.219023, -0.319540);
	FVector vert579(-0.270427, 5.169333, -0.275018);
	FVector vert580(-0.252560, 5.128554, -0.220768);
	FVector vert581(-0.239283, 5.098252, -0.158875);
	FVector vert582(-0.231107, 5.079592, -0.091717);
	FVector vert583(-0.228347, 5.073292, -0.021874);
	FVector vert584(-0.231107, 5.079592, 0.047968);
	FVector vert585(-0.239283, 5.098252, 0.115126);
	FVector vert586(-0.252560, 5.128554, 0.177020);
	FVector vert587(-0.270427, 5.169333, 0.231270);
	FVector vert588(-0.292199, 5.219022, 0.275792);
	FVector vert589(-0.317037, 5.275713, 0.308875);
	FVector vert590(-0.343989, 5.337226, 0.329247);
	FVector vert591(-0.372018, 5.401197, 0.336126);
	FVector vert592(-0.400046, 5.465169, 0.329247);
	FVector vert593(-0.426998, 5.526682, 0.308875);
	FVector vert594(-0.451837, 5.583373, 0.275792);
	FVector vert595(-0.473609, 5.633062, 0.231270);
	FVector vert596(-0.491476, 5.673842, 0.177020);
	FVector vert597(-0.504753, 5.704144, 0.115127);
	FVector vert598(-0.512928, 5.722804, 0.047968);
	FVector vert599(-0.515689, 5.729104, -0.021874);
	FVector vert600(-0.512928, 5.722804, -0.091716);
	FVector vert601(-0.504753, 5.704144, -0.158875);
	FVector vert602(-0.491476, 5.673842, -0.220768);
	FVector vert603(-0.473609, 5.633062, -0.275018);
	FVector vert604(-0.451837, 5.583373, -0.319540);
	FVector vert605(-0.426998, 5.526682, -0.352623);
	FVector vert606(-0.400047, 5.465169, -0.372995);
	FVector vert607(-0.372018, 5.401197, -0.379874);
	FVector vert608(-0.302051, 5.351864, -0.372995);
	FVector vert609(-0.284873, 5.286940, -0.352623);
	FVector vert610(-0.269042, 5.227105, -0.319540);
	FVector vert611(-0.255167, 5.174659, -0.275018);
	FVector vert612(-0.243779, 5.131618, -0.220768);
	FVector vert613(-0.235317, 5.099636, -0.158875);
	FVector vert614(-0.230106, 5.079941, -0.091717);
	FVector vert615(-0.228347, 5.073292, -0.021874);
	FVector vert616(-0.230106, 5.079941, 0.047968);
	FVector vert617(-0.235317, 5.099636, 0.115126);
	FVector vert618(-0.243779, 5.131618, 0.177020);
	FVector vert619(-0.255166, 5.174659, 0.231270);
	FVector vert620(-0.269042, 5.227104, 0.275792);
	FVector vert621(-0.284873, 5.286939, 0.308875);
	FVector vert622(-0.302050, 5.351863, 0.329247);
	FVector vert623(-0.319915, 5.419382, 0.336126);
	FVector vert624(-0.337778, 5.486902, 0.329247);
	FVector vert625(-0.354956, 5.551826, 0.308875);
	FVector vert626(-0.370787, 5.611661, 0.275792);
	FVector vert627(-0.384663, 5.664106, 0.231270);
	FVector vert628(-0.396050, 5.707148, 0.177020);
	FVector vert629(-0.404512, 5.739130, 0.115126);
	FVector vert630(-0.409723, 5.758824, 0.047968);
	FVector vert631(-0.411482, 5.765474, -0.021874);
	FVector vert632(-0.409723, 5.758824, -0.091716);
	FVector vert633(-0.404512, 5.739130, -0.158875);
	FVector vert634(-0.396050, 5.707148, -0.220768);
	FVector vert635(-0.384663, 5.664106, -0.275018);
	FVector vert636(-0.370787, 5.611661, -0.319540);
	FVector vert637(-0.354956, 5.551826, -0.352623);
	FVector vert638(-0.337778, 5.486902, -0.372995);
	FVector vert639(-0.319915, 5.419382, -0.379874);
	FVector vert640(-0.249594, 5.360665, -0.372995);
	FVector vert641(-0.244642, 5.293690, -0.352623);
	FVector vert642(-0.240079, 5.231964, -0.319540);
	FVector vert643(-0.236079, 5.177862, -0.275018);
	FVector vert644(-0.232795, 5.133461, -0.220768);
	FVector vert645(-0.230356, 5.100468, -0.158875);
	FVector vert646(-0.228854, 5.080152, -0.091717);
	FVector vert647(-0.228347, 5.073292, -0.021874);
	FVector vert648(-0.228854, 5.080152, 0.047968);
	FVector vert649(-0.230356, 5.100468, 0.115126);
	FVector vert650(-0.232795, 5.133461, 0.177020);
	FVector vert651(-0.236078, 5.177862, 0.231270);
	FVector vert652(-0.240079, 5.231964, 0.275792);
	FVector vert653(-0.244642, 5.293689, 0.308875);
	FVector vert654(-0.249594, 5.360664, 0.329247);
	FVector vert655(-0.254744, 5.430316, 0.336126);
	FVector vert656(-0.259893, 5.499969, 0.329247);
	FVector vert657(-0.264845, 5.566944, 0.308875);
	FVector vert658(-0.269409, 5.628670, 0.275792);
	FVector vert659(-0.273409, 5.682771, 0.231270);
	FVector vert660(-0.276692, 5.727173, 0.177020);
	FVector vert661(-0.279131, 5.760165, 0.115126);
	FVector vert662(-0.280634, 5.780482, 0.047968);
	FVector vert663(-0.281141, 5.787342, -0.021874);
	FVector vert664(-0.280634, 5.780482, -0.091716);
	FVector vert665(-0.279131, 5.760165, -0.158875);
	FVector vert666(-0.276692, 5.727173, -0.220768);
	FVector vert667(-0.273409, 5.682771, -0.275018);
	FVector vert668(-0.269409, 5.628670, -0.319540);
	FVector vert669(-0.264845, 5.566945, -0.352623);
	FVector vert670(-0.259893, 5.499969, -0.372995);
	FVector vert671(-0.254744, 5.430316, -0.379874);
	FVector vert672(0.353404, 5.363061, -0.378674);
	FVector vert673(0.358276, 5.297167, -0.358631);
	FVector vert674(0.362766, 5.236438, -0.326082);
	FVector vert675(0.366701, 5.183208, -0.282279);
	FVector vert676(0.369931, 5.139525, -0.228904);
	FVector vert677(0.372331, 5.107064, -0.168010);
	FVector vert678(0.373809, 5.087075, -0.101935);
	FVector vert679(0.374308, 5.080327, -0.033220);
	FVector vert680(0.373809, 5.087075, 0.035495);
	FVector vert681(0.372331, 5.107064, 0.101569);
	FVector vert682(0.369931, 5.139524, 0.162464);
	FVector vert683(0.366702, 5.183208, 0.215838);
	FVector vert684(0.362766, 5.236437, 0.259642);
	FVector vert685(0.358276, 5.297166, 0.292190);
	FVector vert686(0.353404, 5.363061, 0.312234);
	FVector vert687(0.348337, 5.431589, 0.319002);
	FVector vert688(0.343271, 5.500117, 0.312234);
	FVector vert689(0.338399, 5.566011, 0.292190);
	FVector vert690(0.333909, 5.626741, 0.259642);
	FVector vert691(0.329973, 5.679970, 0.215838);
	FVector vert692(0.326744, 5.723654, 0.162464);
	FVector vert693(0.324343, 5.756114, 0.101569);
	FVector vert694(0.322865, 5.776103, 0.035495);
	FVector vert695(0.322366, 5.782852, -0.033220);
	FVector vert696(0.322865, 5.776103, -0.101935);
	FVector vert697(0.324343, 5.756114, -0.168010);
	FVector vert698(0.326744, 5.723654, -0.228904);
	FVector vert699(0.329973, 5.679970, -0.282278);
	FVector vert700(0.333909, 5.626741, -0.326082);
	FVector vert701(0.338399, 5.566012, -0.358631);
	FVector vert702(0.343271, 5.500117, -0.378674);
	FVector vert703(0.348337, 5.431589, -0.385442);
	FVector vert704(0.720742, 5.321203, -0.336288);
	FVector vert705(0.724800, 5.266311, -0.319591);
	FVector vert706(0.728541, 5.215721, -0.292477);
	FVector vert707(0.731819, 5.171378, -0.255987);
	FVector vert708(0.734510, 5.134988, -0.211524);
	FVector vert709(0.736509, 5.107946, -0.160796);
	FVector vert710(0.737740, 5.091295, -0.105753);
	FVector vert711(0.738156, 5.085673, -0.048511);
	FVector vert712(0.737740, 5.091295, 0.008732);
	FVector vert713(0.736509, 5.107946, 0.063774);
	FVector vert714(0.734510, 5.134987, 0.114502);
	FVector vert715(0.731819, 5.171378, 0.158965);
	FVector vert716(0.728540, 5.215720, 0.195455);
	FVector vert717(0.724800, 5.266310, 0.222570);
	FVector vert718(0.720742, 5.321203, 0.239267);
	FVector vert719(0.716521, 5.378289, 0.244905);
	FVector vert720(0.712301, 5.435376, 0.239267);
	FVector vert721(0.708242, 5.490269, 0.222570);
	FVector vert722(0.704502, 5.540859, 0.195455);
	FVector vert723(0.701223, 5.585201, 0.158965);
	FVector vert724(0.698533, 5.621592, 0.114502);
	FVector vert725(0.696533, 5.648633, 0.063775);
	FVector vert726(0.695302, 5.665284, 0.008732);
	FVector vert727(0.694886, 5.670906, -0.048511);
	FVector vert728(0.695302, 5.665284, -0.105753);
	FVector vert729(0.696533, 5.648633, -0.160796);
	FVector vert730(0.698533, 5.621592, -0.211523);
	FVector vert731(0.701223, 5.585201, -0.255986);
	FVector vert732(0.704502, 5.540859, -0.292476);
	FVector vert733(0.708242, 5.490269, -0.319591);
	FVector vert734(0.712301, 5.435376, -0.336288);
	FVector vert735(0.716521, 5.378289, -0.341926);
	FVector vert736(1.139815, 5.288565, -0.338265);
	FVector vert737(1.143654, 5.236647, -0.322473);
	FVector vert738(1.147192, 5.188798, -0.296828);
	FVector vert739(1.150292, 5.146859, -0.262315);
	FVector vert740(1.152837, 5.112440, -0.220262);
	FVector vert741(1.154728, 5.086864, -0.172283);
	FVector vert742(1.155893, 5.071115, -0.120223);
	FVector vert743(1.156286, 5.065798, -0.066082);
	FVector vert744(1.155893, 5.071115, -0.011942);
	FVector vert745(1.154728, 5.086864, 0.040118);
	FVector vert746(1.152837, 5.112440, 0.088097);
	FVector vert747(1.150293, 5.146859, 0.130151);
	FVector vert748(1.147192, 5.188797, 0.164663);
	FVector vert749(1.143654, 5.236646, 0.190308);
	FVector vert750(1.139816, 5.288564, 0.206101);
	FVector vert751(1.135823, 5.342557, 0.211433);
	FVector vert752(1.131832, 5.396551, 0.206101);
	FVector vert753(1.127993, 5.448469, 0.190309);
	FVector vert754(1.124455, 5.496318, 0.164663);
	FVector vert755(1.121354, 5.538256, 0.130151);
	FVector vert756(1.118810, 5.572676, 0.088097);
	FVector vert757(1.116919, 5.598251, 0.040118);
	FVector vert758(1.115754, 5.613999, -0.011942);
	FVector vert759(1.115361, 5.619317, -0.066082);
	FVector vert760(1.115754, 5.613999, -0.120223);
	FVector vert761(1.116919, 5.598251, -0.172283);
	FVector vert762(1.118810, 5.572676, -0.220262);
	FVector vert763(1.121354, 5.538256, -0.262315);
	FVector vert764(1.124455, 5.496318, -0.296828);
	FVector vert765(1.127993, 5.448469, -0.322473);
	FVector vert766(1.131832, 5.396551, -0.338265);
	FVector vert767(1.135823, 5.342557, -0.343598);
	FVector vert768(1.361734, 5.261805, -0.331777);
	FVector vert769(1.365351, 5.212895, -0.316900);
	FVector vert770(1.368683, 5.167820, -0.292742);
	FVector vert771(1.371604, 5.128311, -0.260229);
	FVector vert772(1.374002, 5.095887, -0.220613);
	FVector vert773(1.375783, 5.071794, -0.175414);
	FVector vert774(1.376880, 5.056957, -0.126371);
	FVector vert775(1.377250, 5.051948, -0.075368);
	FVector vert776(1.376880, 5.056957, -0.024365);
	FVector vert777(1.375783, 5.071794, 0.024678);
	FVector vert778(1.374002, 5.095887, 0.069876);
	FVector vert779(1.371604, 5.128311, 0.109492);
	FVector vert780(1.368683, 5.167819, 0.142005);
	FVector vert781(1.365350, 5.212895, 0.166164);
	FVector vert782(1.361735, 5.261804, 0.181041);
	FVector vert783(1.357974, 5.312668, 0.186064);
	FVector vert784(1.354213, 5.363533, 0.181041);
	FVector vert785(1.350597, 5.412442, 0.166164);
	FVector vert786(1.347264, 5.457518, 0.142005);
	FVector vert787(1.344343, 5.497026, 0.109492);
	FVector vert788(1.341946, 5.529451, 0.069876);
	FVector vert789(1.340165, 5.553544, 0.024678);
	FVector vert790(1.339067, 5.568379, -0.024365);
	FVector vert791(1.338697, 5.573390, -0.075368);
	FVector vert792(1.339067, 5.568379, -0.126371);
	FVector vert793(1.340165, 5.553544, -0.175414);
	FVector vert794(1.341946, 5.529451, -0.220612);
	FVector vert795(1.344343, 5.497026, -0.260229);
	FVector vert796(1.347264, 5.457518, -0.292741);
	FVector vert797(1.350597, 5.412442, -0.316900);
	FVector vert798(1.354213, 5.363533, -0.331777);
	FVector vert799(1.357974, 5.312668, -0.336801);
	FVector vert800(1.462494, 5.239971, -0.318974);
	FVector vert801(1.465870, 5.194303, -0.305083);
	FVector vert802(1.468982, 5.152215, -0.282526);
	FVector vert803(1.471709, 5.115325, -0.252168);
	FVector vert804(1.473948, 5.085050, -0.215177);
	FVector vert805(1.475611, 5.062553, -0.172975);
	FVector vert806(1.476635, 5.048700, -0.127182);
	FVector vert807(1.476981, 5.044023, -0.079560);
	FVector vert808(1.476635, 5.048700, -0.031937);
	FVector vert809(1.475611, 5.062553, 0.013856);
	FVector vert810(1.473948, 5.085049, 0.056058);
	FVector vert811(1.471709, 5.115325, 0.093049);
	FVector vert812(1.468982, 5.152215, 0.123407);
	FVector vert813(1.465870, 5.194303, 0.145965);
	FVector vert814(1.462494, 5.239970, 0.159856);
	FVector vert815(1.458982, 5.287463, 0.164546);
	FVector vert816(1.455471, 5.334957, 0.159856);
	FVector vert817(1.452094, 5.380624, 0.145965);
	FVector vert818(1.448982, 5.422713, 0.123407);
	FVector vert819(1.446255, 5.459602, 0.093049);
	FVector vert820(1.444017, 5.489878, 0.056058);
	FVector vert821(1.442353, 5.512373, 0.013856);
	FVector vert822(1.441329, 5.526226, -0.031937);
	FVector vert823(1.440983, 5.530904, -0.079559);
	FVector vert824(1.441329, 5.526226, -0.127182);
	FVector vert825(1.442353, 5.512373, -0.172974);
	FVector vert826(1.444017, 5.489878, -0.215177);
	FVector vert827(1.446255, 5.459602, -0.252168);
	FVector vert828(1.448982, 5.422713, -0.282525);
	FVector vert829(1.452094, 5.380624, -0.305083);
	FVector vert830(1.455471, 5.334957, -0.318974);
	FVector vert831(1.458982, 5.287463, -0.323665);
	FVector vert832(1.566203, 5.209683, -0.315211);
	FVector vert833(1.569465, 5.165561, -0.301790);
	FVector vert834(1.572471, 5.124898, -0.279995);
	FVector vert835(1.575107, 5.089256, -0.250665);
	FVector vert836(1.577270, 5.060005, -0.214926);
	FVector vert837(1.578876, 5.038270, -0.174151);
	FVector vert838(1.579866, 5.024886, -0.129908);
	FVector vert839(1.580200, 5.020367, -0.083897);
	FVector vert840(1.579866, 5.024886, -0.037886);
	FVector vert841(1.578877, 5.038270, 0.006357);
	FVector vert842(1.577270, 5.060005, 0.047131);
	FVector vert843(1.575107, 5.089256, 0.082871);
	FVector vert844(1.572471, 5.124897, 0.112201);
	FVector vert845(1.569465, 5.165561, 0.133995);
	FVector vert846(1.566203, 5.209683, 0.147416);
	FVector vert847(1.562810, 5.255569, 0.151948);
	FVector vert848(1.559418, 5.301455, 0.147416);
	FVector vert849(1.556155, 5.345578, 0.133996);
	FVector vert850(1.553149, 5.386242, 0.112201);
	FVector vert851(1.550514, 5.421883, 0.082871);
	FVector vert852(1.548351, 5.451134, 0.047131);
	FVector vert853(1.546744, 5.472869, 0.006357);
	FVector vert854(1.545754, 5.486253, -0.037886);
	FVector vert855(1.545420, 5.490773, -0.083897);
	FVector vert856(1.545754, 5.486253, -0.129908);
	FVector vert857(1.546744, 5.472869, -0.174151);
	FVector vert858(1.548351, 5.451134, -0.214926);
	FVector vert859(1.550514, 5.421883, -0.250665);
	FVector vert860(1.553149, 5.386242, -0.279995);
	FVector vert861(1.556155, 5.345578, -0.301790);
	FVector vert862(1.559418, 5.301455, -0.315211);
	FVector vert863(1.562810, 5.255569, -0.319742);
	FVector vert864(1.642399, 5.197730, -0.315197);
	FVector vert865(1.645616, 5.154219, -0.301962);
	FVector vert866(1.648580, 5.114120, -0.280470);
	FVector vert867(1.651179, 5.078972, -0.251547);
	FVector vert868(1.653312, 5.050127, -0.216303);
	FVector vert869(1.654896, 5.028693, -0.176094);
	FVector vert870(1.655872, 5.015494, -0.132464);
	FVector vert871(1.656202, 5.011038, -0.087091);
	FVector vert872(1.655872, 5.015494, -0.041718);
	FVector vert873(1.654897, 5.028693, 0.001911);
	FVector vert874(1.653312, 5.050127, 0.042121);
	FVector vert875(1.651179, 5.078972, 0.077364);
	FVector vert876(1.648580, 5.114119, 0.106288);
	FVector vert877(1.645616, 5.154219, 0.127780);
	FVector vert878(1.642399, 5.197729, 0.141015);
	FVector vert879(1.639053, 5.242980, 0.145484);
	FVector vert880(1.635707, 5.288229, 0.141015);
	FVector vert881(1.632491, 5.331740, 0.127780);
	FVector vert882(1.629526, 5.371840, 0.106288);
	FVector vert883(1.626927, 5.406987, 0.077364);
	FVector vert884(1.624795, 5.435833, 0.042121);
	FVector vert885(1.623210, 5.457266, 0.001912);
	FVector vert886(1.622234, 5.470465, -0.041718);
	FVector vert887(1.621904, 5.474922, -0.087091);
	FVector vert888(1.622234, 5.470465, -0.132464);
	FVector vert889(1.623210, 5.457266, -0.176094);
	FVector vert890(1.624795, 5.435833, -0.216303);
	FVector vert891(1.626927, 5.406987, -0.251546);
	FVector vert892(1.629526, 5.371840, -0.280470);
	FVector vert893(1.632491, 5.331740, -0.301962);
	FVector vert894(1.635707, 5.288229, -0.315197);
	FVector vert895(1.639053, 5.242980, -0.319666);
	FVector vert896(1.695494, 5.197309, -0.288408);
	FVector vert897(1.698302, 5.159338, -0.276858);
	FVector vert898(1.700889, 5.124343, -0.258102);
	FVector vert899(1.703156, 5.093670, -0.232860);
	FVector vert900(1.705017, 5.068497, -0.202103);
	FVector vert901(1.706401, 5.049791, -0.167013);
	FVector vert902(1.707252, 5.038273, -0.128937);
	FVector vert903(1.707540, 5.034384, -0.089340);
	FVector vert904(1.707252, 5.038273, -0.049743);
	FVector vert905(1.706401, 5.049791, -0.011668);
	FVector vert906(1.705017, 5.068497, 0.023422);
	FVector vert907(1.703156, 5.093670, 0.054179);
	FVector vert908(1.700889, 5.124342, 0.079421);
	FVector vert909(1.698301, 5.159338, 0.098177);
	FVector vert910(1.695494, 5.197309, 0.109727);
	FVector vert911(1.692574, 5.236798, 0.113627);
	FVector vert912(1.689654, 5.276288, 0.109727);
	FVector vert913(1.686847, 5.314259, 0.098177);
	FVector vert914(1.684260, 5.349255, 0.079421);
	FVector vert915(1.681992, 5.379927, 0.054179);
	FVector vert916(1.680131, 5.405101, 0.023422);
	FVector vert917(1.678748, 5.423806, -0.011668);
	FVector vert918(1.677896, 5.435324, -0.049743);
	FVector vert919(1.677608, 5.439214, -0.089340);
	FVector vert920(1.677896, 5.435324, -0.128937);
	FVector vert921(1.678748, 5.423806, -0.167012);
	FVector vert922(1.680131, 5.405101, -0.202103);
	FVector vert923(1.681992, 5.379927, -0.232860);
	FVector vert924(1.684260, 5.349255, -0.258101);
	FVector vert925(1.686847, 5.314260, -0.276858);
	FVector vert926(1.689654, 5.276288, -0.288408);
	FVector vert927(1.692574, 5.236798, -0.292307);
	FVector vert928(1.723430, 5.204727, -0.245006);
	FVector vert929(1.725609, 5.175263, -0.236044);
	FVector vert930(1.727616, 5.148109, -0.221490);
	FVector vert931(1.729376, 5.124309, -0.201904);
	FVector vert932(1.730820, 5.104776, -0.178039);
	FVector vert933(1.731893, 5.090262, -0.150811);
	FVector vert934(1.732554, 5.081324, -0.121267);
	FVector vert935(1.732777, 5.078307, -0.090542);
	FVector vert936(1.732554, 5.081324, -0.059817);
	FVector vert937(1.731893, 5.090262, -0.030273);
	FVector vert938(1.730820, 5.104776, -0.003045);
	FVector vert939(1.729376, 5.124309, 0.020821);
	FVector vert940(1.727616, 5.148109, 0.040406);
	FVector vert941(1.725608, 5.175263, 0.054960);
	FVector vert942(1.723430, 5.204726, 0.063922);
	FVector vert943(1.721164, 5.235368, 0.066948);
	FVector vert944(1.718899, 5.266009, 0.063922);
	FVector vert945(1.716721, 5.295473, 0.054960);
	FVector vert946(1.714713, 5.322628, 0.040407);
	FVector vert947(1.712953, 5.346427, 0.020821);
	FVector vert948(1.711509, 5.365960, -0.003045);
	FVector vert949(1.710436, 5.380474, -0.030273);
	FVector vert950(1.709775, 5.389411, -0.059817);
	FVector vert951(1.709552, 5.392429, -0.090542);
	FVector vert952(1.709775, 5.389411, -0.121267);
	FVector vert953(1.710436, 5.380474, -0.150811);
	FVector vert954(1.711509, 5.365960, -0.178039);
	FVector vert955(1.712953, 5.346427, -0.201904);
	FVector vert956(1.714713, 5.322628, -0.221490);
	FVector vert957(1.716721, 5.295473, -0.236044);
	FVector vert958(1.718899, 5.266009, -0.245006);
	FVector vert959(1.721164, 5.235368, -0.248032);
	FVector vert960(1.736527, 5.220933, -0.163910);
	FVector vert961(1.737553, 5.207053, -0.159688);
	FVector vert962(1.738499, 5.194261, -0.152832);
	FVector vert963(1.739328, 5.183049, -0.143605);
	FVector vert964(1.740008, 5.173847, -0.132362);
	FVector vert965(1.740514, 5.167009, -0.119535);
	FVector vert966(1.740825, 5.162798, -0.105617);
	FVector vert967(1.740930, 5.161377, -0.091143);
	FVector vert968(1.740825, 5.162798, -0.076668);
	FVector vert969(1.740514, 5.167009, -0.062750);
	FVector vert970(1.740008, 5.173847, -0.049923);
	FVector vert971(1.739328, 5.183049, -0.038680);
	FVector vert972(1.738499, 5.194261, -0.029453);
	FVector vert973(1.737553, 5.207053, -0.022597);
	FVector vert974(1.736527, 5.220933, -0.018375);
	FVector vert975(1.735460, 5.235368, -0.016949);
	FVector vert976(1.734392, 5.249803, -0.018375);
	FVector vert977(1.733366, 5.263683, -0.022597);
	FVector vert978(1.732420, 5.276475, -0.029453);
	FVector vert979(1.731591, 5.287688, -0.038680);
	FVector vert980(1.730911, 5.296890, -0.049923);
	FVector vert981(1.730405, 5.303727, -0.062750);
	FVector vert982(1.730094, 5.307938, -0.076668);
	FVector vert983(1.729989, 5.309359, -0.091142);
	FVector vert984(1.730094, 5.307938, -0.105617);
	FVector vert985(1.730405, 5.303727, -0.119535);
	FVector vert986(1.730911, 5.296890, -0.132362);
	FVector vert987(1.731591, 5.287688, -0.143605);
	FVector vert988(1.732420, 5.276475, -0.152832);
	FVector vert989(1.733366, 5.263683, -0.159688);
	FVector vert990(1.734392, 5.249803, -0.163910);
	FVector vert991(1.735460, 5.235368, -0.165336);
	 */
/*
	TArray<FVector> vertArrayFromBlender = { vert0, vert1, vert2, vert3, vert4, vert5, vert6, vert7, vert8, vert9, vert10,
		vert11, vert12, vert13, vert14, vert15, vert16, vert17, vert18, vert19, vert20,
		vert21, vert22, vert23, vert24, vert25, vert26, vert27, vert28, vert29, vert30,
		vert31, vert32, vert33, vert34, vert35, vert36, vert37, vert38, vert39, vert40,
		vert41, vert42, vert43, vert44, vert45, vert46, vert47, vert48, vert49, vert50,
		vert51, vert52, vert53, vert54, vert55, vert56, vert57, vert58, vert59, vert60,
		vert61, vert62, vert63, vert64, vert65, vert66, vert67, vert68, vert69, vert70,
		vert71, vert72, vert73, vert74, vert75, vert76, vert77, vert78, vert79, vert80,
		vert81, vert82, vert83, vert84, vert85, vert86, vert87, vert88, vert89, vert90,
		vert91, vert92, vert93, vert94, vert95, vert96, vert97, vert98, vert99, vert100,
		vert101, vert102, vert103, vert104, vert105, vert106, vert107, vert108, vert109, vert110,
		vert111, vert112, vert113, vert114, vert115, vert116, vert117, vert118, vert119, vert120,
		vert121, vert122, vert123, vert124, vert125, vert126, vert127, vert128, vert129, vert130,
		vert131, vert132, vert133, vert134, vert135, vert136, vert137, vert138, vert139, vert140,
		vert141, vert142, vert143, vert144, vert145, vert146, vert147, vert148, vert149, vert150,
		vert151, vert152, vert153, vert154, vert155, vert156, vert157, vert158, vert159, vert160,
		vert161, vert162, vert163, vert164, vert165, vert166, vert167, vert168, vert169, vert170,
		vert171, vert172, vert173, vert174, vert175, vert176, vert177, vert178, vert179, vert180,
		vert181, vert182, vert183, vert184, vert185, vert186, vert187, vert188, vert189, vert190,
		vert191, vert192, vert193, vert194, vert195, vert196, vert197, vert198, vert199, vert200,
		vert201, vert202, vert203, vert204, vert205, vert206, vert207, vert208, vert209, vert210,
		vert211, vert212, vert213, vert214, vert215, vert216, vert217, vert218, vert219, vert220,
		vert221, vert222, vert223, vert224, vert225, vert226, vert227, vert228, vert229, vert230,
		vert231, vert232, vert233, vert234, vert235, vert236, vert237, vert238, vert239, vert240,
		vert241, vert242, vert243, vert244, vert245, vert246, vert247, vert248, vert249, vert250,
		vert251, vert252, vert253, vert254, vert255, vert256, vert257, vert258, vert259, vert260,
		vert261, vert262, vert263, vert264, vert265, vert266, vert267, vert268, vert269, vert270,
		vert271, vert272, vert273, vert274, vert275, vert276, vert277, vert278, vert279, vert280,
		vert281, vert282, vert283, vert284, vert285, vert286, vert287, vert288, vert289, vert290,
		vert291, vert292, vert293, vert294, vert295, vert296, vert297, vert298, vert299, vert300,
		vert301, vert302, vert303, vert304, vert305, vert306, vert307, vert308, vert309, vert310,
		vert311, vert312, vert313, vert314, vert315, vert316, vert317, vert318, vert319, vert320,
		vert321, vert322, vert323, vert324, vert325, vert326, vert327, vert328, vert329, vert330,
		vert331, vert332, vert333, vert334, vert335, vert336, vert337, vert338, vert339, vert340,
		vert341, vert342, vert343, vert344, vert345, vert346, vert347, vert348, vert349, vert350,
		vert351, vert352, vert353, vert354, vert355, vert356, vert357, vert358, vert359, vert360,
		vert361, vert362, vert363, vert364, vert365, vert366, vert367, vert368, vert369, vert370,
		vert371, vert372, vert373, vert374, vert375, vert376, vert377, vert378, vert379, vert380,
		vert381, vert382, vert383, vert384, vert385, vert386, vert387, vert388, vert389, vert390,
		vert391, vert392, vert393, vert394, vert395, vert396, vert397, vert398, vert399, vert400,
		vert401, vert402, vert403, vert404, vert405, vert406, vert407, vert408, vert409, vert410,
		vert411, vert412, vert413, vert414, vert415, vert416, vert417, vert418, vert419, vert420,
		vert421, vert422, vert423, vert424, vert425, vert426, vert427, vert428, vert429, vert430,
		vert431, vert432, vert433, vert434, vert435, vert436, vert437, vert438, vert439, vert440,
		vert441, vert442, vert443, vert444, vert445, vert446, vert447, vert448, vert449, vert450,
		vert451, vert452, vert453, vert454, vert455, vert456, vert457, vert458, vert459, vert460,
		vert461, vert462, vert463, vert464, vert465, vert466, vert467, vert468, vert469, vert470,
		vert471, vert472, vert473, vert474, vert475, vert476, vert477, vert478, vert479, vert480,
		vert481, vert482, vert483, vert484, vert485, vert486, vert487, vert488, vert489, vert490,
		vert491, vert492, vert493, vert494, vert495, vert496, vert497, vert498, vert499, vert500,
		vert501, vert502, vert503, vert504, vert505, vert506, vert507, vert508, vert509, vert510,
		vert511, vert512, vert513, vert514, vert515, vert516, vert517, vert518, vert519, vert520,
		vert521, vert522, vert523, vert524, vert525, vert526, vert527, vert528, vert529, vert530,
		vert531, vert532, vert533, vert534, vert535, vert536, vert537, vert538, vert539, vert540,
		vert541, vert542, vert543, vert544, vert545, vert546, vert547, vert548, vert549, vert550,
		vert551, vert552, vert553, vert554, vert555, vert556, vert557, vert558, vert559, vert560,
		vert561, vert562, vert563, vert564, vert565, vert566, vert567, vert568, vert569, vert570,
		vert571, vert572, vert573, vert574, vert575, vert576, vert577, vert578, vert579, vert580,
		vert581, vert582, vert583, vert584, vert585, vert586, vert587, vert588, vert589, vert590,
		vert591, vert592, vert593, vert594, vert595, vert596, vert597, vert598, vert599, vert600,
		vert601, vert602, vert603, vert604, vert605, vert606, vert607, vert608, vert609, vert610,
		vert611, vert612, vert613, vert614, vert615, vert616, vert617, vert618, vert619, vert620,
		vert621, vert622, vert623, vert624, vert625, vert626, vert627, vert628, vert629, vert630,
		vert631, vert632, vert633, vert634, vert635, vert636, vert637, vert638, vert639, vert640,
		vert641, vert642, vert643, vert644, vert645, vert646, vert647, vert648, vert649, vert650,
		vert651, vert652, vert653, vert654, vert655, vert656, vert657, vert658, vert659, vert660,
		vert661, vert662, vert663, vert664, vert665, vert666, vert667, vert668, vert669, vert670,
		vert671, vert672, vert673, vert674, vert675, vert676, vert677, vert678, vert679, vert680,
		vert681, vert682, vert683, vert684, vert685, vert686, vert687, vert688, vert689, vert690,
		vert691, vert692, vert693, vert694, vert695, vert696, vert697, vert698, vert699, vert700,
		vert701, vert702, vert703, vert704, vert705, vert706, vert707, vert708, vert709, vert710,
		vert711, vert712, vert713, vert714, vert715, vert716, vert717, vert718, vert719, vert720,
		vert721, vert722, vert723, vert724, vert725, vert726, vert727, vert728, vert729, vert730,
		vert731, vert732, vert733, vert734, vert735, vert736, vert737, vert738, vert739, vert740,
		vert741, vert742, vert743, vert744, vert745, vert746, vert747, vert748, vert749, vert750,
		vert751, vert752, vert753, vert754, vert755, vert756, vert757, vert758, vert759, vert760,
		vert761, vert762, vert763, vert764, vert765, vert766, vert767, vert768, vert769, vert770,
		vert771, vert772, vert773, vert774, vert775, vert776, vert777, vert778, vert779, vert780,
		vert781, vert782, vert783, vert784, vert785, vert786, vert787, vert788, vert789, vert790,
		vert791, vert792, vert793, vert794, vert795, vert796, vert797, vert798, vert799, vert800,
		vert801, vert802, vert803, vert804, vert805, vert806, vert807, vert808, vert809, vert810,
		vert811, vert812, vert813, vert814, vert815, vert816, vert817, vert818, vert819, vert820,
		vert821, vert822, vert823, vert824, vert825, vert826, vert827, vert828, vert829, vert830,
		vert831, vert832, vert833, vert834, vert835, vert836, vert837, vert838, vert839, vert840,
		vert841, vert842, vert843, vert844, vert845, vert846, vert847, vert848, vert849, vert850,
		vert851, vert852, vert853, vert854, vert855, vert856, vert857, vert858, vert859, vert860,
		vert861, vert862, vert863, vert864, vert865, vert866, vert867, vert868, vert869, vert870,
		vert871, vert872, vert873, vert874, vert875, vert876, vert877, vert878, vert879, vert880,
		vert881, vert882, vert883, vert884, vert885, vert886, vert887, vert888, vert889, vert890,
		vert891, vert892, vert893, vert894, vert895, vert896, vert897, vert898, vert899, vert900,
		vert901, vert902, vert903, vert904, vert905, vert906, vert907, vert908, vert909, vert910,
		vert911, vert912, vert913, vert914, vert915, vert916, vert917, vert918, vert919, vert920,
		vert921, vert922, vert923, vert924, vert925, vert926, vert927, vert928, vert929, vert930,
		vert931, vert932, vert933, vert934, vert935, vert936, vert937, vert938, vert939, vert940,
		vert941, vert942, vert943, vert944, vert945, vert946, vert947, vert948, vert949, vert950,
		vert951, vert952, vert953, vert954, vert955, vert956, vert957, vert958, vert959, vert960,
		vert961, vert962, vert963, vert964, vert965, vert966, vert967, vert968, vert969, vert970,
		vert971, vert972, vert973, vert974, vert975, vert976, vert977, vert978, vert979, vert980,
		vert981, vert982, vert983, vert984, vert985, vert986, vert987, vert988, vert989, vert990,
		vert991 };
		*/
	/* Tris. Initiallize an array with this data. When I feed it into tri structures,
		design the loop as 0 2 1 3 5 4 ... *
	TArray<int32> triArrayFromBlender = { 27, 19, 11, 54, 85, 53, 26, 59, 58, 14, 45, 13, 27, 60, 59, 15, 46, 14, 1,
	34, 33, 28, 61, 60, 16, 47, 15, 3, 34, 2,
	30, 61, 29, 16, 49, 48, 4, 35, 3, 30, 63, 62, 18, 49, 17, 5, 36, 4, 31, 64, 63, 18, 51, 50, 6, 37, 5, 1, 64, 32,
	20, 51, 19, 7, 38, 6, 21, 52, 20, 8, 39, 7, 21, 54, 53, 9, 40, 8, 23, 54, 22, 10, 41, 9, 23, 56, 55, 11, 42, 10,
	24, 57, 56, 12, 43, 11, 25, 58, 57, 13, 44, 12, 89, 120, 88, 41, 72, 40, 55, 86, 54, 42, 73, 41, 55, 88, 87, 42,
	75, 74, 57, 88, 56, 44, 75, 43, 57, 90, 89, 45, 76, 44, 58, 91, 90, 46, 77, 45, 59, 92, 91, 47, 78, 46, 33, 66, 65,
	60, 93, 92, 48, 79, 47, 35, 66, 34, 62, 93, 61, 49, 80, 48, 36, 67, 35, 62, 95, 94, 50, 81, 49, 36, 69, 68, 64, 95,
	63, 51, 82, 50, 38, 69, 37, 33, 96, 64, 51, 84, 83, 39, 70, 38, 53, 84, 52, 39, 72, 71, 123, 156, 155, 76, 107, 75,
	89, 122, 121, 77, 108, 76, 90, 123, 122, 78, 109, 77, 92, 123, 91, 79, 110, 78, 65, 98, 97, 92, 125, 124, 80, 111, 79,
	66, 99, 98, 94, 125, 93, 81, 112, 80, 67, 100, 99, 95, 126, 94, 82, 113, 81, 69, 100, 68, 95, 128, 127, 82, 115, 114,
	69, 102, 101, 65, 128, 96, 84, 115, 83, 71, 102, 70, 84, 117, 116, 71, 104, 103, 85, 118, 117, 73, 104, 72, 87, 118, 86,
	74, 105, 73, 87, 120, 119, 74, 107, 106, 131, 164, 163, 110, 143, 142, 97, 130, 129, 124, 157, 156, 111, 144, 143, 98,
	131, 130, 125, 158, 157, 112, 145, 144, 99, 132, 131, 126, 159, 158, 113, 146, 145, 100, 133, 132, 127, 160, 159, 114,
	147, 146, 101, 134, 133, 128, 129, 160, 115, 148, 147, 102, 135, 134, 116, 149, 148, 103, 136, 135, 117, 150, 149, 104,
	137, 136, 118, 151, 150, 105, 138, 137, 119, 152, 151, 106, 139, 138, 120, 153, 152, 107, 140, 139, 121, 154, 153, 108,
	141, 140, 122, 155, 154, 109, 142, 141, 167, 198, 166, 158, 191, 190, 146, 177, 145, 133, 164, 132, 160, 191, 159, 146,
	179, 178, 134, 165, 133, 129, 192, 160, 148, 179, 147, 134, 167, 166, 149, 180, 148, 136, 167, 135, 150, 181, 149, 137,
	168, 136, 151, 182, 150, 137, 170, 169, 151, 184, 183, 138, 171, 170, 153, 184, 152, 140, 171, 139, 154, 185, 153, 141,
	172, 140, 154, 187, 186, 142, 173, 141, 155, 188, 187, 142, 175, 174, 129, 162, 161, 156, 189, 188, 144, 175, 143, 131,
	162, 130, 158, 189, 157, 144, 177, 176, 202, 233, 201, 181, 212, 180, 167, 200, 199, 181, 214, 213, 169, 200, 168, 183,
	214, 182, 170, 201, 169, 183, 216, 215, 170, 203, 202, 185, 216, 184, 172, 203, 171, 186, 217, 185, 173, 204, 172, 186,
	219, 218, 174, 205, 173, 188, 219, 187, 175, 206, 174, 162, 193, 161, 188, 221, 220, 176, 207, 175, 163, 194, 162, 190,
	221, 189, 177, 208, 176, 164, 195, 163, 191, 222, 190, 178, 209, 177, 165, 196, 164, 192, 223, 191, 178, 211, 210, 165,
	198, 197, 161, 224, 192, 180, 211, 179, 236, 269, 268, 216, 247, 215, 203, 234, 202, 217, 248, 216, 204, 235, 203, 218,
	249, 217, 205, 236, 204, 219, 250, 218, 206, 237, 205, 220, 251, 219, 207, 238, 206, 194, 225, 193, 221, 252, 220, 208,
	239, 207, 195, 226, 194, 222, 253, 221, 209, 240, 208, 196, 227, 195, 223, 254, 222, 210, 241, 209, 197, 228, 196, 224,
	255, 223, 211, 242, 210, 198, 229, 197, 193, 256, 224, 212, 243, 211, 199, 230, 198, 213, 244, 212, 200, 231, 199, 214,
	245, 213, 201, 232, 200, 215, 246, 214, 271, 304, 303, 251, 282, 250, 237, 270, 269, 252, 283, 251, 238, 271, 270, 226,
	257, 225, 253, 284, 252, 239, 272, 271, 226, 259, 258, 253, 286, 285, 241, 272, 240, 228, 259, 227, 254, 287, 286, 241,
	274, 273, 228, 261, 260, 256, 287, 255, 243, 274, 242, 230, 261, 229, 225, 288, 256, 244, 275, 243, 230, 263, 262, 245,
	276, 244, 232, 263, 231, 246, 277, 245, 233, 264, 232, 246, 279, 278, 233, 266, 265, 248, 279, 247, 235, 266, 234, 248,
	281, 280, 236, 267, 235, 249, 282, 281, 307, 338, 306, 258, 291, 290, 285, 318, 317, 273, 304, 272, 260, 291, 259, 287,
	318, 286, 273, 306, 305, 260, 293, 292, 288, 319, 287, 275, 306, 274, 261, 294, 293, 257, 320, 288, 276, 307, 275, 263,
	294, 262, 276, 309, 308, 264, 295, 263, 277, 310, 309, 265, 296, 264, 278, 311, 310, 265, 298, 297, 280, 311, 279, 267,
	298, 266, 280, 313, 312, 267, 300, 299, 281, 314, 313, 268, 301, 300, 283, 314, 282, 269, 302, 301, 284, 315, 283, 270,
	303, 302, 258, 289, 257, 285, 316, 284, 339, 365, 366, 294, 325, 293, 289, 352, 320, 308, 339, 307, 295, 326, 294, 308,
	341, 340, 296, 327, 295, 310, 341, 309, 296, 329, 328, 310, 343, 342, 297, 330, 329, 312, 343, 311, 299, 330, 298, 312,
	345, 344, 299, 332, 331, 313, 346, 345, 300, 333, 332, 315, 346, 314, 301, 334, 333, 316, 347, 315, 302, 335, 334, 290,
	321, 289, 317, 348, 316, 303, 336, 335, 290, 323, 322, 317, 350, 349, 305, 336, 304, 292, 323, 291, 319, 350, 318, 305,
	338, 337, 293, 324, 292, 320, 351, 319, 363, 396, 364, 404, 435, 436, 326, 380, 325, 406, 437, 438, 352, 354, 351, 355,
	388, 356, 324, 382, 323, 367, 398, 399, 350, 356, 349, 354, 387, 355, 334, 370, 371, 376, 407, 408, 333, 371, 372, 371,
	402, 403, 411, 442, 443, 332, 372, 373, 369, 400, 401, 413, 444, 445, 331, 373, 374, 383, 416, 384, 414, 445, 446, 329,
	375, 376, 377, 408, 409, 389, 422, 390, 329, 377, 328, 356, 389, 357, 403, 434, 435, 341, 363, 364, 373, 404, 405, 386,
	419, 387, 328, 378, 327, 394, 427, 395, 3, 2, 1, 1, 32, 3, 32, 31, 3, 31, 30, 29, 29, 28, 27, 27, 26, 25, 25, 24, 27, 24,
	23, 27, 23, 22, 19, 22, 21, 19, 21, 20, 19, 19, 18, 17, 17, 16, 15, 15, 14, 13, 13, 12, 11, 11, 10, 9, 9, 8, 11, 8, 7, 11,
	7, 6, 5, 5, 4, 3, 31, 29, 3, 29, 27, 3, 19, 17, 11, 17, 15, 11, 15, 13, 11, 7, 5, 11, 5, 3, 11, 27, 23, 19, 3, 27, 11, 54,
	86, 85, 26, 27, 59, 14, 46, 45, 27, 28, 60, 15, 47, 46, 1, 2, 34, 28, 29, 61, 16, 48, 47, 3, 35, 34, 30, 62, 61, 16, 17, 49,
	4, 36, 35, 30, 31, 63, 18, 50, 49, 5, 37, 36, 31, 32, 64, 18, 19, 51, 6, 38, 37, 1, 33, 64, 20, 52, 51, 7, 39, 38, 21, 53,
	52, 8, 40, 39, 21, 22, 54, 9, 41, 40, 23, 55, 54, 10, 42, 41, 23, 24, 56, 11, 43, 42, 24, 25, 57, 12, 44, 43, 25, 26, 58, 13,
	45, 44, 89, 121, 120, 41, 73, 72, 55, 87, 86, 42, 74, 73, 55, 56, 88, 42, 43, 75, 57, 89, 88, 44, 76, 75, 57, 58, 90, 45, 77,
	76, 58, 59, 91, 46, 78, 77, 59, 60, 92, 47, 79, 78, 33, 34, 66, 60, 61, 93, 48, 80, 79, 35, 67, 66, 62, 94, 93, 49, 81, 80,
	36, 68, 67, 62, 63, 95, 50, 82, 81, 36, 37, 69, 64, 96, 95, 51, 83, 82, 38, 70, 69, 33, 65, 96, 51, 52, 84, 39, 71, 70, 53,
	85, 84, 39, 40, 72, 123, 124, 156, 76, 108, 107, 89, 90, 122, 77, 109, 108, 90, 91, 123, 78, 110, 109, 92, 124, 123, 79, 111,
	110, 65, 66, 98, 92, 93, 125, 80, 112, 111, 66, 67, 99, 94, 126, 125, 81, 113, 112, 67, 68, 100, 95, 127, 126, 82, 114, 113,
	69, 101, 100, 95, 96, 128, 82, 83, 115, 69, 70, 102, 65, 97, 128, 84, 116, 115, 71, 103, 102, 84, 85, 117, 71, 72, 104, 85,
	86, 118, 73, 105, 104, 87, 119, 118, 74, 106, 105, 87, 88, 120, 74, 75, 107, 131, 132, 164, 110, 111, 143, 97, 98, 130, 124,
	125, 157, 111, 112, 144, 98, 99, 131, 125, 126, 158, 112, 113, 145, 99, 100, 132, 126, 127, 159, 113, 114, 146, 100, 101, 133,
	127, 128, 160, 114, 115, 147, 101, 102, 134, 128, 97, 129, 115, 116, 148, 102, 103, 135, 116, 117, 149, 103, 104, 136, 117, 118,
	150, 104, 105, 137, 118, 119, 151, 105, 106, 138, 119, 120, 152, 106, 107, 139, 120, 121, 153, 107, 108, 140, 121, 122, 154, 108,
	109, 141, 122, 123, 155, 109, 110, 142, 167, 199, 198, 158, 159, 191, 146, 178, 177, 133, 165, 164, 160, 192, 191, 146, 147, 179,
	134, 166, 165, 129, 161, 192, 148, 180, 179, 134, 135, 167, 149, 181, 180, 136, 168, 167, 150, 182, 181, 137, 169, 168, 151, 183,
	182, 137, 138, 170, 151, 152, 184, 138, 139, 171, 153, 185, 184, 140, 172, 171, 154, 186, 185, 141, 173, 172, 154, 155, 187, 142,
	174, 173, 155, 156, 188, 142, 143, 175, 129, 130, 162, 156, 157, 189, 144, 176, 175, 131, 163, 162, 158, 190, 189, 144, 145, 177,
	202, 234, 233, 181, 213, 212, 167, 168, 200, 181, 182, 214, 169, 201, 200, 183, 215, 214, 170, 202, 201, 183, 184, 216, 170, 171,
	203, 185, 217, 216, 172, 204, 203, 186, 218, 217, 173, 205, 204, 186, 187, 219, 174, 206, 205, 188, 220, 219, 175, 207, 206, 162,
	194, 193, 188, 189, 221, 176, 208, 207, 163, 195, 194, 190, 222, 221, 177, 209, 208, 164, 196, 195, 191, 223, 222, 178, 210, 209,
	165, 197, 196, 192, 224, 223, 178, 179, 211, 165, 166, 198, 161, 193, 224, 180, 212, 211, 236, 237, 269, 216, 248, 247, 203, 235,
	234, 217, 249, 248, 204, 236, 235, 218, 250, 249, 205, 237, 236, 219, 251, 250, 206, 238, 237, 220, 252, 251, 207, 239, 238, 194,
	226, 225, 221, 253, 252, 208, 240, 239, 195, 227, 226, 222, 254, 253, 209, 241, 240, 196, 228, 227, 223, 255, 254, 210, 242, 241,
	197, 229, 228, 224, 256, 255, 211, 243, 242, 198, 230, 229, 193, 225, 256, 212, 244, 243, 199, 231, 230, 213, 245, 244, 200, 232,
	231, 214, 246, 245, 201, 233, 232, 215, 247, 246, 271, 272, 304, 251, 283, 282, 237, 238, 270, 252, 284, 283, 238, 239, 271, 226,
	258, 257, 253, 285, 284, 239, 240, 272, 226, 227, 259, 253, 254, 286, 241, 273, 272, 228, 260, 259, 254, 255, 287, 241, 242, 274,
	228, 229, 261, 256, 288, 287, 243, 275, 274, 230, 262, 261, 225, 257, 288, 244, 276, 275, 230, 231, 263, 245, 277, 276, 232, 264,
	263, 246, 278, 277, 233, 265, 264, 246, 247, 279, 233, 234, 266, 248, 280, 279, 235, 267, 266, 248, 249, 281, 236, 268, 267, 249,
	250, 282, 307, 339, 338, 258, 259, 291, 285, 286, 318, 273, 305, 304, 260, 292, 291, 287, 319, 318, 273, 274, 306, 260, 261, 293,
	288, 320, 319, 275, 307, 306, 261, 262, 294, 257, 289, 320, 276, 308, 307, 263, 295, 294, 276, 277, 309, 264, 296, 295, 277, 278,
	310, 265, 297, 296, 278, 279, 311, 265, 266, 298, 280, 312, 311, 267, 299, 298, 280, 281, 313, 267, 268, 300, 281, 282, 314, 268,
	269, 301, 283, 315, 314, 269, 270, 302, 284, 316, 315, 270, 271, 303, 258, 290, 289, 285, 317, 316, 327, 379, 326, 294, 326, 325,
	289, 321, 352, 308, 340, 339, 295, 327, 326, 308, 309, 341, 296, 328, 327, 310, 342, 341, 296, 297, 329, 310, 311, 343, 297, 298,
	330, 312, 344, 343, 299, 331, 330, 312, 313, 345, 299, 300, 332, 313, 314, 346, 300, 301, 333, 315, 347, 346, 301, 302, 334, 316,
	348, 347, 302, 303, 335, 290, 322, 321, 317, 349, 348, 303, 304, 336, 290, 291, 323, 317, 318, 350, 305, 337, 336, 292, 324, 323,
	319, 351, 350, 305, 306, 338, 293, 325, 324, 320, 352, 351, 412, 443, 444, 397, 430, 398, 416, 447, 448, 388, 421, 389, 393, 426,
	394, 387, 420, 388, 379, 410, 411, 378, 409, 410, 380, 411, 412, 359, 392, 360, 357, 390, 358, 381, 414, 382, 340, 364, 365, 321,
	353, 352, 338, 366, 367, 336, 368, 369, 323, 383, 322, 335, 369, 370, 346, 360, 345, 344, 360, 361, 396, 429, 397, 416, 417, 385,
	395, 428, 396, 360, 393, 361, 366, 397, 398, 390, 423, 391, 368, 399, 400, 405, 436, 437, 385, 418, 386, 402, 433, 434, 325, 381,
	324, 370, 401, 402, 351, 355, 350, 375, 406, 407, 337, 367, 368, 382, 415, 383, 322, 384, 321, 381, 412, 413, 349, 357, 348, 374,
	405, 406, 348, 358, 347, 362, 395, 363, 410, 441, 442, 347, 359, 346, 372, 403, 404, 392, 425, 393, 343, 361, 362, 358, 391, 359,
	409, 440, 441, 330, 374, 375, 353, 386, 354, 398, 431, 399, 342, 362, 363, 361, 394, 362, 391, 424, 392, 399, 432, 400, 384, 385,
	353, 415, 446, 447, 364, 397, 365, 401, 432, 433, 408, 439, 440, 407, 438, 439, 448, 449, 417, 439, 470, 471, 425, 458, 426, 427,
	460, 428, 422, 455, 423, 447, 480, 448, 424, 457, 425, 434, 465, 466, 446, 477, 478, 445, 476, 477, 426, 459, 427, 417, 450, 418,
	433, 464, 465, 444, 475, 476, 420, 453, 421, 419, 452, 420, 428, 461, 429, 418, 451, 419, 442, 473, 474, 435, 466, 467, 438, 469,
	470, 423, 456, 424, 446, 479, 447, 441, 472, 473, 431, 462, 463, 437, 468, 469, 421, 454, 422, 443, 474, 475, 440, 471, 472, 429,
	462, 430, 432, 463, 464, 436, 467, 468, 477, 508, 509, 458, 491, 459, 450, 481, 482, 464, 497, 465, 475, 508, 476, 453, 484, 485,
	452, 483, 484, 460, 493, 461, 451, 482, 483, 473, 506, 474, 466, 499, 467, 469, 502, 470, 456, 487, 488, 478, 511, 479, 473, 504,
	505, 463, 494, 495, 469, 500, 501, 454, 485, 486, 475, 506, 507, 471, 504, 472, 461, 494, 462, 463, 496, 464, 467, 500, 468, 449,
	512, 481, 471, 502, 503, 457, 490, 458, 459, 492, 460, 455, 486, 487, 480, 511, 512, 456, 489, 457, 465, 498, 466, 478, 509, 510,
	484, 515, 516, 492, 525, 493, 483, 514, 515, 506, 537, 538, 498, 531, 499, 501, 534, 502, 487, 520, 488, 510, 543, 511, 504, 537,
	505, 495, 526, 527, 501, 532, 533, 486, 517, 518, 507, 538, 539, 504, 535, 536, 493, 526, 494, 495, 528, 496, 499, 532, 500, 481,
	544, 513, 502, 535, 503, 489, 522, 490, 491, 524, 492, 487, 518, 519, 511, 544, 512, 488, 521, 489, 498, 529, 530, 510, 541, 542,
	509, 540, 541, 490, 523, 491, 482, 513, 514, 497, 528, 529, 507, 540, 508, 485, 516, 517, 519, 552, 520, 543, 574, 575, 536, 569,
	537, 527, 558, 559, 533, 564, 565, 518, 549, 550, 539, 570, 571, 535, 568, 536, 525, 558, 526, 527, 560, 528, 531, 564, 532, 513,
	576, 545, 534, 567, 535, 521, 554, 522, 523, 556, 524, 518, 551, 519, 543, 576, 544, 520, 553, 521, 529, 562, 530, 542, 573, 574,
	541, 572, 573, 522, 555, 523, 514, 545, 546, 529, 560, 561, 539, 572, 540, 517, 548, 549, 516, 547, 548, 524, 557, 525, 515, 546,
	547, 537, 570, 538, 531, 562, 563, 533, 566, 534, 568, 599, 600, 557, 590, 558, 559, 592, 560, 563, 596, 564, 545, 608, 577, 566,
	599, 567, 553, 586, 554, 555, 588, 556, 551, 582, 583, 575, 608, 576, 552, 585, 553, 561, 594, 562, 574, 605, 606, 573, 604, 605,
	554, 587, 555, 546, 577, 578, 561, 592, 593, 571, 604, 572, 549, 580, 581, 547, 580, 548, 556, 589, 557, 546, 579, 547, 570, 601,
	602, 562, 595, 563, 565, 598, 566, 552, 583, 584, 575, 606, 607, 568, 601, 569, 559, 590, 591, 565, 596, 597, 550, 581, 582, 571,
	602, 603, 607, 640, 608, 585, 616, 617, 593, 626, 594, 606, 637, 638, 605, 636, 637, 586, 619, 587, 578, 609, 610, 593, 624, 625,
	603, 636, 604, 581, 612, 613, 579, 612, 580, 588, 621, 589, 579, 610, 611, 602, 633, 634, 594, 627, 595, 597, 630, 598, 584, 615,
	616, 607, 638, 639, 600, 633, 601, 590, 623, 591, 597, 628, 629, 582, 613, 614, 603, 634, 635, 599, 632, 600, 589, 622, 590, 591,
	624, 592, 595, 628, 596, 577, 640, 609, 598, 631, 599, 586, 617, 618, 587, 620, 588, 582, 615, 583, 635, 668, 636, 613, 644, 645,
	612, 643, 644, 620, 653, 621, 610, 643, 611, 634, 665, 666, 626, 659, 627, 629, 662, 630, 615, 648, 616, 639, 670, 671, 632, 665,
	633, 622, 655, 623, 629, 660, 661, 614, 645, 646, 635, 666, 667, 632, 663, 664, 622, 653, 654, 623, 656, 624, 627, 660, 628, 609,
	672, 641, 630, 663, 631, 617, 650, 618, 619, 652, 620, 614, 647, 615, 639, 672, 640, 616, 649, 617, 625, 658, 626, 637, 670, 638,
	637, 668, 669, 618, 651, 619, 610, 641, 642, 625, 656, 657, 658, 691, 659, 661, 694, 662, 647, 680, 648, 671, 702, 703, 665, 696,
	697, 654, 687, 655, 660, 693, 661, 646, 677, 678, 667, 698, 699, 664, 695, 696, 653, 686, 654, 655, 688, 656, 659, 692, 660, 641,
	704, 673, 662, 695, 663, 649, 682, 650, 651, 684, 652, 647, 678, 679, 672, 703, 704, 648, 681, 649, 657, 690, 658, 670, 701, 702,
	669, 700, 701, 650, 683, 651, 642, 673, 674, 656, 689, 657, 668, 699, 700, 645, 676, 677, 644, 675, 676, 652, 685, 653, 643, 674,
	675, 666, 697, 698, 701, 732, 733, 682, 715, 683, 674, 705, 706, 688, 721, 689, 700, 731, 732, 677, 708, 709, 676, 707, 708, 684,
	717, 685, 675, 706, 707, 698, 729, 730, 690, 723, 691, 693, 726, 694, 679, 712, 680, 703, 734, 735, 697, 728, 729, 686, 719, 687,
	692, 725, 693, 678, 709, 710, 699, 730, 731, 696, 727, 728, 685, 718, 686, 687, 720, 688, 691, 724, 692, 673, 736, 705, 694, 727,
	695, 681, 714, 682, 683, 716, 684, 679, 710, 711, 704, 735, 736, 680, 713, 681, 689, 722, 690, 702, 733, 734, 708, 739, 740, 716,
	749, 717, 707, 738, 739, 730, 761, 762, 722, 755, 723, 725, 758, 726, 711, 744, 712, 735, 766, 767, 729, 760, 761, 718, 751, 719,
	724, 757, 725, 710, 741, 742, 731, 762, 763, 728, 759, 760, 717, 750, 718, 719, 752, 720, 723, 756, 724, 705, 768, 737, 726, 759,
	727, 713, 746, 714, 715, 748, 716, 711, 742, 743, 736, 767, 768, 712, 745, 713, 721, 754, 722, 734, 765, 766, 733, 764, 765, 714,
	747, 715, 706, 737, 738, 720, 753, 721, 732, 763, 764, 709, 740, 741, 743, 776, 744, 767, 798, 799, 761, 792, 793, 750, 783, 751,
	756, 789, 757, 742, 773, 774, 763, 794, 795, 760, 791, 792, 749, 782, 750, 751, 784, 752, 755, 788, 756, 737, 800, 769, 758, 791,
	759, 745, 778, 746, 747, 780, 748, 743, 774, 775, 768, 799, 800, 744, 777, 745, 753, 786, 754, 766, 797, 798, 765, 796, 797, 746,
	779, 747, 738, 769, 770, 752, 785, 753, 764, 795, 796, 741, 772, 773, 740, 771, 772, 748, 781, 749, 739, 770, 771, 762, 793, 794,
	754, 787, 755, 757, 790, 758, 792, 823, 824, 781, 814, 782, 783, 816, 784, 787, 820, 788, 769, 832, 801, 790, 823, 791, 777, 810,
	778, 779, 812, 780, 775, 806, 807, 800, 831, 832, 776, 809, 777, 785, 818, 786, 798, 829, 830, 797, 828, 829, 778, 811, 779, 770,
	801, 802, 784, 817, 785, 796, 827, 828, 773, 804, 805, 772, 803, 804, 780, 813, 781, 771, 802, 803, 794, 825, 826, 786, 819, 787,
	789, 822, 790, 775, 808, 776, 799, 830, 831, 793, 824, 825, 782, 815, 783, 788, 821, 789, 774, 805, 806, 795, 826, 827, 832, 863,
	864, 808, 841, 809, 817, 850, 818, 830, 861, 862, 829, 860, 861, 810, 843, 811, 802, 833, 834, 816, 849, 817, 828, 859, 860, 805,
	836, 837, 804, 835, 836, 812, 845, 813, 803, 834, 835, 826, 857, 858, 818, 851, 819, 821, 854, 822, 807, 840, 808, 831, 862, 863,
	825, 856, 857, 814, 847, 815, 820, 853, 821, 806, 837, 838, 827, 858, 859, 824, 855, 856, 813, 846, 814, 815, 848, 816, 819, 852,
	820, 801, 864, 833, 822, 855, 823, 809, 842, 810, 811, 844, 812, 807, 838, 839, 860, 891, 892, 837, 868, 869, 836, 867, 868, 844,
	877, 845, 835, 866, 867, 858, 889, 890, 850, 883, 851, 853, 886, 854, 839, 872, 840, 863, 894, 895, 857, 888, 889, 846, 879, 847,
	852, 885, 853, 838, 869, 870, 859, 890, 891, 856, 887, 888, 845, 878, 846, 847, 880, 848, 851, 884, 852, 833, 896, 865, 854, 887,
	855, 841, 874, 842, 843, 876, 844, 839, 870, 871, 864, 895, 896, 840, 873, 841, 849, 882, 850, 862, 893, 894, 861, 892, 893, 842,
	875, 843, 834, 865, 866, 848, 881, 849, 882, 915, 883, 885, 918, 886, 871, 904, 872, 895, 926, 927, 889, 920, 921, 878, 911, 879,
	884, 917, 885, 870, 901, 902, 891, 922, 923, 888, 919, 920, 877, 910, 878, 879, 912, 880, 883, 916, 884, 865, 928, 897, 886, 919,
	887, 873, 906, 874, 875, 908, 876, 871, 902, 903, 896, 927, 928, 872, 905, 873, 881, 914, 882, 894, 925, 926, 893, 924, 925, 874,
	907, 875, 866, 897, 898, 880, 913, 881, 892, 923, 924, 869, 900, 901, 868, 899, 900, 876, 909, 877, 867, 898, 899, 890, 921, 922,
	916, 949, 917, 902, 933, 934, 923, 954, 955, 920, 951, 952, 909, 942, 910, 911, 944, 912, 915, 948, 916, 897, 960, 929, 919, 950,
	951, 905, 938, 906, 907, 940, 908, 902, 935, 903, 928, 959, 960, 904, 937, 905, 913, 946, 914, 926, 957, 958, 925, 956, 957, 906,
	939, 907, 898, 929, 930, 912, 945, 913, 924, 955, 956, 901, 932, 933, 900, 931, 932, 908, 941, 909, 899, 930, 931, 922, 953, 954,
	914, 947, 915, 917, 950, 918, 903, 936, 904, 927, 958, 959, 921, 952, 953, 910, 943, 911, 951, 982, 983, 937, 970, 938, 939, 972,
	940, 934, 967, 935, 960, 991, 992, 936, 969, 937, 945, 978, 946, 958, 989, 990, 957, 988, 989, 938, 971, 939, 930, 961, 962, 944,
	977, 945, 956, 987, 988, 933, 964, 965, 932, 963, 964, 940, 973, 941, 931, 962, 963, 954, 985, 986, 946, 979, 947, 950, 981, 982,
	935, 968, 936, 959, 990, 991, 953, 984, 985, 942, 975, 943, 948, 981, 949, 933, 966, 934, 955, 986, 987, 952, 983, 984, 941, 974,
	942, 943, 976, 944, 947, 980, 948, 929, 992, 961, 339, 340, 365, 363, 395, 396, 404, 403, 435, 326, 379, 380, 406, 405, 437, 352,
	353, 354, 355, 387, 388, 324, 381, 382, 367, 366, 398, 350, 355, 356, 354, 386, 387, 334, 335, 370, 376, 375, 407, 333, 334, 371,
	371, 370, 402, 411, 410, 442, 332, 333, 372, 369, 368, 400, 413, 412, 444, 331, 332, 373, 383, 415, 416, 414, 413, 445, 329, 330,
	375, 377, 376, 408, 389, 421, 422, 329, 376, 377, 356, 388, 389, 403, 402, 434, 341, 342, 363, 373, 372, 404, 386, 418, 419, 328,
	377, 378, 394, 426, 427, 327, 378, 379, 412, 411, 443, 397, 429, 430, 416, 415, 447, 388, 420, 421, 393, 425, 426, 387, 419, 420,
	379, 378, 410, 378, 377, 409, 380, 379, 411, 359, 391, 392, 357, 389, 390, 381, 413, 414, 340, 341, 364, 321, 384, 353, 338, 339,
	366, 336, 337, 368, 323, 382, 383, 335, 336, 369, 346, 359, 360, 344, 345, 360, 396, 428, 429, 416, 448, 417, 395, 427, 428, 360,
	392, 393, 366, 365, 397, 390, 422, 423, 368, 367, 399, 405, 404, 436, 385, 417, 418, 402, 401, 433, 325, 380, 381, 370, 369, 401,
	351, 354, 355, 375, 374, 406, 337, 338, 367, 382, 414, 415, 322, 383, 384, 381, 380, 412, 349, 356, 357, 374, 373, 405, 348, 357,
	358, 362, 394, 395, 410, 409, 441, 347, 358, 359, 372, 371, 403, 392, 424, 425, 343, 344, 361, 358, 390, 391, 409, 408, 440, 330,
	331, 374, 353, 385, 386, 398, 430, 431, 342, 343, 362, 361, 393, 394, 391, 423, 424, 399, 431, 432, 384, 416, 385, 415, 414, 446,
	364, 396, 397, 401, 400, 432, 408, 407, 439, 407, 406, 438, 448, 480, 449, 439, 438, 470, 425, 457, 458, 427, 459, 460, 422, 454,
	455, 447, 479, 480, 424, 456, 457, 434, 433, 465, 446, 445, 477, 445, 444, 476, 426, 458, 459, 417, 449, 450, 433, 432, 464, 444,
	443, 475, 420, 452, 453, 419, 451, 452, 428, 460, 461, 418, 450, 451, 442, 441, 473, 435, 434, 466, 438, 437, 469, 423, 455, 456,
	446, 478, 479, 441, 440, 472, 431, 430, 462, 437, 436, 468, 421, 453, 454, 443, 442, 474, 440, 439, 471, 429, 461, 462, 432, 431,
	463, 436, 435, 467, 477, 476, 508, 458, 490, 491, 450, 449, 481, 464, 496, 497, 475, 507, 508, 453, 452, 484, 452, 451, 483, 460,
	492, 493, 451, 450, 482, 473, 505, 506, 466, 498, 499, 469, 501, 502, 456, 455, 487, 478, 510, 511, 473, 472, 504, 463, 462, 494,
	469, 468, 500, 454, 453, 485, 475, 474, 506, 471, 503, 504, 461, 493, 494, 463, 495, 496, 467, 499, 500, 449, 480, 512, 471, 470,
	502, 457, 489, 490, 459, 491, 492, 455, 454, 486, 480, 479, 511, 456, 488, 489, 465, 497, 498, 478, 477, 509, 484, 483, 515, 492,
	524, 525, 483, 482, 514, 506, 505, 537, 498, 530, 531, 501, 533, 534, 487, 519, 520, 510, 542, 543, 504, 536, 537, 495, 494, 526,
	501, 500, 532, 486, 485, 517, 507, 506, 538, 504, 503, 535, 493, 525, 526, 495, 527, 528, 499, 531, 532, 481, 512, 544, 502, 534,
	535, 489, 521, 522, 491, 523, 524, 487, 486, 518, 511, 543, 544, 488, 520, 521, 498, 497, 529, 510, 509, 541, 509, 508, 540, 490,
	522, 523, 482, 481, 513, 497, 496, 528, 507, 539, 540, 485, 484, 516, 519, 551, 552, 543, 542, 574, 536, 568, 569, 527, 526, 558,
	533, 532, 564, 518, 517, 549, 539, 538, 570, 535, 567, 568, 525, 557, 558, 527, 559, 560, 531, 563, 564, 513, 544, 576, 534, 566,
	567, 521, 553, 554, 523, 555, 556, 518, 550, 551, 543, 575, 576, 520, 552, 553, 529, 561, 562, 542, 541, 573, 541, 540, 572, 522,
	554, 555, 514, 513, 545, 529, 528, 560, 539, 571, 572, 517, 516, 548, 516, 515, 547, 524, 556, 557, 515, 514, 546, 537, 569, 570,
	531, 530, 562, 533, 565, 566, 568, 567, 599, 557, 589, 590, 559, 591, 592, 563, 595, 596, 545, 576, 608, 566, 598, 599, 553, 585,
	586, 555, 587, 588, 551, 550, 582, 575, 607, 608, 552, 584, 585, 561, 593, 594, 574, 573, 605, 573, 572, 604, 554, 586, 587, 546,
	545, 577, 561, 560, 592, 571, 603, 604, 549, 548, 580, 547, 579, 580, 556, 588, 589, 546, 578, 579, 570, 569, 601, 562, 594, 595,
	565, 597, 598, 552, 551, 583, 575, 574, 606, 568, 600, 601, 559, 558, 590, 565, 564, 596, 550, 549, 581, 571, 570, 602, 607, 639,
	640, 585, 584, 616, 593, 625, 626, 606, 605, 637, 605, 604, 636, 586, 618, 619, 578, 577, 609, 593, 592, 624, 603, 635, 636, 581,
	580, 612, 579, 611, 612, 588, 620, 621, 579, 578, 610, 602, 601, 633, 594, 626, 627, 597, 629, 630, 584, 583, 615, 607, 606, 638,
	600, 632, 633, 590, 622, 623, 597, 596, 628, 582, 581, 613, 603, 602, 634, 599, 631, 632, 589, 621, 622, 591, 623, 624, 595, 627,
	628, 577, 608, 640, 598, 630, 631, 586, 585, 617, 587, 619, 620, 582, 614, 615, 635, 667, 668, 613, 612, 644, 612, 611, 643, 620,
	652, 653, 610, 642, 643, 634, 633, 665, 626, 658, 659, 629, 661, 662, 615, 647, 648, 639, 638, 670, 632, 664, 665, 622, 654, 655,
	629, 628, 660, 614, 613, 645, 635, 634, 666, 632, 631, 663, 622, 621, 653, 623, 655, 656, 627, 659, 660, 609, 640, 672, 630, 662,
	663, 617, 649, 650, 619, 651, 652, 614, 646, 647, 639, 671, 672, 616, 648, 649, 625, 657, 658, 637, 669, 670, 637, 636, 668, 618,
	650, 651, 610, 609, 641, 625, 624, 656, 658, 690, 691, 661, 693, 694, 647, 679, 680, 671, 670, 702, 665, 664, 696, 654, 686, 687,
	660, 692, 693, 646, 645, 677, 667, 666, 698, 664, 663, 695, 653, 685, 686, 655, 687, 688, 659, 691, 692, 641, 672, 704, 662, 694,
	695, 649, 681, 682, 651, 683, 684, 647, 646, 678, 672, 671, 703, 648, 680, 681, 657, 689, 690, 670, 669, 701, 669, 668, 700, 650,
	682, 683, 642, 641, 673, 656, 688, 689, 668, 667, 699, 645, 644, 676, 644, 643, 675, 652, 684, 685, 643, 642, 674, 666, 665, 697,
	701, 700, 732, 682, 714, 715, 674, 673, 705, 688, 720, 721, 700, 699, 731, 677, 676, 708, 676, 675, 707, 684, 716, 717, 675, 674,
	706, 698, 697, 729, 690, 722, 723, 693, 725, 726, 679, 711, 712, 703, 702, 734, 697, 696, 728, 686, 718, 719, 692, 724, 725, 678,
	677, 709, 699, 698, 730, 696, 695, 727, 685, 717, 718, 687, 719, 720, 691, 723, 724, 673, 704, 736, 694, 726, 727, 681, 713, 714,
	683, 715, 716, 679, 678, 710, 704, 703, 735, 680, 712, 713, 689, 721, 722, 702, 701, 733, 708, 707, 739, 716, 748, 749, 707, 706,
	738, 730, 729, 761, 722, 754, 755, 725, 757, 758, 711, 743, 744, 735, 734, 766, 729, 728, 760, 718, 750, 751, 724, 756, 757, 710,
	709, 741, 731, 730, 762, 728, 727, 759, 717, 749, 750, 719, 751, 752, 723, 755, 756, 705, 736, 768, 726, 758, 759, 713, 745, 746,
	715, 747, 748, 711, 710, 742, 736, 735, 767, 712, 744, 745, 721, 753, 754, 734, 733, 765, 733, 732, 764, 714, 746, 747, 706, 705,
	737, 720, 752, 753, 732, 731, 763, 709, 708, 740, 743, 775, 776, 767, 766, 798, 761, 760, 792, 750, 782, 783, 756, 788, 789, 742,
	741, 773, 763, 762, 794, 760, 759, 791, 749, 781, 782, 751, 783, 784, 755, 787, 788, 737, 768, 800, 758, 790, 791, 745, 777, 778,
	747, 779, 780, 743, 742, 774, 768, 767, 799, 744, 776, 777, 753, 785, 786, 766, 765, 797, 765, 764, 796, 746, 778, 779, 738, 737,
	769, 752, 784, 785, 764, 763, 795, 741, 740, 772, 740, 739, 771, 748, 780, 781, 739, 738, 770, 762, 761, 793, 754, 786, 787, 757,
	789, 790, 792, 791, 823, 781, 813, 814, 783, 815, 816, 787, 819, 820, 769, 800, 832, 790, 822, 823, 777, 809, 810, 779, 811, 812,
	775, 774, 806, 800, 799, 831, 776, 808, 809, 785, 817, 818, 798, 797, 829, 797, 796, 828, 778, 810, 811, 770, 769, 801, 784, 816,
	817, 796, 795, 827, 773, 772, 804, 772, 771, 803, 780, 812, 813, 771, 770, 802, 794, 793, 825, 786, 818, 819, 789, 821, 822, 775,
	807, 808, 799, 798, 830, 793, 792, 824, 782, 814, 815, 788, 820, 821, 774, 773, 805, 795, 794, 826, 832, 831, 863, 808, 840, 841,
	817, 849, 850, 830, 829, 861, 829, 828, 860, 810, 842, 843, 802, 801, 833, 816, 848, 849, 828, 827, 859, 805, 804, 836, 804, 803,
	835, 812, 844, 845, 803, 802, 834, 826, 825, 857, 818, 850, 851, 821, 853, 854, 807, 839, 840, 831, 830, 862, 825, 824, 856, 814,
	846, 847, 820, 852, 853, 806, 805, 837, 827, 826, 858, 824, 823, 855, 813, 845, 846, 815, 847, 848, 819, 851, 852, 801, 832, 864,
	822, 854, 855, 809, 841, 842, 811, 843, 844, 807, 806, 838, 860, 859, 891, 837, 836, 868, 836, 835, 867, 844, 876, 877, 835, 834,
	866, 858, 857, 889, 850, 882, 883, 853, 885, 886, 839, 871, 872, 863, 862, 894, 857, 856, 888, 846, 878, 879, 852, 884, 885, 838,
	837, 869, 859, 858, 890, 856, 855, 887, 845, 877, 878, 847, 879, 880, 851, 883, 884, 833, 864, 896, 854, 886, 887, 841, 873, 874,
	843, 875, 876, 839, 838, 870, 864, 863, 895, 840, 872, 873, 849, 881, 882, 862, 861, 893, 861, 860, 892, 842, 874, 875, 834, 833,
	865, 848, 880, 881, 882, 914, 915, 885, 917, 918, 871, 903, 904, 895, 894, 926, 889, 888, 920, 878, 910, 911, 884, 916, 917, 870,
	869, 901, 891, 890, 922, 888, 887, 919, 877, 909, 910, 879, 911, 912, 883, 915, 916, 865, 896, 928, 886, 918, 919, 873, 905, 906,
	875, 907, 908, 871, 870, 902, 896, 895, 927, 872, 904, 905, 881, 913, 914, 894, 893, 925, 893, 892, 924, 874, 906, 907, 866, 865,
	897, 880, 912, 913, 892, 891, 923, 869, 868, 900, 868, 867, 899, 876, 908, 909, 867, 866, 898, 890, 889, 921, 916, 948, 949, 902,
	901, 933, 923, 922, 954, 920, 919, 951, 909, 941, 942, 911, 943, 944, 915, 947, 948, 897, 928, 960, 919, 918, 950, 905, 937, 938,
	907, 939, 940, 902, 934, 935, 928, 927, 959, 904, 936, 937, 913, 945, 946, 926, 925, 957, 925, 924, 956, 906, 938, 939, 898, 897,
	929, 912, 944, 945, 924, 923, 955, 901, 900, 932, 900, 899, 931, 908, 940, 941, 899, 898, 930, 922, 921, 953, 914, 946, 947, 917,
	949, 950, 903, 935, 936, 927, 926, 958, 921, 920, 952, 910, 942, 943, 951, 950, 982, 937, 969, 970, 939, 971, 972, 934, 966, 967,
	960, 959, 991, 936, 968, 969, 945, 977, 978, 958, 957, 989, 957, 956, 988, 938, 970, 971, 930, 929, 961, 944, 976, 977, 956, 955,
	987, 933, 932, 964, 932, 931, 963, 940, 972, 973, 931, 930, 962, 954, 953, 985, 946, 978, 979, 950, 949, 981, 935, 967, 968, 959,
	958, 990, 953, 952, 984, 942, 974, 975, 948, 980, 981, 933, 965, 966, 955, 954, 986, 952, 951, 983, 941, 973, 974, 943, 975, 976,
	947, 979, 980, 929, 960, 992 };
	*/

	/*
	UE_LOG(LogTemp, Error,
		TEXT("TEST: vertArrayFromBlender.Num() = %d (expected 1950)"), vertArrayFromBlender.Num());
	*/

	/*
	for (int32 vertIx = 0; vertIx < vertArrayFromBlender.Num(); ++vertIx) {
		//UE_LOG(LogTemp, Error, TEXT("TEST: vertIx = %d"), vertIx);

		FVector blendVert = vertArrayFromBlender[vertIx];
		FVector unrealVert = FVector(blendVert.X, blendVert.Z, blendVert.Y);

		AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, 5.0f * unrealVert, vertices, newIndices);
	}
	*/

	// Curling tris are added below



#endif

	/*
	v 1.000000 -1.000000 -1.000000
	v 1.000000 -1.000000 1.000000
	v -1.000000 -1.000000 1.000000
	v -1.000000 -1.000000 -1.000000
	v 1.000000 1.000000 -0.999999
	v 0.999999 1.000000 1.000001
	v -1.000000 1.000000 1.000000
	v -1.000000 1.000000 -1.000000
	*/


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



	//int32 newIndex2 = verts2Dim[subtreeNo].Verts.Add(relTrafo.GetLocation());

#if 0 /* Tris for normal cube, pivot in the centre */
	// Bottom!
	tris2Dim[subtreeNo].Ints.Add(newIndices[0]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[2]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[1]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[3]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[1]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[2]);

	// Front(facing me)!
	tris2Dim[subtreeNo].Ints.Add(newIndices[0]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[1]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[5]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[5]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[4]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[0]);

	// Left!
	tris2Dim[subtreeNo].Ints.Add(newIndices[2]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[0]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[4]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[4]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[6]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[2]);

	// Top!
	tris2Dim[subtreeNo].Ints.Add(newIndices[3]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[2]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[6]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[6]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[7]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[3]);

	// Right!
	tris2Dim[subtreeNo].Ints.Add(newIndices[1]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[3]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[7]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[7]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[5]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[1]);

	// Back (facing away from me)!
	tris2Dim[subtreeNo].Ints.Add(newIndices[6]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[4]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[5]);

	tris2Dim[subtreeNo].Ints.Add(newIndices[5]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[7]);
	tris2Dim[subtreeNo].Ints.Add(newIndices[6]);
#else

	/* */
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
	/**/




	/*
	UE_LOG(LogTemp, Error,
	TEXT("TEST: triArrayFromBlender.Num() = %d (from %d verts)"), triArrayFromBlender.Num(), vertArrayFromBlender.Num());
	*/

	//for (int32 triIx = 0; triIx < triArrayFromBlender.Num(); ((triIx % 3 == 2) ? --triIx : triIx += 2)) {
#if 0
	for (int32 triIx = 0; triIx < triArrayFromBlender.Num(); ++triIx) {
		//for (int32 triIx = 0; triIx < triArrayFromBlender.Num() / 3; ++triIx) {

			//UE_LOG(LogTemp, Error, TEXT("TEST: triIx = %d, triArrayFromBlender[triIx]=%d"), triIx, triArrayFromBlender[triIx]);

		tris2Dim[subtreeNo].Ints.Add(newIndices[triArrayFromBlender[triIx] - 1]);

		/*
		// Seems to be left (or right) side bot-triangle
		tris2Dim[subtreeNo].Ints.Add(newIndices[1]); // Was 1 3 0, try 1 0 3
		tris2Dim[subtreeNo].Ints.Add(newIndices[0]);
		tris2Dim[subtreeNo].Ints.Add(newIndices[3]);
		*/

	}
#endif





#endif


	/*
	normals.Add(FVector(-1, 0, 0));
	normals.Add(FVector(-1, 0, 0));
	normals.Add(FVector(-1, 0, 0));
	normals.Add(FVector(-1, 0, 0));
	*/

	//Normal test 2(bad, inner light)
	/*
	normals.Add(FVector(-1, -1, -1));
	normals.Add(FVector(-1, 1, -1));
	normals.Add(FVector(1, -1, -1));
	normals.Add(FVector(1, 1, -1));
	normals.Add(FVector(-1, -1, 1));
	normals.Add(FVector(-1, 1, 1));
	normals.Add(FVector(1, -1, 1));
	normals.Add(FVector(1, 1, 1));
	*/

	//Normal test 3 ()
	/*
	normals.Add(FVector(0, 0, -1));
	normals.Add(FVector(0, 0, -1));
	normals.Add(FVector(0, 0, -1));
	normals.Add(FVector(0, 0, -1));
	normals.Add(FVector(0, 0, 1));
	normals.Add(FVector(0, 0, 1));
	normals.Add(FVector(0, 0, 1));
	normals.Add(FVector(0, 0, 1));
	*/


#if 1 /* Cube UV */
	/* Horizontal texture
		UV0.Add(FVector2D(0.0f, 0.0f));
		UV0.Add(FVector2D(0.0f, 1.0f));
		UV0.Add(FVector2D(1.0f, 0.0f));
		UV0.Add(FVector2D(1.0f, 1.0f));

		UV0.Add(FVector2D(0.0f, 0.0f));
		UV0.Add(FVector2D(0.0f, 1.0f));
		UV0.Add(FVector2D(1.0f, 0.0f));
		UV0.Add(FVector2D(1.0f, 1.0f));
		*/

		// Vertical texture
	UV0.Add(FVector2D(0.0f, 1.0f));
	UV0.Add(FVector2D(0.0f, 1.0f));
	UV0.Add(FVector2D(0.0f, 1.0f));
	UV0.Add(FVector2D(0.0f, 1.0f));

	UV0.Add(FVector2D(0.0f, 0.0f));
	UV0.Add(FVector2D(0.0f, 0.0f));
	UV0.Add(FVector2D(0.0f, 0.0f));
	UV0.Add(FVector2D(0.0f, 0.0f));
#else /* Curling stone UV */

	// x is -4 to 4, so try to make u 0 to 1 accordingly
	// z is similar,  so try to make v 0 to 1 accordingly

	FVector vert;
	for (int32 vertIx = 0; vertIx < vertArrayFromBlender.Num(); ++vertIx) {

		vert = vertArrayFromBlender[vertIx];

		/*
		if (vert.Z > 0.0) {
			UV0.Add(FVector2D(0.0f, 0.0f));
		}
		else {
			UV0.Add(FVector2D(0.0f, 1.0f));
		}
		*/

		/*
		// If z<0, u must be >0.5. If z>0, v must be <0.5.
		//float uValue = (vert.X + 4.0f) / 8.0f;
		float uValue = 0.0f;
		// If z<0, v must be >0.5. If z>0, v must be <0.5.
		float vValue = (vert.Z - 4.0f) / -8.0f;
		UV0.Add(FVector2D(uValue, vValue));
		*/

		/*
		// Maybe it becomes horizontal because I rotate at "import". Try to "rotate" uv as well...
		float vValue = 0.0f;
		// If z<0, v must be >0.5. If z>0, v must be <0.5.
		float uValue = (vert.Z - 4.0f) / -8.0f;
		UV0.Add(FVector2D(uValue, vValue));
		*/

		float uValue = 0.0f;
		// If z<0, v must be >0.5. If z>0, v must be <0.5.
		float vValue = (vert.Y + 4.0f) / 8.0f;
		UV0.Add(FVector2D(uValue, vValue));

	}

	/*
	FVector vert0(0.000000, 0.000000, -0.932369);
	FVector vert1(-0.181896, 0.000000, -0.914454);
	FVector vert2(-0.356802, 0.000000, -0.861396);
	FVector vert3(-0.517996, 0.000000, -0.775236);
	FVector vert4(-0.659284, 0.000000, -0.659284);
	FVector vert5(-0.775236, 0.000000, -0.517996);
	FVector vert6(-0.861396, 0.000000, -0.356802);
	FVector vert7(-0.914454, 0.000000, -0.181896);
	FVector vert8(-0.932369, 0.000000, -0.000000);
	FVector vert9(-0.914454, 0.000000, 0.181896);
	FVector vert10(-0.861396, 0.000000, 0.356802);
	FVector vert11(-0.775236, 0.000000, 0.517996);
	FVector vert12(-0.659284, 0.000000, 0.659284);
	FVector vert13(-0.517996, 0.000000, 0.775236);
	*/
#endif


	/*
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(-CUBE_SIZE/2, -CUBE_SIZE/2, -CUBE_SIZE/2), vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(-CUBE_SIZE/2, CUBE_SIZE/2, -CUBE_SIZE/2), vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(CUBE_SIZE/2, -CUBE_SIZE/2, -CUBE_SIZE/2), vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(CUBE_SIZE/2, CUBE_SIZE/2, -CUBE_SIZE/2), vertices, newIndices);

	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(-CUBE_SIZE/2, -CUBE_SIZE/2, CUBE_SIZE/2), vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(-CUBE_SIZE/2, CUBE_SIZE/2, CUBE_SIZE/2), vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(CUBE_SIZE/2, -CUBE_SIZE/2, CUBE_SIZE/2), vertices, newIndices);
	AddVertex(treeLevel, subtreeNo, verts2Dim, baseTrafo, FVector(CUBE_SIZE/2, CUBE_SIZE/2, CUBE_SIZE/2), vertices, newIndices);
	*/


#if 0 /* Did tangents or vertexColors fix the texture? */
	tangents.Add(FRuntimeMeshTangent(0, 1, 0));
	tangents.Add(FRuntimeMeshTangent(0, 1, 0));
	tangents.Add(FRuntimeMeshTangent(0, 1, 0));
	tangents.Add(FRuntimeMeshTangent(0, 1, 0));
#endif

}


/*
void AThing::Add(TArray<FTransform> trafos) {

	UE_LOG(LogTemp, Warning, TEXT("AThing::Add(...Trafos...) called, add %d stuff"), trafos.Num());

	// TODO: Add to EXISTING group, if there is one!
	group.Append(trafos);
}
*/



