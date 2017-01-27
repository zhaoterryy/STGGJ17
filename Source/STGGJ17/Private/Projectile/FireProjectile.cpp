// Fill out your copyright notice in the Description page of Project Settings.

#include "STGGJ17.h"
#include "FireProjectile.h"

AFireProjectile::AFireProjectile()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshContainer(TEXT("StaticMesh'/Game/Projectiles/fire_projectile.fire_projectile'"));

	if (MeshContainer.Succeeded())
	{
		MeshComp->SetStaticMesh(MeshContainer.Object);
		MeshComp->SetRelativeScale3D(FVector(5.f));
		MeshComp->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	}

	// Impact SFX
	static ConstructorHelpers::FObjectFinder<USoundCue> impactCueLoader1(TEXT("SoundCue'/Game/Audio/Fire_Elemental_Attk_-_Fireball_HIT_Cue.Fire_Elemental_Attk_-_Fireball_HIT_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> impactCueLoader2(TEXT("SoundCue'/Game/Audio/Fire_Elemental_-_Fireball_hit2_Cue.Fire_Elemental_-_Fireball_hit2_Cue'"));

	if (impactCueLoader1.Succeeded() && impactCueLoader2.Succeeded())
	{
		ImpactSFX.Add(impactCueLoader1.Object);
		ImpactSFX.Add(impactCueLoader2.Object);
		ImpactSFXComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackSFX"));
		ImpactSFXComp->bAutoActivate = false;
		ImpactSFXComp->SetupAttachment(RootComponent);
		ImpactSFXComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	
}


