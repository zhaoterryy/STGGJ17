// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ParentProjectile.generated.h"

UCLASS(Abstract)
class STGGJ17_API AParentProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	USphereComponent* CollisionComp;
	UProjectileMovementComponent* ProjMoveComp;
	UStaticMeshComponent* MeshComp;

	//SFX
	TArray<USoundCue*> ImpactSFX;
	UAudioComponent* ImpactSFXComp;
	

private:
	float LifeTime;
};
