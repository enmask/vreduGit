// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorMouse.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
AActorMouse::AActorMouse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("ActorMouse mesh"));
	//RootComponent = mesh;

	//CustomMeshComponent = CreateDefaultSubobject(TEXT("Test Component"));
	mesh->AttachTo(RootComponent);

	BuildCube();

	mesh->OnBeginCursorOver.AddDynamic(this, &AActorMouse::CustomOnBeginMouseOver);

}

// Called when the game starts or when spawned
void AActorMouse::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorMouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("debug works!"));
	//}

}


void AActorMouse::CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("ActorMouse Mouse Over"));
	}
}


void AActorMouse::BuildCube()
{

	/* To build... */

	TArray<FVector> vertices;
	vertices.Add(FVector(0, 0, 0));
	vertices.Add(FVector(0, 100, 0));
	vertices.Add(FVector(0, 0, 100));
	vertices.Add(FVector(0, 100, 100));

	vertices.Add(FVector(100, 0, 0));
	vertices.Add(FVector(100, 100, 0));
	vertices.Add(FVector(100, 0, 100));
	vertices.Add(FVector(100, 100, 100));



	TArray<int32> Triangles;
	// Side 1 (front)
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

	Triangles.Add(3);
	Triangles.Add(2);
	Triangles.Add(1);

	// Side 2 (bottom)
	Triangles.Add(0);
	Triangles.Add(5);
	Triangles.Add(1);

	Triangles.Add(5);
	Triangles.Add(0);
	Triangles.Add(4);

	// Side 3 (left)
	Triangles.Add(2);
	Triangles.Add(4);
	Triangles.Add(0);

	Triangles.Add(4);
	Triangles.Add(2);
	Triangles.Add(6);

	// Side 4 (top)
	Triangles.Add(3);
	Triangles.Add(6);
	Triangles.Add(2);

	Triangles.Add(6);
	Triangles.Add(3);
	Triangles.Add(7);

	// Side 5 (right)
	Triangles.Add(1);
	Triangles.Add(7);
	Triangles.Add(3);

	Triangles.Add(7);
	Triangles.Add(1);
	Triangles.Add(5);

	// Side 6 (back)
	Triangles.Add(6);
	Triangles.Add(5);
	Triangles.Add(4);

	Triangles.Add(5);
	Triangles.Add(6);
	Triangles.Add(7);


	TArray<FVector> normals;
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	//normals.Add(FVector(1, 0, 0));
	//normals.Add(FVector(1, 0, 0));
	//normals.Add(FVector(1, 0, 0));
	//normals.Add(FVector(1, 0, 0));

	TArray<FVector2D> UV0;
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 10));
	UV0.Add(FVector2D(10, 10));

	//UV0.Add(FVector2D(0, 0));
	//UV0.Add(FVector2D(10, 0));
	//UV0.Add(FVector2D(0, 10));
	//UV0.Add(FVector2D(10, 10));

	TArray<FRuntimeMeshTangent> tangents;

	tangents.Add(FRuntimeMeshTangent(0, 1, 0));
	tangents.Add(FRuntimeMeshTangent(0, 1, 0));
	tangents.Add(FRuntimeMeshTangent(0, 1, 0));
	tangents.Add(FRuntimeMeshTangent(0, 1, 0));


	//tangents.Add(FProcMeshTangent(0, 1, 0));
	//tangents.Add(FProcMeshTangent(0, 1, 0));
	//tangents.Add(FProcMeshTangent(0, 1, 0));
	//tangents.Add(FProcMeshTangent(0, 1, 0));

	TArray<FColor> vertexColors;

	vertexColors.Add(FColor::White);
	vertexColors.Add(FColor::White);
	vertexColors.Add(FColor::White);
	vertexColors.Add(FColor::White);

	vertexColors.Add(FColor::White);
	vertexColors.Add(FColor::White);
	vertexColors.Add(FColor::White);
	vertexColors.Add(FColor::White);

	UE_LOG(LogTemp, Warning, TEXT("APop::BuildMesh, will call CreateMeshSection"));


	// For a moment, just pass verts and tris
	mesh->CreateMeshSection(0, vertices, Triangles,
		normals, UV0, vertexColors,
		tangents, true, EUpdateFrequency::Frequent);

}