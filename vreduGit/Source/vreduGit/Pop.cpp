// Fill out your copyright notice in the Description page of Project Settings.

#include "Pop.h"
#include "vreduGameMode.h"
#include "Thing.h"
#include "Runtime/HeadMountedDisplay/Public/MotionControllerComponent.h"
#include "MyRunebergVR_Pawn.h"

// Sets default values
APop::APop()
{
	//UE_LOG(LogTemp, Warning, TEXT("APop constructor called"));
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TEST, temporary!
	init2();
	//init(0, FTransform(FVector(0, 0, 0)));

}

void APop::init2() {

	//mesh = NewObject<USceneComponent>(this, TEXT("RootSceneComponent"));
	mesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Pop mesh test"));
	//RootComponent = mesh;
	mesh->AttachTo(RootComponent);

	TestSetupCollisionBox();
	TestSetupPhysics();
	TestSetupMaterial();

	//const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObjCube(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	//meshCube = MeshObjCube.Object;

	//mesh->SetStaticMesh(meshCube);

	////box->OnBeginCursorOver.AddDynamic(this, &APop::CustomOnBeginMouseOver);


}

void APop::TestSetupCollisionBox() {

	////box = CreateDefaultSubobject<UBoxComponent>(TEXT("Pop collision box"));
	//RootComponent = mesh;

	//box->AttachTo(mesh);
	RootComponent = mesh;
	////box->SetupAttachment(mesh);

	////box->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	////box->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//box->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	//box->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Block);
	mesh->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	////box->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Ignore);


	/*
	box->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
	box->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	box->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	box->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	box->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	*/

	// To be able to get mouse events
	////box->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);


	/*CollisionMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CollisionMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetSimulatePhysics(true);*/

}

void APop::TestSetupPhysics() {
	mesh->SetSimulatePhysics(true);
	////box->SetSimulatePhysics(false);    // WAS true!!!    !!!

	mesh->SetEnableGravity(false);
	//this->GetRootPrimitiveComponent()->SetEnableGravity(true);
	////box->SetEnableGravity(false);

	// Hide collision box (or not)
	//box->ToggleVisibility(true);
	////box->SetVisibility(true);

	//bUseComplexAsSimpleCollision = false;
	//mesh->GetBodySetup()->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseSimpleAsComplex;

	//this->SphereCollider->SetWorldScale3D(Scale * 1.5f);
	////box->SetWorldScale3D(FVector(20.0, 20.0, 20.0));
	//box->SetWorldLocation(
}


void APop::TestSetupMaterial() {

	static ConstructorHelpers::FObjectFinder<UMaterial> MAtom1(TEXT("Material'/Game/Materials/M_Atom1'"));
	if (MAtom1.Succeeded()) {
		MIAtom1 = UMaterialInstanceDynamic::Create(MAtom1.Object, MAtom1.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material 1 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MAtom2(TEXT("Material'/Game/Materials/M_Atom2'"));
	if (MAtom2.Succeeded()) {
		MIAtom2 = UMaterialInstanceDynamic::Create(MAtom2.Object, MAtom2.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material 2 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MAtom3(TEXT("Material'/Game/Materials/M_Atom3'"));
	if (MAtom3.Succeeded()) {
		MIAtom3 = UMaterialInstanceDynamic::Create(MAtom3.Object, MAtom3.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material 3 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MAtom4(TEXT("Material'/Game/Materials/M_Atom4'"));
	if (MAtom4.Succeeded()) {
		MIAtom4 = UMaterialInstanceDynamic::Create(MAtom4.Object, MAtom4.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material 4 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MAtom5(TEXT("Material'/Game/Materials/M_Atom5'"));
	if (MAtom5.Succeeded()) {
		MIAtom5 = UMaterialInstanceDynamic::Create(MAtom5.Object, MAtom5.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material 5 failed"));
	}

#if 1
	static ConstructorHelpers::FObjectFinder<UMaterial> MAtom6(TEXT("Material'/Game/Materials/M_Atom6'"));
#else /* Temporary... */
	static ConstructorHelpers::FObjectFinder<UMaterial> Material6(TEXT("Material'/Game/Materials/M_AtomWireChild'"));
#endif

	if (MAtom6.Succeeded()) {
		MIAtom6 = UMaterialInstanceDynamic::Create(MAtom6.Object, MAtom6.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material 6 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MAtom7(TEXT("Material'/Game/Materials/M_Atom7'"));
	if (MAtom7.Succeeded()) {
		MIAtom7 = UMaterialInstanceDynamic::Create(MAtom7.Object, MAtom7.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material 7 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MAtom8(TEXT("Material'/Game/Materials/M_Atom8'"));
	if (MAtom8.Succeeded()) {
		MIAtom8 = UMaterialInstanceDynamic::Create(MAtom8.Object, MAtom8.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material 8 failed"));
	}


	static ConstructorHelpers::FObjectFinder<UMaterial> MWire1(TEXT("Material'/Game/Materials/M_Wire1'"));
	if (MWire1.Succeeded()) {
		MIWire1 = UMaterialInstanceDynamic::Create(MWire1.Object, MWire1.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material Wire 1 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MWire2(TEXT("Material'/Game/Materials/M_Wire2'"));
	if (MWire2.Succeeded()) {
		MIWire2 = UMaterialInstanceDynamic::Create(MWire2.Object, MWire2.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material Wire 2 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MWire3(TEXT("Material'/Game/Materials/M_Wire3'"));
	if (MWire3.Succeeded()) {
		MIWire3 = UMaterialInstanceDynamic::Create(MWire3.Object, MWire3.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material Wire 3 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MWire4(TEXT("Material'/Game/Materials/M_Wire4'"));
	if (MWire4.Succeeded()) {
		MIWire4 = UMaterialInstanceDynamic::Create(MWire4.Object, MWire4.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material Wire 4 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MWire5(TEXT("Material'/Game/Materials/M_Wire5'"));
	if (MWire5.Succeeded()) {
		MIWire5 = UMaterialInstanceDynamic::Create(MWire5.Object, MWire5.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material Wire 5 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MWire6(TEXT("Material'/Game/Materials/M_Wire6'"));
	if (MWire6.Succeeded()) {
		MIWire6 = UMaterialInstanceDynamic::Create(MWire6.Object, MWire6.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material Wire 6 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MWire7(TEXT("Material'/Game/Materials/M_Wire7'"));
	if (MWire7.Succeeded()) {
		MIWire7 = UMaterialInstanceDynamic::Create(MWire7.Object, MWire7.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material Wire 7 failed"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MWire8(TEXT("Material'/Game/Materials/M_Wire8'"));
	if (MWire8.Succeeded()) {
		MIWire8 = UMaterialInstanceDynamic::Create(MWire8.Object, MWire8.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pop: Material Wire 8 failed"));
	}


}


void APop::init(AThing* thing, FTransform trafo) {
	//UE_LOG(LogTemp, Warning, TEXT("APop::init called, this=%p"), this);

	thingRef = thing;
	picked = false;

	BuildMesh();
	mesh->RegisterComponent();

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

	mesh->SetSimulatePhysics(true);


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

	this->SetActorLocation(trafo.GetLocation());
	loc = GetActorTransform().GetLocation();
}

// Called when the game starts or when spawned
void APop::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void APop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


AvreduGameMode* APop::GetGameMode() {
	UWorld* const theWorld = GetWorld();

	verify(theWorld != nullptr);

	return Cast<AvreduGameMode>(theWorld->GetAuthGameMode());
}


FString APop::ToString() {

	FVector loc = GetActorTransform().GetLocation();

	FString str = FString::Printf(TEXT("Pop points to thing with id <%s>, loc X=%f Y=%f Z=%f"), *(thingRef->name), loc.X, loc.Y, loc.Z);

	//FString str = FString::Printf(TEXT("Id: %s\n  No. of atoms: %d"), *name, CountAtoms());


	return str;
}



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

	UE_LOG(LogTemp, Warning, TEXT("APop::BuildMesh called, this-pop=%p, thingRef has the name: %s"), this, *thingRef->name);


	// Build combined mesh data for the full tree of the Thing that this Pop instantiates
	// Q: Do the verts positions depend on the trafo of this Pop?
	// A: No!
	// Q: What is the PURPOSE of the trafo of this Pop?
	// A: The trafo is the world position of the Pop. When it changes, the verts position won't change, since the verts are positioned RELATIVE TO THE Pop!
	//    If the root thing is an ATOM, the ORIGIN will be at the origin of that cube mesh (which in turn lives at the same position as the Pop).
	//	  If the root thing is a PARENT, it has sub-trafo:s of each of its children
	TArray<FVertexArray> verts2Dim;
	TArray<FInt32Array> tris2Dim;
	TArray<FColorArray> colors2Dim;
	TArray<FTrafoArray> collisions2Dim;
	TArray<FTransform> collisionCubePositions;
	thingRef->ComputeMeshData(verts2Dim, tris2Dim, colors2Dim, collisions2Dim, vertices, Triangles, normals, UV0, vertexColors, tangents, collisionCubePositions);

	//UE_LOG(LogTemp, Warning, TEXT("APop::BuildMesh: ComputeMeshData gave back collisionCubePositions.Num()==%d,  verts2Dim.Num()=%d,  tris2Dim.Num()=%d,  colors2Dim.Num()=%d,  collisions2Dim.Num()=%d"),
	//	collisionCubePositions.Num(), verts2Dim.Num(), tris2Dim.Num(), colors2Dim.Num(), collisions2Dim.Num());

	// The mesh may already have data. Remove it
	mesh->ClearAllMeshSections();

	/* Removing 180919 when trying to get house parts to work again
	Mesh->ClearCollisionConvexMeshes();
	*/

	// Add the new mesh data
	//Mesh->CreateMeshSection(0, vertices, Triangles, normals, UV0, vertexColors, tangents, false, EUpdateFrequency::Frequent);
	for (int i = 0; i < verts2Dim.Num(); ++i) {

		mesh->CreateMeshSection(i, verts2Dim[i].Verts, tris2Dim[i].Ints, TArray<FVector>(), UV0, colors2Dim[i].Colors, TArray<FRuntimeMeshTangent>(), false);

		// Set a material on just this mesh section
#if 0
		if (i % 2 == 0)
			mesh->SetSectionMaterial(i, MaterialInstance);
		else
			mesh->SetSectionMaterial(i, MaterialInstance2);
#endif



		switch (i % 8) {

			case 0:
				mesh->SetMaterial(0, MIAtom1);
				break;
			case 1:

#if 0 /* TEST: Let red shine! */
				MaterialInstance2->SetVectorParameterValue(FName(TEXT("EmissiveColor")), FLinearColor(0.97f, 0.32f, 0.30f));

#endif

				mesh->SetSectionMaterial(i, MIAtom2);
				break;
			case 2:
				mesh->SetSectionMaterial(i, MIAtom3);
				break;
			case 3:
				mesh->SetSectionMaterial(i, MIAtom4);
				break;
			case 4:
				mesh->SetSectionMaterial(i, MIAtom5);
				break;
			case 5:
				mesh->SetSectionMaterial(i, MIAtom6);
				break;
			case 6:
				mesh->SetSectionMaterial(i, MIAtom7);
				break;
			case 7:
				mesh->SetSectionMaterial(i, MIAtom8);
				break;
			default:
				mesh->SetSectionMaterial(i, MIAtom1);
		}

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

	//AddGrabBoxes(collisionCubePositions);

	AddGrabBoxes2Dim(collisions2Dim);

}




#if 0
//
// Setup the collision boxes for grabbing. Make them children of the root mesh.
//
void APop::AddGrabBoxes(TArray<FTransform>& grabBoxLocations) {

	UE_LOG(LogTemp, Warning, TEXT("APop::AddGrabBoxes called, address %p, grabBoxLocations.Num()==%d"), this, grabBoxLocations.Num());

	UBoxComponent* collisionBoxN;

	for (int32 grabBoxNo = 0; grabBoxNo < grabBoxLocations.Num(); ++grabBoxNo) {

		FTransform trafo = grabBoxLocations[grabBoxNo];
		FVector loc = trafo.GetLocation();

		FString boxNameStr = "Pop collision box " + FString::FromInt(grabBoxNo);
		FName boxName = FName(*boxNameStr);

		collisionBoxN = NewObject<UBoxComponent>(this, boxName);

		collisionBoxN->SetupAttachment(mesh);
		collisionBoxN->InitBoxExtent(FVector(CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2));

		FVector locAfter = trafo.GetLocation();	

		collisionBoxN->SetRelativeTransform(trafo);  // TODO: Add (50 50 50) to the location part
		collisionBoxN->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);		// Grabbable
		collisionBoxN->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);	// Try also QueryOnly
		collisionBoxN->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Overlap);  // Maybe overlap just for the grab sphere is faster?
		collisionBoxN->SetSimulatePhysics(false);
		collisionBoxN->SetEnableGravity(false);
		collisionBoxN->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
		collisionBoxN->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		collisionBoxN->OnBeginCursorOver.AddDynamic(this, &APop::CustomOnBeginMouseOver);
		collisionBoxN->OnEndCursorOver.AddDynamic(this, &APop::CustomOnEndMouseOver);
		collisionBoxN->OnClicked.AddDynamic(this, &APop::CustomOnClicked);
		collisionBoxN->RegisterComponent();

		grabBoxes.Add(collisionBoxN);
	}
}
#endif

//
// Setup the collision boxes for grabbing. Make them children of the root mesh.
//
void APop::AddGrabBoxes2Dim(TArray<FTrafoArray>& collisions2Dim) {

	UE_LOG(LogTemp, Warning, TEXT("APop::AddGrabBoxes2Dim called, address %p, collisions2Dim.Num()==%d"), this, collisions2Dim.Num());

	UBoxComponent* collisionBoxN;

	for (int32 subtreeNo = 0; subtreeNo < collisions2Dim.Num(); ++subtreeNo) {

		TArray<FTransform> grabBoxLocations = collisions2Dim[subtreeNo].Trafos;

		for (int32 grabBoxNo = 0; grabBoxNo < grabBoxLocations.Num(); ++grabBoxNo) {

			FTransform trafo = grabBoxLocations[grabBoxNo];
			FVector loc = trafo.GetLocation();

			FString boxNameStr = "Pop box " + FString::FromInt(grabBoxNo) + " of subtree " + FString::FromInt(subtreeNo);
			FName boxName = FName(*boxNameStr);

			collisionBoxN = NewObject<UBoxComponent>(this, boxName);

			collisionBoxN->SetupAttachment(mesh);
			collisionBoxN->InitBoxExtent(FVector(CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2));

			FVector locAfter = trafo.GetLocation();

			collisionBoxN->SetRelativeTransform(trafo);  // TODO: Add (50 50 50) to the location part
			collisionBoxN->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);		// Grabbable
			collisionBoxN->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);	// Try also QueryOnly
			collisionBoxN->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Overlap);  // Maybe overlap just for the grab sphere is faster?
			collisionBoxN->SetSimulatePhysics(false);
			collisionBoxN->SetEnableGravity(false);
			collisionBoxN->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
			collisionBoxN->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
			collisionBoxN->OnBeginCursorOver.AddDynamic(this, &APop::CustomOnBeginMouseOver);
			collisionBoxN->OnEndCursorOver.AddDynamic(this, &APop::CustomOnEndMouseOver);
			collisionBoxN->OnClicked.AddDynamic(this, &APop::CustomOnClicked);
			collisionBoxN->RegisterComponent();

			grabBoxes.Add(collisionBoxN);
		}
	}
}

void APop::CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent)
{

	UBoxComponent* grabBox = Cast<UBoxComponent>(TouchedComponent);
	if (grabBox == nullptr)
		return;

	FString dummyLeft, subtreeStr;
	grabBox->GetName().Split(TEXT("subtree "), &dummyLeft, &subtreeStr);
	int subtree = FCString::Atoi(*subtreeStr);

	//
	// Highlight the Pop that the mouse pointer is over
	//
#if 0
	Highlight(subtree, 1);
#else
	HighlightWireChild(subtree, 1);
#endif

}

void APop::CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent)
{

	UBoxComponent* grabBox = Cast<UBoxComponent>(TouchedComponent);
	if (grabBox == nullptr)
		return;

	FString dummyLeft, subtreeStr;
	grabBox->GetName().Split(TEXT("subtree "), &dummyLeft, &subtreeStr);
	int subtree = FCString::Atoi(*subtreeStr);

	//
	// De-highlight the Pop that the mouse pointer was over
	//
#if 0
	Highlight(subtree, 0);
#else
	HighlightWireChild(subtree, 0);
#endif

	UE_LOG(LogTemp, Warning, TEXT("APop::CustomOnEndMouseOver: Pop Mouse End,  TouchedComponent=%p or %p, with name=%s"),
		   TouchedComponent, grabBox, *grabBox->GetName());

}


void APop::CustomOnClicked(UPrimitiveComponent* clickedComponent, FKey inKey)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("Pop Mouse Click"));
		UE_LOG(LogTemp, Warning, TEXT("APop::CustomOnClicked: Pop Mouse Click on component with name=<%s>"),
			   *clickedComponent->GetName());
	}

	// Signal that Pop wants to be dropped or picked
	((AvreduGameMode*)GetWorld()->GetAuthGameMode())->AddWantsPicking(this);

}


//
// Highlight a section of the mesh by passing the sectionIx.
// Highlight all sections of the mesh by passing -1.
//
// lightLevel 0 is not highlighted, 1 is highlighted, 2 is more highlighted
//
void APop::Highlight(int sectionIx, int lightLevel) {

	UE_LOG(LogTemp, Warning, TEXT("APop::Highlight: this=%p (%s), sectionIx=%d, lightLevel=%d"),
		   this, *this->thingRef->name, sectionIx, lightLevel);

	UMaterialInstanceDynamic* mi = nullptr;
	if (sectionIx == -1) {
	}
	else {
		switch (sectionIx % 8) {

		case 0:
			mi = MIAtom1;
			break;
		case 1:
			mi = MIAtom2;
			break;
		case 2:
			mi = MIAtom3;
			break;
		case 3:
			mi = MIAtom4;
			break;
		case 4:
			mi = MIAtom5;
			break;
		case 5:
			mi = MIAtom6;
			break;
		case 6:
			mi = MIAtom7;
			break;
		case 7:
			mi = MIAtom8;
			break;
		}

		verify(mi != nullptr);
	}

	AvreduGameMode* theGameMode = (AvreduGameMode*)GetWorld()->GetAuthGameMode();
	FLinearColor color = theGameMode->deHighlightColor;

	switch (lightLevel) {

		case 0:
			// De-highlight
			color = theGameMode->deHighlightColor;
			break;
		case 1:
			// Highlight
#if 0
			color = theGameMode->highlightColor;
#else /* Wireframe version of the code */
			color = theGameMode->deHighlightColor;
			mi = MIWire1;
			UE_LOG(LogTemp, Warning, TEXT("APop::Highlight: mi was set to MIWire1 (%p)"), mi);

#endif
			break;
		case 2:
			// Highlight more
			color = theGameMode->brightHighlightColor;
			break;
		default:
			// At this point, this verify will always fail
			verify(lightLevel >= 0 && lightLevel <= 2);
	}

	if (sectionIx == -1) {
		MIAtom1->SetVectorParameterValue(FName(TEXT("EmissiveColor")), color);
		MIAtom2->SetVectorParameterValue(FName(TEXT("EmissiveColor")), color);
		MIAtom3->SetVectorParameterValue(FName(TEXT("EmissiveColor")), color);
		MIAtom4->SetVectorParameterValue(FName(TEXT("EmissiveColor")), color);
		MIAtom5->SetVectorParameterValue(FName(TEXT("EmissiveColor")), color);
		MIAtom6->SetVectorParameterValue(FName(TEXT("EmissiveColor")), color);
		MIAtom7->SetVectorParameterValue(FName(TEXT("EmissiveColor")), color);
		MIAtom8->SetVectorParameterValue(FName(TEXT("EmissiveColor")), color);
	}
	else {
		mi->SetVectorParameterValue(FName(TEXT("EmissiveColor")), color);
	}
}


void APop::HighlightWireChild(int sectionIx, int lightLevel) {

	UE_LOG(LogTemp, Warning, TEXT("APop::Highlight: this=%p (%s), sectionIx=%d"),
		this, *this->thingRef->name, sectionIx);

	switch (lightLevel) {

		case 0:
			// Hardcode MIAtom1 for now (green atm)
			if (sectionIx == -1)
				mesh->SetMaterial(0, MIAtom1);
			else
				mesh->SetSectionMaterial(sectionIx, MIAtom1);
			break;
			
		case 1:
		case 2:   /* TEMPORARY, should have own implementation */
			if (sectionIx == -1) {
				//mesh->SetMaterial(0, MIWire1);
				for (int sectIx = 0; sectIx < 8; ++sectIx) {
					mesh->SetSectionMaterial(sectIx, section2MIWire(sectIx));
				}
			}
			else
				//mesh->SetSectionMaterial(sectionIx, MIWire1);
				mesh->SetSectionMaterial(sectionIx, section2MIWire(sectionIx));
			break;

		//case 2:
		// Bright-highlight is NYI atm
	}
	
}


UMaterialInstanceDynamic* APop::section2MIWire(int sectionIx) {

	UMaterialInstanceDynamic* mi = nullptr;

	switch (sectionIx) {

		case 0:
			mi = MIWire1;
			break;

		case 1:
			mi = MIWire2;
			break;

		case 2:
			mi = MIWire3;
			break;

		case 3:
			mi = MIWire4;
			break;

		case 4:
			mi = MIWire5;
			break;

		case 5:
			mi = MIWire6;
			break;

		case 6:
			mi = MIWire7;
			break;

		case 7:
			mi = MIWire8;
			break;
	}

	return mi;
}


void APop::LogComponentHierarchy(USceneComponent* rootComp) {

	UE_LOG(LogTemp, Warning, TEXT("APop::LogComponentHierarchy: Called, this-pop=%p, thing-name=%s, rootComp=%p"),
		   this, *thingRef->name, rootComp);

/*
	void GetChildrenComponents
	(
		bool bIncludeAllDescendants,
		TArray < USceneComponent * > & Children
	)
*/

	USceneComponent* theRoot = rootComp;

	TArray < USceneComponent* > children;
		
	theRoot->GetChildrenComponents(true, children);

	UE_LOG(LogTemp, Warning, TEXT("APop::LogComponentHierarchy: children.Num()=%d"), children.Num());

	for (int ix = 0; ix < children.Num(); ++ix) {

		USceneComponent* child = children[ix];

		UE_LOG(LogTemp, Warning, TEXT("APop::LogComponentHierarchy: child=%p, name=%s"),
			   child, *child->GetName());
	}

}