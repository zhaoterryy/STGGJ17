// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ParentTitan.h"
#include "STGGJ17GameMode.h"
#include "GameFramework/Actor.h"
#include "HexTile.generated.h"

UCLASS()
class STGGJ17_API AHexTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexTile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void ChangeMaterial(ETitanElement element);

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerChangeMaterial(ETitanElement element);

	void ServerChangeMaterial_Implementation(ETitanElement element);

	bool ServerChangeMaterial_Validate(ETitanElement element);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UStaticMeshComponent* MeshComp;
	UBoxComponent* BoxColliderComp;
	
	//UMaterialInterface* DynMat;

	UMaterial* GrassMat;
	UMaterial* MagmaMat;
	UMaterial* WaterMat; 
	
	ASTGGJ17GameMode* GameMode;
};
