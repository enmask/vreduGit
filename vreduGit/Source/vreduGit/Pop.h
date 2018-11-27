// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "Pop.generated.h"

class AThing;

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

#if 1
	UPROPERTY(VisibleAnywhere)
		URuntimeMeshComponent* mesh;
#else
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;
#endif

	UMaterialInstanceDynamic* MaterialInstance;
	UMaterialInstanceDynamic* MaterialInstance2;

	// Tried this for collision. Probably remove soon!
	//UPROPERTY(EditAnywhere)
	//	UBoxComponent* box;

	UPROPERTY(EditAnywhere)
		UStaticMesh* meshCube;

	UPROPERTY(VisibleAnywhere)
		TArray<UBoxComponent*> grabBoxes;

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

	//Functions to handle the interaction
	UFUNCTION()
		void CustomOnClicked(UPrimitiveComponent* clickedComponent, FKey inKey);


private:
	void AddGrabBoxes(TArray<FTransform>& grabBoxLocations);


};
