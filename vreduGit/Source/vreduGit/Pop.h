// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "Pop.generated.h"

class AThing;
struct FTrafoArray;

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

	UMaterialInstanceDynamic* MaterialInstance1;
	UMaterialInstanceDynamic* MaterialInstance2;
	UMaterialInstanceDynamic* MaterialInstance3;
	UMaterialInstanceDynamic* MaterialInstance4;
	UMaterialInstanceDynamic* MaterialInstance5;
	UMaterialInstanceDynamic* MaterialInstance6;
	UMaterialInstanceDynamic* MaterialInstance7;
	UMaterialInstanceDynamic* MaterialInstance8;

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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

private:
	void AddGrabBoxes(TArray<FTransform>& grabBoxLocations);
	void AddGrabBoxes2Dim(TArray<FTrafoArray>& collisions2Dim);

	void LogComponentHierarchy(USceneComponent* rootComp);
	UActorComponent* GetRightMotionController();

};
