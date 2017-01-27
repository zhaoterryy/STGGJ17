// Fill out your copyright notice in the Description page of Project Settings.

#include "STGGJ17.h"
#include "RockProjectile.h"

ARockProjectile::ARockProjectile()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshContainer(TEXT("StaticMesh'/Game/Projectiles/rock_projectile.rock_projectile'"));

	if (MeshContainer.Succeeded())
	{
		MeshComp->SetStaticMesh(MeshContainer.Object);
		MeshComp->SetRelativeScale3D(FVector(5.f));
		MeshComp->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	}

	// Impact SFX
	static ConstructorHelpers::FObjectFinder<USoundCue> impactCueLoader1(TEXT("SoundCue'/Game/Audio/Rock_Elemental_-_Punch_HIT_Cue.Rock_Elemental_-_Punch_HIT_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> impactCueLoader2(TEXT("SoundCue'/Game/Audio/Rock_Elemental_-_Punch_HIT_2_Cue.Rock_Elemental_-_Punch_HIT_2_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> impactCueLoader3(TEXT("SoundCue'/Game/Audio/Rock_Elemental_-_Punch_HIT_3_Cue.Rock_Elemental_-_Punch_HIT_3_Cue'"));

	if (impactCueLoader1.Succeeded() && impactCueLoader2.Succeeded() && impactCueLoader2.Succeeded())
	{
		ImpactSFX.Add(impactCueLoader1.Object);
		ImpactSFX.Add(impactCueLoader2.Object);
		ImpactSFX.Add(impactCueLoader3.Object);
		ImpactSFXComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackSFX"));
		ImpactSFXComp->bAutoActivate = false;
		ImpactSFXComp->SetupAttachment(RootComponent);
		ImpactSFXComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	
}


