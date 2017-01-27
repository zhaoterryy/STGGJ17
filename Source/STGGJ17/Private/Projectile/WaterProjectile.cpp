// Fill out your copyright notice in the Description page of Project Settings.

#include "STGGJ17.h"
#include "WaterProjectile.h"

AWaterProjectile::AWaterProjectile()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshContainer(TEXT("StaticMesh'/Game/Projectiles/water_projectile.water_projectile'"));

	if (MeshContainer.Succeeded())
	{
		MeshComp->SetStaticMesh(MeshContainer.Object);
		MeshComp->SetRelativeScale3D(FVector(10.f));
		MeshComp->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	}

	// Impact SFX
	static ConstructorHelpers::FObjectFinder<USoundCue> impactCueLoader1(TEXT("SoundCue'/Game/Audio/Water_Elemental_-ATTK_HIT_Cue.Water_Elemental_-ATTK_HIT_Cue'"));

	if (impactCueLoader1.Succeeded())
	{
		ImpactSFX.Add(impactCueLoader1.Object);
		ImpactSFXComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackSFX"));
		ImpactSFXComp->bAutoActivate = false;
		ImpactSFXComp->SetupAttachment(RootComponent);
		ImpactSFXComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}