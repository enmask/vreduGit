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
	mesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Pop mesh"));
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
	
	// TEST 190103
	mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	// TEST 190103
	mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//box->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	ECollisionResponse response4Early = mesh->BodyInstance.GetResponseToChannel(ECC_WorldDynamic);
	UE_LOG(LogTemp, Warning,
		TEXT("APop::TestSetupCollisionBox: Before SetResponseToAllChannels: response4Early=%s"),
		*ECollisionResponse2Str(response4Early));

	//mesh->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Block);

	response4Early = mesh->BodyInstance.GetResponseToChannel(ECC_WorldDynamic);
	UE_LOG(LogTemp, Warning,
		   TEXT("APop::TestSetupCollisionBox: Between SetResponseToAllChannels and SetResponseToChannel: response4Early=%s"),
		   *ECollisionResponse2Str(response4Early));

	// TEST HACK 190105: Ignore WorldDynamic, because I'm testing out grabBoxes as WorldDynamic
	//mesh->BodyInstance.SetResponseToChannel(ECC_WorldDynamic, ECR_Ignore);

	// TEST HACK 190106: Ignore PhysicsBody as well, because I'm welding now, so the child (grabBoxes)
	// will mimic the parent (RMC), I guess. Possibly both parent and child will be PhysicsBody,
	// and if they block PhysicsBody, they might collide with each other and "explode"...
	mesh->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
		//SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

	mesh->BodyInstance.SetResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	response4Early = mesh->BodyInstance.GetResponseToChannel(ECC_WorldDynamic);
	UE_LOG(LogTemp, Warning,
		TEXT("APop::TestSetupCollisionBox: After SetResponseToChannel: response4Early=%s"),
		*ECollisionResponse2Str(response4Early));

	//mesh->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	/// Changed to BLOCK 190104    mesh->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	////box->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Ignore);


	// 190105: Try to make pop collide with Floor
	mesh->SetNotifyRigidBodyCollision(true);


	/*
	box->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
	box->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	box->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	box->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	box->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	*/

	// To be able to get mouse events
	mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);


	/*CollisionMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CollisionMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetSimulatePhysics(true);*/

}

void APop::TestSetupPhysics() {

	bool simPhys = mesh->IsSimulatingPhysics();
	bool simPhys2 = mesh->IsAnySimulatingPhysics();
	UE_LOG(LogTemp, Warning, TEXT("APop::TestSetupPhysics: Before mesh->SetSimulatePhysics(true):  simPhys1=%s, simPhys2=%s"),
		   simPhys ? TEXT("true") : TEXT("false"),
		   simPhys2 ? TEXT("true") : TEXT("false"));

	mesh->SetSimulatePhysics(true);

	bool simPhys3 = mesh->IsSimulatingPhysics();
	bool simPhys4 = mesh->IsAnySimulatingPhysics();
	UE_LOG(LogTemp, Warning, TEXT("APop::TestSetupPhysics: After mesh->SetSimulatePhysics(true):  simPhys3=%s, simPhys4=%s"),
		simPhys3 ? TEXT("true") : TEXT("false"),
		simPhys4 ? TEXT("true") : TEXT("false"));


	////box->SetSimulatePhysics(false);    // WAS true!!!    !!!

	mesh->SetEnableGravity(true);
	//this->GetRootPrimitiveComponent()->SetEnableGravity(true);
	////box->SetEnableGravity(false);

	// Hide collision box (or not)
	//box->ToggleVisibility(true);
	////box->SetVisibility(true);

	// Reinserted these 190102
	//bUseComplexAsSimpleCollision = false;
	//mesh->GetBodySetup()->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseSimpleAsComplex;
	mesh->SetCollisionUseComplexAsSimple(false);

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


void APop::init(AThing* thing, FTransform trafo, bool ghost) {
	//UE_LOG(LogTemp, Warning, TEXT("APop::init called, this=%p"), this);

	thingRef = thing;
	picked = false;
	isGhost = ghost;

	UE_LOG(LogTemp, Warning, TEXT("APop::init() will now call BuildMesh"));

	BuildMesh(ghost);
	mesh->RegisterComponent();

	//
	// Setup the mesh as root
	//
	RootComponent = mesh;

	mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	if (isGhost) {
		mesh->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		mesh->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		mesh->SetSimulatePhysics(true);
		mesh->SetEnableGravity(false);
		this->GetRootPrimitiveComponent()->SetEnableGravity(false);
	}
	else {
		mesh->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		mesh->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Block);
		mesh->SetSimulatePhysics(true);
		mesh->SetEnableGravity(true);
		this->GetRootPrimitiveComponent()->SetEnableGravity(true);
	}

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

#if 0
	// TEST: Call WeldTo() now, when simulate physics is hopefully all done and ready
	for (int i = 0; i < grabBoxes.Num(); ++i) {

		UBoxComponent* grabBox = grabBoxes[i];

		if (mesh->IsSimulatingPhysics()) {
			UE_LOG(LogTemp, Warning, TEXT("APop::BeginPlay before WeldTo, this-pop=%p, IsSimulatingPhysics: ***true***"), this);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("APop::BeginPlay before WeldTo, this-pop=%p, IsSimulatingPhysics: *false*"), this);
		}


		grabBox->WeldTo(mesh);

		if (mesh->IsSimulatingPhysics()) {
			UE_LOG(LogTemp, Warning, TEXT("APop::BeginPlay after WeldTo, this-pop=%p, IsSimulatingPhysics: ***true***"), this);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("APop::BeginPlay after WeldTo, this-pop=%p, IsSimulatingPhysics: *false*"), this);
		}

	}
#endif
}


// Called every frame
void APop::Tick(float DeltaTime)
{
	//const bool simulatesPhysics = Component->BodyInstance.bSimulatePhysics;
	//RootComponent->IsPhysicsCollisionEnabled
	//RootComponent->IsAnySimulatingPhysics
	//RootComponent->GetCollisionEnabled()
	//this->GetRootPrimitiveComponent()->SetEnableGravity(true);
	UPrimitiveComponent* primComp = this->GetRootPrimitiveComponent();

	//bool canEdit = RootComponent->CanEdi
	bool canEdit = primComp->CanEditSimulatePhysics();

	//CanEditSimulatePhysics()
	//bool simPhys = RootComponent->BodyInstance.bSimulatePhysics;
	bool simPhys = primComp->BodyInstance.bSimulatePhysics;
	bool simPhys2 = primComp->IsSimulatingPhysics();


	//bool simPhys2 = primComp->
	USceneComponent* rootSC = this->GetRootComponent();
	bool simPhys3 = rootSC->IsSimulatingPhysics();

	/////primComp->SetSimulatePhysics(true);

	bool simPhys4 = rootSC->IsSimulatingPhysics();
	bool simPhys5 = primComp->IsSimulatingPhysics();


	//bool isCollEnabled = primComp->BodyInstance.GetCollisionEnabled();
	//ECollisionEnabled::QueryOnly
	ECollisionEnabled::Type isCollEnabled = primComp->BodyInstance.GetCollisionEnabled();
	FString isCollEnabledStr = ECollisionEnabled2Str(isCollEnabled);

	FString popCollChannelStr = ECollisionChannel2Str(primComp->GetCollisionObjectType());

	ECollisionResponse response1 = GetComponentsCollisionResponseToChannel(ECC_Camera);
	ECollisionResponse response2 = GetComponentsCollisionResponseToChannel(ECC_Pawn);
	ECollisionResponse response3 = GetComponentsCollisionResponseToChannel(ECC_PhysicsBody);
	ECollisionResponse response4 = GetComponentsCollisionResponseToChannel(ECC_WorldDynamic);
	ECollisionResponse response4_2 = primComp->GetCollisionResponseToChannel(ECC_WorldDynamic);

	FVector logLoc = GetActorLocation();
	FTransform logTrafo = mesh->GetRelativeTransform();
	FVector logLoc2 = logTrafo.GetLocation();

	bool popGrav = primComp->IsGravityEnabled();

#if 1

	float massMesh = mesh->GetMass();
	bool overrideMassMesh = mesh->GetBodyInstance()->bOverrideMass;
		//ShapeStaticMeshComponent->GetBodyInstance()->bOverrideMass
		
	/* */ ////
	UE_LOG(LogTemp, Warning,
		   TEXT("APop::Tick: this-pop=%p (root parent: %p), name: %s, 1.canEditSim=%s, 2.bSimulatePhysics: %s (simPhys2=%s, simPhys3=%s, simPhys4=%s, simPhys5=%s), 3.isCollEnabled=%s, 4.popCollChannelStr=%s, 5.popGrav=%s, response1=%s, response2=%s, response3=%s, response4=%s, response4_2=%s, loc: X=%f  Y=%f  Z=%f, loc2: X=%f  Y=%f  Z=%f, massMesh=%f, overrideMassMesh=%s"),
		   this,
		   GetRootComponent()->GetAttachParent(),
		   *thingRef->name,
		   canEdit ? TEXT("true") : TEXT("false"),
		   simPhys ? TEXT("true") : TEXT("false"),
		   simPhys2 ? TEXT("true") : TEXT("false"),
		   simPhys3 ? TEXT("true") : TEXT("false"),
		   simPhys4 ? TEXT("true") : TEXT("false"),
		   simPhys5 ? TEXT("true") : TEXT("false"),
		   *isCollEnabledStr,
		   *popCollChannelStr,
		   popGrav ? TEXT("true") : TEXT("false"),
		   *ECollisionResponse2Str(response1),
		   *ECollisionResponse2Str(response2),
		   *ECollisionResponse2Str(response3),
		   *ECollisionResponse2Str(response4),
		   *ECollisionResponse2Str(response4_2),
		   logLoc.X, logLoc.Y, logLoc.Z,
		   logLoc2.X, logLoc2.Y, logLoc2.Z,
		   massMesh,
		   overrideMassMesh ? TEXT("true") : TEXT("false"));

	/* */

	for (int i = 0; i < grabBoxes.Num() && i < 10; ++i) {
		UBoxComponent* grabBox = grabBoxes[i];
		//UPrimitiveComponent* grabBoxPrimComp = grabBox->GetRo
		//UPrimitiveComponent* grabBoxPrimComp = grabBox->GetRo
		//this->GetRootPrimitiveComponent();

		bool grabBoxCanEdit = grabBox->CanEditSimulatePhysics();
		//bool grabBoxSimPhys = primComp->BodyInstance.bSimulatePhysics;
		bool grabBoxSimPhys = grabBox->IsSimulatingPhysics();
		//bool grabBoxIsCollEnabled = primComp->BodyInstance.GetCollisionEnabled();
		ECollisionEnabled::Type grabBoxIsCollEnabled = grabBox->GetCollisionEnabled();
		FString grabBoxIsCollEnabledStr = ECollisionEnabled2Str(grabBoxIsCollEnabled);
		FString grabBoxCollChannelStr = ECollisionChannel2Str(grabBox->GetCollisionObjectType());
		bool grabBoxGrav = primComp->IsGravityEnabled();
		FVector grabBoxLoc = grabBox->GetRelativeTransform().GetLocation();

		float massGrabBox = grabBox->GetMass();
		bool overrideMassGrabBox = grabBox->GetBodyInstance()->bOverrideMass;

#if 1 /* //// */
		UE_LOG(LogTemp, Warning,
			TEXT("APop::Tick: grabBox=%p, GetName()=%s, 1.grabBoxCanEdit=%s,  2.grabBoxSimPhys: %s,  3.grabBoxIsCollEnabled=%s, 4.CollChannel=%s,  5.grabBoxGrav=%s,  6.grabBoxLoc:  X=%f  Y=%f  Z=%f,  massGrabBox=%f, overrideMassGrabBox=%s"),
			this,
			*grabBox->GetName(),
			grabBoxCanEdit ? TEXT("true") : TEXT("false"),
			grabBoxSimPhys ? TEXT("true") : TEXT("false"),
			*grabBoxIsCollEnabledStr,
			*grabBoxCollChannelStr,
			grabBoxGrav ? TEXT("true") : TEXT("false"),
			grabBoxLoc.X, grabBoxLoc.Y, grabBoxLoc.Z,
			massGrabBox,
			overrideMassGrabBox ? TEXT("true") : TEXT("false"));
		

#endif

		// TEST: Now also try to ALTER settings!
		//box->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly)
		//Try 1:  primComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		//Try 2: (Invalid Simulate Options: Body (Pop_0.Pop mesh test) is set to simulate physics but
		//									Collision Enabled is incompatible
		//primComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Try 3:
		//primComp->SetSimulatePhysics(false);

		// Try 4:
		//primComp->SetSimulatePhysics(false);
		//primComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Try 5:
		//grabBox->SetSimulatePhysics(false);
		//SetActorEnableCollision(true);

		// Try 6:
		//primComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	}
#endif

	Super::Tick(DeltaTime);


#if 1 /* Tick() weld experiment */

	//UPrimitiveComponent* primComp = this->GetRootPrimitiveComponent();
	//FBodyInstance BI = primComp->BodyInstance;
	//bool grabBoxSimPhys = primComp->BodyInstance.bSimulatePhysics;
	//bool simPhys5 = primComp->IsSimulatingPhysics();

	////UE_LOG(LogTemp, Warning, TEXT("APop::Tick: BI.WeldParent=%p"), primComp->BodyInstance.WeldParent);

	//if (!primComp->BodyInstance.WeldParent) {
	////UE_LOG(LogTemp, Warning, TEXT("APop::Tick: Will weld, if RMC IsSimulating"));

	// TEST: Call WeldTo() now, when simulate physics is hopefully all done and ready
	for (int i = 0; i < grabBoxes.Num(); ++i) {
		UBoxComponent* grabBox = grabBoxes[i];

		UE_LOG(LogTemp, Warning, TEXT("APop::Tick before WeldTo-if, this-pop=%p, IsSimulatingPhysics: %s, WeldPArent=%p"),
			   this, mesh->IsSimulatingPhysics() ? TEXT("true") : TEXT("false"), grabBox->BodyInstance.WeldParent);

		if (mesh->IsSimulatingPhysics() && !grabBox->BodyInstance.WeldParent) {
			////UE_LOG(LogTemp, Warning, TEXT("APop::BeginPlay before WeldTo, this-pop=%p, IsSimulatingPhysics: ***true***, so YEP, will Weld!"), this);

			FTransform meshTrafo = mesh->GetRelativeTransform();
			FVector meshLoc = meshTrafo.GetLocation();
			FTransform grabBoxCompTrafo = grabBox->GetComponentTransform();
			// TODO: Check implementation of GetComponentTransform and GetRelativeTransform. I guess they
			// give the same result for a non-child, but which is most efficient?
			FTransform grabBoxRelTrafo = grabBox->GetRelativeTransform();
			FVector grabBoxCompLoc = grabBoxCompTrafo.GetLocation();
			FVector grabBoxRelLoc = grabBoxRelTrafo.GetLocation();

			FTransform grabBoxWorldTrafo1 = grabBoxRelTrafo * meshTrafo;
			FTransform grabBoxWorldTrafo2 = meshTrafo * grabBoxRelTrafo;
			FVector grabBoxWorldLoc1 = grabBoxWorldTrafo1.GetLocation();
			FVector grabBoxWorldLoc2 = grabBoxWorldTrafo2.GetLocation();

			FVector grabBoxLoc = grabBox->GetRelativeTransform().GetLocation();
			/* */
			UE_LOG(LogTemp, Warning,
				   TEXT("APop::Tick right before WeldTo: this-pop=%p,  meshLoc:  X=%f  Y=%f  Z=%f, grabBoxNo=%d (of %d),  grabBox=%p grabBox rel. loc:  X=%f  Y=%f  Z=%f,  WeldParent=%p,  grabBoxCompLoc:  X=%f  Y=%f  Z=%f,  grabBoxRelLoc:  X=%f  Y=%f  Z=%f,  grabBoxWorldLoc1:  X=%f  Y=%f  Z=%f,  grabBoxWorldLoc2:  X=%f  Y=%f  Z=%f"),
				   this, meshLoc.X, meshLoc.Y, meshLoc.Z, i, grabBoxes.Num(), grabBox, grabBoxLoc.X, grabBoxLoc.Y, grabBoxLoc.Z, grabBox->BodyInstance.WeldParent,
				   grabBoxCompLoc.X, grabBoxCompLoc.Y, grabBoxCompLoc.Z, grabBoxRelLoc.X, grabBoxRelLoc.Y, grabBoxRelLoc.Z,
				   grabBoxWorldLoc1.X, grabBoxWorldLoc1.Y, grabBoxWorldLoc1.Z,
				   grabBoxWorldLoc2.X, grabBoxWorldLoc2.Y, grabBoxWorldLoc2.Z);
			/* */
			AvreduGameMode* theGameMode = GetGameMode();

			// HACK to reduce the adjustment
			// 		float cmAdjustmentZ = 0.0;
			//				float percentAdjustmentZ = 0.0;
			// relAdjustmentZ: 0.0 means non-affected grabBoxRelLoc (this is the default)
			//					   0.5 means 50% grabBoxRelLoc, 50% grabBoxWorldLoc
			//					   1.0 means 100% changed to grabBoxWorldLoc
			//FVector grabBoxCompromiseLoc = 0.5f * (grabBoxRelLoc + grabBoxWorldLoc2);
			FVector grabBoxCompromiseLoc = (1.0 - theGameMode->percentAdjustmentZ) * grabBoxRelLoc +
											theGameMode->percentAdjustmentZ * grabBoxWorldLoc2;

			grabBoxCompromiseLoc.Z = grabBoxCompromiseLoc.Z + theGameMode->cmAdjustmentZ;

			grabBoxWorldTrafo2.SetLocation(grabBoxCompromiseLoc);

			// WeldTo will expect grabBox to have a world transform, make it so
			if (theGameMode->convertGrabBoxRelToWorld)
				grabBox->SetRelativeTransform(grabBoxWorldTrafo2);

			grabBox->WeldTo(mesh);

			FTransform meshTrafoNew = mesh->GetRelativeTransform();
			FVector meshLocNew = meshTrafoNew.GetLocation();
			FTransform grabBoxTrafoNew = grabBox->GetRelativeTransform();
			FVector grabBoxLocNew = grabBoxTrafoNew.GetLocation();

			/* */
			UE_LOG(LogTemp, Warning,
				TEXT("APop::Tick right AFTER WeldTo: this-pop=%p, grabBoxNo=%d (of %d),  grabBox=%p,  ,  meshLocNew:  X=%f  Y=%f  Z=%f, grabBox rel. loc:  X=%f  Y=%f  Z=%f,  grabBoxLocNew:  X=%f  Y=%f  Z=%f,  WeldParent=%p"),
				this, i, grabBoxes.Num(), grabBox, meshLocNew.X, meshLocNew.Y, meshLocNew.Z, grabBoxLoc.X, grabBoxLoc.Y, grabBoxLoc.Z, grabBoxLocNew.X, grabBoxLocNew.Y, grabBoxLocNew.Z, grabBox->BodyInstance.WeldParent);
			/* */
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("APop::BeginPlay before WeldTo, this-pop=%p, IsSimulatingPhysics: *false*, so will NOT WeldTo yet!"), this);
		}
	}

#endif


}


FString APop::ECollisionEnabled2Str(ECollisionEnabled::Type eCollEnabled) {

	FString s;

	switch (eCollEnabled) {
		case ECollisionEnabled::NoCollision:
			s = "NoCollision";
			break;
		case ECollisionEnabled::PhysicsOnly:
			s = "PhysicsOnly";
			break;
		case ECollisionEnabled::QueryAndPhysics:
			s = "QueryAndPhysics";
			break;
		case ECollisionEnabled::QueryOnly:
			s = "QueryOnly";
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("APop::ECollisionEnabled2Str: ERROR, eCollEnabled has unknown value!"));
			FGenericPlatformMisc::RequestExit(false);
	}
	return s;
}


//ECollisionChannel::ECC_PhysicsBody
FString APop::ECollisionChannel2Str(ECollisionChannel eCollChannel) {

	FString s;

	switch (eCollChannel) {
	case ECollisionChannel::ECC_Camera:
		s = "ECC_Camera";
		break;
	case ECollisionChannel::ECC_Destructible:
		s = "ECC_Destructible";
		break;
	case ECollisionChannel::ECC_EngineTraceChannel1:
		s = "ECC_EngineTraceChannel1";
		break;
	case ECollisionChannel::ECC_OverlapAll_Deprecated:
		s = "ECC_OverlapAll_Deprecated";
		break;
	case ECollisionChannel::ECC_Pawn:
		s = "ECC_Pawn";
		break;
	case ECollisionChannel::ECC_PhysicsBody:
		s = "ECC_PhysicsBody";
		break;
	case ECollisionChannel::ECC_Vehicle:
		s = "ECC_Vehicle";
		break;
	case ECollisionChannel::ECC_Visibility:
		s = "ECC_Visibility";
		break;
	case ECollisionChannel::ECC_WorldDynamic:
		s = "ECC_WorldDynamic";
		break;
	case ECollisionChannel::ECC_WorldStatic:
		s = "ECC_WorldStatic";
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("APop::ECollisionChannel2Str: Other ECollisionChannel found, maybe check for more?"));
	}
	return s;
}


FString APop::ECollisionResponse2Str(ECollisionResponse eCollResponse) {

	FString s;

	switch (eCollResponse) {
		case ECollisionResponse::ECR_Ignore:
			s = "ECR_Ignore";
			break;
		case ECollisionResponse::ECR_Block:
			s = "ECR_Block";
			break;
		case ECollisionResponse::ECR_Overlap:
			s = "ECR_Overlap";
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("APop::ECollisionResponse2Str: ERROR, eCollResponse has unknown value!"));
			FGenericPlatformMisc::RequestExit(false);
	}
	return s;
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
void APop::BuildMesh(bool ghost) {

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

	UE_LOG(LogTemp, Warning, TEXT("APop::BuildMesh: ComputeMeshData gave back collisionCubePositions.Num()==%d,  verts2Dim.Num()=%d,  tris2Dim.Num()=%d,  colors2Dim.Num()=%d,  collisions2Dim.Num()=%d"),
		   collisionCubePositions.Num(), verts2Dim.Num(), tris2Dim.Num(), colors2Dim.Num(), collisions2Dim.Num());


	FVertexArray vertArray;

	// Log collision cube positions
	UE_LOG(LogTemp, Warning, TEXT("APop::BuildMesh: Logging verts2Dim:"));
	for (int i = 0; i < verts2Dim.Num(); ++i) {

		vertArray = verts2Dim[i];

		UE_LOG(LogTemp, Warning, TEXT("APop::BuildMesh: Found a new vertArray (no. %d)"), i);
		FVector vert;

		for (int j = 0; j < vertArray.Verts.Num(); ++j) {

			vert = vertArray.Verts[j];

			UE_LOG(LogTemp, Warning, TEXT("APop::BuildMesh: Found a new vert (no. %d): X=%f  Y=%f  Z=%f"),
				j, vert.X, vert.Y, vert.Z);

		}
	}

	FTransform collCubeTrafo;
	FVector collCubeLoc;
	// Log collision cube positions
	UE_LOG(LogTemp, Warning, TEXT("APop::BuildMesh: Logging collisionCubePositions: "));
	for (int i = 0; i < collisionCubePositions.Num(); ++i) {
		collCubeTrafo = collisionCubePositions[i];
		collCubeLoc = collCubeTrafo.GetLocation();

		UE_LOG(LogTemp, Warning,
			   TEXT("APop::BuildMesh: collCubeLoc:  X=%f  Y=%f  Z=%f"),
			   collCubeLoc.X, collCubeLoc.Y, collCubeLoc.Z);

	}

	// The mesh may already have data. Remove it
	mesh->ClearAllMeshSections();

	/* Removing 180919 when trying to get house parts to work again
	Mesh->ClearCollisionConvexMeshes();
	*/

	// Add the new mesh data
	//Mesh->CreateMeshSection(0, vertices, Triangles, normals, UV0, vertexColors, tangents, false, EUpdateFrequency::Frequent);
	for (int i = 0; i < verts2Dim.Num(); ++i) {

		// TEST 190104: Try passing true to create collision automatically! ***
		mesh->CreateMeshSection(i, verts2Dim[i].Verts, tris2Dim[i].Ints, TArray<FVector>(), UV0, colors2Dim[i].Colors, TArray<FRuntimeMeshTangent>(), false);

		// TEST 190106
		mesh->SetMeshSectionCollisionEnabled(i, true);

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
	/**/
	// TEST 190103
	//mesh->ClearCollisionConvexMeshes();  // TODO: maybe use ClearAllMeshCollisionSections instad..............

	// TEST 190103
	//mesh->AddCollisionConvexMesh(verts2Dim[0].Verts); // Todo, I should probably do this for 0, 1, 2, ... Num()
	/**/

	// TEST 190103
	//mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	// TEST 190103
	mesh->RegisterComponent();



	// TEST 190103
	//mesh->BodyInstance.SetResponseToAllChannels(ECR_Block);

	// AddGrabBoxes(collisionCubePositions);

#if 1 /* TEST why no falling */
	AddGrabBoxes2Dim(collisions2Dim, ghost);
#endif
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
void APop::AddGrabBoxes2Dim(TArray<FTrafoArray>& collisions2Dim, bool ghost) {

	UE_LOG(LogTemp, Warning, TEXT("APop::AddGrabBoxes2Dim called, address %p, collisions2Dim.Num()==%d, ghost=%s"),
		   this, collisions2Dim.Num(), ghost ? TEXT("true") : TEXT("false"));

	grabBoxes.Empty();

	UBoxComponent* collisionBoxN;

	for (int32 subtreeNo = 0; subtreeNo < collisions2Dim.Num(); ++subtreeNo) {

		TArray<FTransform> grabBoxLocations = collisions2Dim[subtreeNo].Trafos;

		for (int32 grabBoxNo = 0; grabBoxNo < grabBoxLocations.Num(); ++grabBoxNo) {

			FTransform trafo = grabBoxLocations[grabBoxNo];
			FVector loc = trafo.GetLocation();

			FString boxNameStr = "Pop box " + FString::FromInt(grabBoxNo) + " of subtree " + FString::FromInt(subtreeNo);
			FName boxName = FName(*boxNameStr);

			collisionBoxN = NewObject<UBoxComponent>(this, boxName);
#if 0 /* Before 190106 */
			collisionBoxN->SetupAttachment(mesh);
#else
			//UPrimitiveComponent::WeldTo
			//collisionBoxN->WeldTo(mesh);
#endif

			collisionBoxN->InitBoxExtent(FVector(CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2));

			FTransform popTrafo = GetTransform();
			FVector popLoc = popTrafo.GetLocation();
			FVector locAfter = trafo.GetLocation();
			// Adjust so that collisionBoxN has the world trafo instead of local trafo.
			// This will be changed by the weld of collision box to mesh later on.
			// The weld expects a world trafo but leaves a local trafo as a final result.
#if 1 /* With adjustment */
			FTransform adjustedTrafo = trafo * popTrafo;
#else /* Without adjustment */
			FTransform adjustedTrafo = trafo;
#endif
			FVector adjustedLoc = adjustedTrafo.GetLocation();

			UE_LOG(LogTemp, Warning,
				   TEXT("APop::AddGrabBoxes2Dim: this-pop=%p, popLoc:  X=%f  Y=%f  Z=%f, grabBoxNo=%d,  locAfter:  X=%f  Y=%f  Z=%f,  adjustedLoc:  X=%f  Y=%f  Z=%f"),
				   this, popLoc.X, popLoc.Y, popLoc.Z, grabBoxNo, locAfter.X, locAfter.Y, locAfter.Z, adjustedLoc.X, adjustedLoc.Y, adjustedLoc.Z);

			collisionBoxN->SetRelativeTransform(adjustedTrafo);
			collisionBoxN->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

			if (ghost) {
				collisionBoxN->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				collisionBoxN->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			}
			else {
				collisionBoxN->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				collisionBoxN->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Ignore);
				collisionBoxN->BodyInstance.SetResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
				collisionBoxN->BodyInstance.SetResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
			}
				
			// Make clickable
			collisionBoxN->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
			collisionBoxN->SetSimulatePhysics(false);
			collisionBoxN->SetEnableGravity(true);

			collisionBoxN->SetMobility(EComponentMobility::Movable);  // New 190102
			collisionBoxN->OnBeginCursorOver.AddDynamic(this, &APop::CustomOnBeginMouseOver);
			collisionBoxN->OnEndCursorOver.AddDynamic(this, &APop::CustomOnEndMouseOver);
			collisionBoxN->OnClicked.AddDynamic(this, &APop::CustomOnClicked);

			// 190105: Try to make grabBoxes collide with Floor
			collisionBoxN->SetNotifyRigidBodyCollision(true);

			FinishAndRegisterComponent(collisionBoxN);  // Trying this 190102

			AddToGrabBoxesArray(collisionBoxN);
		}
	}
}

void APop::AddToGrabBoxesArray(UBoxComponent* collisionBox) {

	grabBoxes.Add(collisionBox);

	UE_LOG(LogTemp, Warning, TEXT("APop::AddToGrabBoxes: After adding grabBox %p (%s), grabBoxes has %d elements"),
		   collisionBox, *collisionBox->GetName(), grabBoxes.Num());

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
	UE_LOG(LogTemp, Warning, TEXT("APop::CustomOnClicked called, clickedComponent=%p"), clickedComponent);

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

	//AvreduGameMode* theGameMode = (AvreduGameMode*)GetWorld()->GetAuthGameMode();
	AvreduGameMode* theGameMode = GetGameMode();

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


bool APop::HasWeldedCollider() {

	if (grabBoxes.Num() > 0) {
		UBoxComponent* firstGrabBox = grabBoxes[0];


		UE_LOG(LogTemp, Warning,
			TEXT("APop::HasWeldedCollider: this-pop=%p, name=%s, pop BodyInstance=%p, firstGrabBox=%p, grabBox WeldParent=%p"),
			this,
			*thingRef->name,
			&mesh->BodyInstance,
			//&mesh->BodyInstance,
			firstGrabBox,
			firstGrabBox->BodyInstance.WeldParent);
		//return true;

		return ((firstGrabBox != nullptr) && (firstGrabBox->BodyInstance.WeldParent == &mesh->BodyInstance));
	}

	return false;
}
