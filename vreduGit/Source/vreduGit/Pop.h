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
		UMaterialInstanceDynamic* MaterialInstance1;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MaterialInstance2;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MaterialInstance3;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MaterialInstance4;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MaterialInstance5;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MaterialInstance6;
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MaterialInstance7;
	UPROPERTY(VisibleAnywhere)
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

private:
	void AddGrabBoxes(TArray<FTransform>& grabBoxLocations);
	void AddGrabBoxes2Dim(TArray<FTrafoArray>& collisions2Dim);

	void LogComponentHierarchy(USceneComponent* rootComp);
	UActorComponent* GetRightMotionController();

};
