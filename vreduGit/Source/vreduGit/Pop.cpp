// Fill out your copyright notice in the Description page of Project Settings.

#include "Pop.h"
#include "Thing.h"

// Sets default values
APop::APop()
{
	UE_LOG(LogTemp, Warning, TEXT("APop constructor called"));
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TEST, temporary!
	init2();
	//init(0, FTransform(FVector(0, 0, 0)));

}

void APop::init2() {

	//mesh = NewObject<USceneComponent>(this, TEXT("RootSceneComponent"));
	mesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Pop mesh test"));
	RootComponent = mesh;

	BuildMesh();

	//const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObjCube(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	//meshCube = MeshObjCube.Object;

	//mesh->SetStaticMesh(meshCube);

}

void APop::init(AThing* thing, FTransform trafo) {
	UE_LOG(LogTemp, Warning, TEXT("APop::init called, this=%p"), this);

	thingRef = thing;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	//RootComponent = NewObject<USceneComponent>(this, TEXT("RootSceneComponent"));
	//mesh = NewObject<USceneComponent>(this, TEXT("RootSceneComponent"));


#if 1 /* Got code from old implementation */
	//
	// Setup the mesh as root
	//
	//mesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Pop RMC root"));

	/* Testing SM instead atm...
	mesh = NewObject< URuntimeMeshComponent >(this, TEXT("Pop RMC root"));
	*/
	//mesh = NewObject< UStaticMeshComponent >(this, TEXT("Pop RMC root"));

	
	
	RootComponent = mesh;
	mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	mesh->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);  // Try also PhysicsOnly
	mesh->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Block);

#if 1 /* TEST, reinsert physics! */
	mesh->SetSimulatePhysics(true);
#else
	mesh->SetSimulatePhysics(false);
#endif

	/*
	mesh->SetLinearDamping(0.15);  // Not active, because Tick overwrites this value anyway with a speed-dependant value
	mesh->SetAngularDamping(0.2);
	*/
#endif

	mesh->SetEnableGravity(true);
	this->GetRootPrimitiveComponent()->SetEnableGravity(true);
	//mesh->

	if (IsRootComponentMovable()) {
		UE_LOG(LogTemp, Warning, TEXT("APop::init, this=%p, IsRootComponentMovable TRUE"), this);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("APop::init, this=%p, IsRootComponentMovable FALSE"), this);
	}

	mesh->SetMobility(EComponentMobility::Movable);



	// Location setting experiment
	FVector loc = GetActorTransform().GetLocation();
	UE_LOG(LogTemp, Warning, TEXT("APop::init (BEFORE setting location, loc X=%f Y=%f Z=%f"), loc.X, loc.Y, loc.Z);

	this->SetActorLocation(trafo.GetLocation());

	loc = GetActorTransform().GetLocation();
	UE_LOG(LogTemp, Warning, TEXT("APop::init (AFTER setting location, loc X=%f Y=%f Z=%f"), loc.X, loc.Y, loc.Z);

#if 0
	// Box collision experiment
	box = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass());
	box->SetRelativeTransform(trafo);
	box->SetBoxExtent(FVector(100.0, 100.0, 100.0));
	box->RegisterComponent();
	//BoxComponent->SetupAttachment(GetRootComponent());

#if 1
	box->SetupAttachment(GetRootComponent());
#endif
#if 0
	RootComponent = BoxComponent;
	mesh->SetupAttachment(GetRootComponent());
#endif

	// More on box coll.
	//CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("TestCollision"));
	//CollisionMesh->SetBoxExtent(FVector(200.f, 200.f, 96.f));
	box->bDynamicObstacle = true;
	//CollisionMesh->SetupAttachment(GetRootComponent());
	// bGenerateOverlapEvents
	box->bGenerateOverlapEvents = true;

	// SetCollisionResponseToAllChannels   ECR_Overlap。
	box->SetCollisionResponseToAllChannels(ECR_Overlap);
	/*CollisionMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CollisionMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetSimulatePhysics(true);*/

	// Generate Overlap Events
	FScriptDelegate DelegateBegin;
	DelegateBegin.BindUFunction(this, "OnTestOverlapBegin");
	box->OnComponentBeginOverlap.Add(DelegateBegin);
	FScriptDelegate DelegateEnd;
	DelegateEnd.BindUFunction(this, "OnTestOverlapEnd");
	box->OnComponentEndOverlap.Add(DelegateEnd);


	// More...
	//BoxComponent->bUseComplexAsSimpleCollision = false;
	//BoxComponent->

	//Mesh->bGenerateHitEvents = true;
	mesh->SetNotifyRigidBodyCollision(true);
	box->SetNotifyRigidBodyCollision(true);

	// And more...
	//mesh->WakeRigidBody();
#endif

}

// Called when the game starts or when spawned
void APop::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("APop::BeginPlay called, this=%p"), this);

	Super::BeginPlay();
	
}

// Called every frame
void APop::Tick(float DeltaTime)
{
	FVector loc = GetActorTransform().GetLocation();

	UE_LOG(LogTemp, Warning, TEXT("APop::Tick called, this=%p, loc: X=%f, Y=%f, Z=%f"),
		   this, loc.X, loc.Y, loc.Z);


	Super::Tick(DeltaTime);

	//SetActorLocation(FVector(loc.X, loc.Y + 1.0, loc.Z));
}

FString APop::ToString() {

	FVector loc = GetActorTransform().GetLocation();

	FString str = FString::Printf(TEXT("Pop points to thing with id <%s>, loc X=%f Y=%f Z=%f"), *(thingRef->name), loc.X, loc.Y, loc.Z);

	//FString str = FString::Printf(TEXT("Id: %s\n  No. of atoms: %d"), *name, CountAtoms());


	return str;
}




void APop::BuildMesh()
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


#if 0 /* RMC code from old vred */

//
// Build mesh section and also add collision grab boxes
//
void APop::BuildMesh(/* thing, FTransform baseTrafo */) {

	TArray<FVector> vertices;
	TArray<int32> Triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FRuntimeMeshTangent> tangents;
	TArray<FColor> vertexColors;

	UE_LOG(LogTemp, Warning, TEXT("APop::BuildMesh called, thingRef has the name: %s"), *thingRef->name);


	// Build combined mesh data for the full tree of the Thing that this Pop instantiates
	// Q: Do the verts positions depend on the trafo of this Pop?
	// A: No!
	// Q: What is the PURPOSE of the trafo of this Pop?
	// A: The trafo is the world position of the Pop. When it changes, the verts position won't change, since the verts are positioned RELATIVE TO THE Pop!
	//    If the root thing is an ATOM, the ORIGIN will be at the origin of that cube mesh (which in turn lives at the same position as the Pop).
	//	  If the root thing is a PARENT, it has sub-trafo:s of each of its children
	TArray<FVertexArray> verts2Dim;
	TArray<FInt32Array> tris2Dim;
	TArray<FTransform> collisionCubePositions;
	thingRef->ComputeMeshData(verts2Dim, tris2Dim, vertices, Triangles, normals, UV0, vertexColors, tangents, collisionCubePositions);

	UE_LOG(LogTemp, Warning, TEXT("APop::BuildMesh: ComputeMeshData gave back collisionCubePositions.Num()==%d,  verts2Dim.Num()=%d,  tris2Dim.Num()=%d"),
		collisionCubePositions.Num(), verts2Dim.Num(), tris2Dim.Num());

	// The mesh may already have data. Remove it
	Mesh->ClearAllMeshSections();

	/* Removing 180919 when trying to get house parts to work again
	Mesh->ClearCollisionConvexMeshes();
	*/

	// Add the new mesh data
	//Mesh->CreateMeshSection(0, vertices, Triangles, normals, UV0, vertexColors, tangents, false, EUpdateFrequency::Frequent);
	for (int i = 0; i < verts2Dim.Num(); ++i) {


		/*
		RuntimeMeshComp->CreateMeshSection(SectionIndex, *Vertices.GetVertices(), *Triangles.GetIndices(),
		bShouldCreateCollision, EUpdateFrequency::Infrequent, ESectionUpdateFlags::MoveArrays);
		*/
		//					ix      vert    tri     createColl  freq   MoveArrays

		//                  ix      vert    tri     norm  UV  colors   tangents    createColl    freq
#if 1
		//Mesh->CreateMeshSection(i, verts2Dim[i].Verts, tris2Dim[i].Ints, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FRuntimeMeshTangent>(), false);

		Mesh->CreateMeshSection(i, verts2Dim[i].Verts, tris2Dim[i].Ints, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FRuntimeMeshTangent>(), false);
#else /* TEST: UV mapping. TODO: Don't use the same UV array for all mesh sections! .......................................................................................... */
		Mesh->CreateMeshSection(i, verts2Dim[i].Verts, tris2Dim[i].Ints, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FRuntimeMeshTangent>(), false);

		// Another try, WITHOUT UV and everything!
		//Mesh->CreateMeshSection(i, verts2Dim[i].Verts, tris2Dim[i].Ints,
		//	false, EUpdateFrequency::Infrequent, ESectionUpdateFlags::MoveArrays);
		/*
		RuntimeMeshComp->CreateMeshSection(i, *Vertices.GetVertices(), *Triangles.GetIndices(),
							bShouldCreateCollision, EUpdateFrequency::Infrequent, ESectionUpdateFlags::MoveArrays);
		*/

		// Try with everything, including UV. WORKS!!
		//Mesh->CreateMeshSection(i, verts2Dim[i].Verts, tris2Dim[i].Ints, normals, UV0, vertexColors, tangents, false);


#endif
		Mesh->SetMaterial(i, MaterialInstance);

		/* Removing 180919 when trying to get house parts to work again
		Mesh->AddCollisionConvexMesh(verts2Dim[i].Verts);
		*/
	}

	//Mesh->CreateMeshSection(0, vertices, Triangles /*, TArray<FVector> */);


	//
	// Other things needed to setup, e.g. to get physics simulation working
	//

	// NEW TEST (just to see if there might be an old collision mesh that messes thing up)
	/*
	Mesh->ClearCollisionConvexMeshes();  // TODO: maybe use ClearAllMeshCollisionSections instad..............

	Mesh->AddCollisionConvexMesh(verts2Dim[0].Verts); // Todo, I should probably do this for 0, 1, 2, ... Num()
	*/

	//Mesh->RegisterComponent();

	//Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	//Mesh->BodyInstance.SetResponseToAllChannels(ECR_Block);

	AddGrabBoxes(collisionCubePositions);


}



















void APop::CreateTriangle()
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


	////Mesh->CreateMeshSection(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true, EUpdateFrequency::Frequent);
	// For a moment, just pass verts and tris
	//Mesh->CreateMeshSection(0, vertices, Triangles, TArray<FVector>);



	///Mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);

	// TEST false, TEMPORARY FOR AddCollisionConvexMesh
	//mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, false);

	// Enable collision data
	//  Seems to be private in RuntimeMeshComponent...
	//Mesh->ContainsPhysicsTriMeshData(true);


	//Mesh->AddCollisionConvexMesh(vertices);


	// TEST override mass
	//mesh->GetBodyInstance()->bOverrideMass = true;

	/*
	// Change Mass
	float Mass = Mesh->GetMass();
	///UE_LOG(LogTemp, Warning, TEXT(">>>> Starting Mass = %s"), *FString::SanitizeFloat(Mass));
	Mesh->GetBodyInstance()->bOverrideMass = true;
	//mesh->SetMassOverrideInKg(NAME_None, this->NewScale);
	Mesh->SetMassOverrideInKg(NAME_None, 100.0f, true);
	Mesh->GetBodyInstance()->UpdateMassProperties();
	Mass = Mesh->GetMass();
	///UE_LOG(LogTemp, Warning, TEXT(">>>> New Mass = %s"), *FString::SanitizeFloat(Mass));
	*/



	// TEST
	Mesh->RegisterComponent();
	//mesh->FinishAndRegisterComponent();
	// TEST (nope, made mesh invisible)
	//FinishAndRegisterComponent(mesh);


	// Try (dupl code)

	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	//mesh->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//Block All!
	//////Mesh->BodyInstance.SetResponseToAllChannels(ECR_Block);

	// TRY THIS
	//mesh->SetCollisionProfileName(TEXT("OverlapAll"));
	/**/
}



#endif

