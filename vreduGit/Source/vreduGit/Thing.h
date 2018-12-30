// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Math/Transform.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/PhysicsEngine/BodySetup.h"
#include "RuntimeMeshComponent.h"
#include "Thing.generated.h"

//DECLARE_LOG_CATEGORY_EXTERN(LogVredu, Log, All);

// Basic constants
#define CUBE_SIZE 60
#define CUBEMESH_SIZE 20


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

USTRUCT()
struct FColorArray
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		TArray<FColor> Colors;

	FColorArray()
	{
	}

	void Log() {

		for (int i = 0; i < Colors.Num(); ++i) {
			FColor color = Colors[i];
			UE_LOG(LogTemp, Warning, TEXT("FColorArray::Log(), i=%d   color=%s"), i, *color.ToString());
		}
	}

};


USTRUCT()
struct FTrafoArray
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		TArray<FTransform> Trafos;

	FTrafoArray()
	{
	}

	void Log() {

		for (int i = 0; i < Trafos.Num(); ++i) {
			FTransform trafo = Trafos[i];
			UE_LOG(LogTemp, Warning, TEXT("FTrafoArray::Log(), i=%d   trafo=%s"), i, *trafo.ToString());
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Compute data for the triangles making up the whole mesh of a Thing tree
	void ComputeMeshData(TArray<FVertexArray>& verts2Dim, TArray<FInt32Array>& tris2Dim,
						 TArray<FColorArray>& colors2Dim, TArray<FTrafoArray>& collisions2Dim,
						 TArray<FVector>& vertices, TArray<int32>& Triangles,
						 TArray<FVector>& normals, TArray<FVector2D>& UV0,
						 TArray<FColor>& vertexColors, TArray<FRuntimeMeshTangent>& tangents,
						 TArray<FTransform>& collisionCubePositions);
private:

	int CountAtoms();


	void ComputeMeshDataAux(int32 treeLevel, int32 subtreeNo,
		TArray<FVertexArray>& verts2Dim, TArray<FInt32Array>& int2Dim,
		TArray<FColorArray>& colors2Dim, TArray<FTrafoArray>& collisions2Dim,
		FTransform baseTrafo,
		TArray<FVector>& vertices, TArray<int32>& Triangles,
		TArray<FVector>& normals, TArray<FVector2D>& UV0,
		TArray<FColor>& vertexColors, TArray<FRuntimeMeshTangent>& tangents,
		TArray<FTransform>& collisionCubePositions);
	void AddMeshDataForOneAtom(int32 treeLevel, int32 subtreeNo,
		TArray<FVertexArray>& verts2Dim, TArray<FInt32Array>& int2Dim,
		TArray<FColorArray>& colors2Dim, TArray<FTrafoArray>& collisions2Dim,
		FTransform baseTrafo,
		TArray<FVector>& vertices, TArray<int32>& Triangles,
		TArray<FVector>& normals, TArray<FVector2D>& UV0,
		TArray<FColor>& vertexColors, TArray<FRuntimeMeshTangent>& tangents);
	void AddVertex(int32 treeLevel, int32 subtreeNo, TArray<FVertexArray>& verts2Dim,
				   TArray<FColorArray>& colors2Dim, TArray<FTrafoArray>& collisions2Dim,
				   FTransform baseTrafo, FVector origLocation,
				   TArray<FVector>& vertices, TArray<int32>& newIndices);

public:

	// Name
	FString name;

	// Add a sub-thing
	void Add(AThing* subThing, FTransform subThingRelTrafo, FString subThingRole);

	TArray<AThing*> subThings;
	TArray<FTransform> subThingRelTrafos;
	TArray<FString> subThingRoles;

	void Log2DimVertsArray(TArray<FVertexArray> verts2Dim);
	void Log2DimIntsArray(TArray<FInt32Array> ints2Dim);
	void Log2DimColorArray(TArray<FColorArray> colors2Dim);

	FString ToString();

};
