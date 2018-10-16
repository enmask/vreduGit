// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/PhysicsEngine/BodySetup.h"
#include "RuntimeMeshComponent.h"
#include "Thing.generated.h"


// Basic constants
#define CUBE_SIZE 60


USTRUCT()
struct FVertexArray
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY()
		TArray<FVector> Verts;

	FVertexArray()
	{
	}

	void Log() {

		for (int i = 0; i < Verts.Num(); ++i) {
			FVector Vert = Verts[i];
			UE_LOG(LogTemp, Warning, TEXT("FVertexArray::Log(), i=%d   X=%f  Y=%f  Z=%f"), i, Vert.X, Vert.Y, Vert.Z);
		}
	}

};

USTRUCT()
struct FInt32Array
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY()
		TArray<int32> Ints;

	FInt32Array()
	{
	}

	void Log() {

		for (int i = 0; i < Ints.Num(); ++i) {
			UE_LOG(LogTemp, Warning, TEXT("FInt32Array::Log(), i=%d   the tri value: %d"), i, Ints[i]);
		}
	}
};

UCLASS()
class VREDUGIT_API AThing : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AThing();

	void init(FString theName);


	// Add a group of transform instances to this Thing. Combine the new group with any existing group!
	//void Add(TArray<FTransform> trafos);

	// Add a group of things to this thing
	//Add(TArray<AThing> thingsToAdd));

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Compute data for the triangles making up the whole mesh of a Thing tree
	void ComputeMeshData(TArray<FVertexArray>& verts2Dim, TArray<FInt32Array>& tris2Dim,
		TArray<FVector>& vertices, TArray<int32>& Triangles,
		TArray<FVector>& normals, TArray<FVector2D>& UV0,
		TArray<FColor>& vertexColors, TArray<FRuntimeMeshTangent>& tangents,
		TArray<FTransform>& collisionCubePositions);
private:
	void ComputeMeshDataAux(int32 treeLevel, int32 subtreeNo,
		TArray<FVertexArray>& verts2DimArray, TArray<FInt32Array>& int2DimArray,
		FTransform baseTrafo,
		TArray<FVector>& vertices, TArray<int32>& Triangles,
		TArray<FVector>& normals, TArray<FVector2D>& UV0,
		TArray<FColor>& vertexColors, TArray<FRuntimeMeshTangent>& tangents,
		TArray<FTransform>& collisionCubePositions);
	void AddMeshDataForOneAtom(int32 treeLevel, int32 subtreeNo,
		TArray<FVertexArray>& verts2DimArray, TArray<FInt32Array>& int2DimArray,
		FTransform baseTrafo,
		TArray<FVector>& vertices, TArray<int32>& Triangles,
		TArray<FVector>& normals, TArray<FVector2D>& UV0,
		TArray<FColor>& vertexColors, TArray<FRuntimeMeshTangent>& tangents);
	void AddVertex(int32 treeLevel, int32 subtreeNo, TArray<FVertexArray>& verts2DimArray,
		FTransform baseTrafo, FVector origLocation, TArray<FVector>& vertices, TArray<int32>& newIndices);

public:

	// Name
	FString name;

	// Add a sub-thing
	void Add(AThing* subThing, FTransform subThingRelTrafo);

	TArray<AThing*> subThings;
	TArray<FTransform> subThingRelTrafos;

	void Log2DimVertsArray(TArray<FVertexArray> verts2Dim);
	void Log2DimIntsArray(TArray<FInt32Array> ints2Dim);


	/*
	USTRUCT()
		struct FFlowerField
	{
		GENERATED_USTRUCT_BODY()

			UPROPERTY()
			TArray<FFlowerStruct> Flowers;

		FFlowerField()
		{
		}
	};
	*/



	/*
	//All Flower Fields on The Island
	TArray<FFlowerField> FlowerFields;
	*/

};






#if 0 /* The auto-generated h file */
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Thing.generated.h"

UCLASS()
class VREDUGIT_API AThing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThing();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
#endif