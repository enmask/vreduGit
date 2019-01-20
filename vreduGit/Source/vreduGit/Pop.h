// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "Pop.generated.h"

class AThing;
struct FTrafoArray;
class AvreduGameMode;

UCLASS()
class VREDUGIT_API APop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APop();

	void init(AThing* thing, FTransform trafo);
	void init2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnyWhere)
		AThing* thingRef;

	UPROPERTY(VisibleAnywhere)
		URuntimeMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIAtom1;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIAtom2;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIAtom3;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIAtom4;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIAtom5;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIAtom6;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIAtom7;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIAtom8;

	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIWire1;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIWire2;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIWire3;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIWire4;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIWire5;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIWire6;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIWire7;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MIWire8;

	UPROPERTY(EditAnywhere)
		UStaticMesh* meshCube;

	UPROPERTY(VisibleAnywhere)
		TArray<UBoxComponent*> grabBoxes;

	UPROPERTY(VisibleAnywhere)
		bool picked;

	//
	// API methods
	//

	// Highlight (or de-highlight) the Pop, or a part of it, in a color to make it stand out to the user
	void Highlight(int sectionIx, int lightLevel);
	void HighlightWireChild(int sectionIx, int lightLevel);


	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Only for logging
	FString ECollisionEnabled2Str(ECollisionEnabled::Type eCollEnabled);
	FString ECollisionChannel2Str(ECollisionChannel eCollChannel);
	FString ECollisionResponse2Str(ECollisionResponse eCollResponse);

	AvreduGameMode* GetGameMode();

	FString ToString();
	
	void BuildMesh();

	void TestSetupCollisionBox();
	void TestSetupPhysics();
	void TestSetupMaterial();

	//Functions to handle the interaction
	UFUNCTION()
		void CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
		void CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
		void CustomOnClicked(UPrimitiveComponent* clickedComponent, FKey inKey);

	void LogComponentHierarchy(USceneComponent* rootComp);

	UFUNCTION()
		bool HasWeldedCollider();


private:
	void AddGrabBoxes(TArray<FTransform>& grabBoxLocations);
	void AddGrabBoxes2Dim(TArray<FTrafoArray>& collisions2Dim);

	void AddToGrabBoxesArray(UBoxComponent* collisionBox);

	UActorComponent* GetRightMotionController();

	UMaterialInstanceDynamic* section2MIWire(int sectionIx);


};
