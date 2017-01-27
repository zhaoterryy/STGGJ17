// Fill out your copyright notice in the Description page of Project Settings.

#include "STGGJ17.h"
#include "FireTitan.h"
#include "FireProjectile.h"

AFireTitan::AFireTitan()
{
	Element = ETitanElement::Fire;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshContainer(TEXT("SkeletalMesh'/Game/Characters/FireTitan/fire_titan_rig_final.fire_titan_rig_final'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimContainer(TEXT("AnimBlueprint'/Game/Characters/FireTitan/Animations/FireAnimBP.FireAnimBP_C'"));

	if (MeshContainer.Succeeded())
	{
		MeshComp->SetSkeletalMesh(MeshContainer.Object);
		MeshComp->SetAnimInstanceClass(AnimContainer.Object);
		MeshComp->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		MeshComp->SetRelativeLocation(FVector(40.f, 0.f, -200.f));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Missing mesh"));
	}

	//Movement SFX
	static ConstructorHelpers::FObjectFinder<USoundCue> movementCueLoader(TEXT("SoundCue'/Game/Audio/Fire_Elemental_MVMT_Cue.Fire_Elemental_MVMT_Cue'"));
	if (movementCueLoader.Succeeded())
	{
		MoveSFXCue = movementCueLoader.Object;
		MoveSFXComp = CreateDefaultSubobject<UAudioComponent>(TEXT("MoveSFX"));
		// Begin Music for gameplay
		MoveSFXComp->bAutoActivate = false;

		MoveSFXComp->SetupAttachment(RootComponent);
		MoveSFXComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	//Attack SFX
	static ConstructorHelpers::FObjectFinder<USoundCue> attackCueLoader(TEXT("SoundCue'/Game/Audio/Fire_Elemental_Attk_-_Fireball_throw_Cue.Fire_Elemental_Attk_-_Fireball_throw_Cue'"));
	if (attackCueLoader.Succeeded())
	{
		AttackSFX.Add(attackCueLoader.Object);
		AttackSFXComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackSFX"));
		AttackSFXComp->bAutoActivate = false;
		AttackSFXComp->SetupAttachment(RootComponent);
		AttackSFXComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	// Claim SFX
	static ConstructorHelpers::FObjectFinder<USoundCue> claimCueLoader2(TEXT("SoundCue'/Game/Audio/Fire_Elemental_-_Territory_Claim_Cue.Fire_Elemental_-_Territory_Claim_Cue'"));

	if (claimCueLoader2.Succeeded())
	{
		ClaimSFX = (claimCueLoader2.Object);
		ClaimSFXComp = CreateDefaultSubobject<UAudioComponent>(TEXT("ClaimSFX"));
		ClaimSFXComp->bAutoActivate = false;
		ClaimSFXComp->SetupAttachment(RootComponent);
		ClaimSFXComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

void AFireTitan::FireProjectile()
{
	if (FireRateCounter < 0.f && GetWorld())
	{
		Super::FireProjectile();

		AnimInstance->bUsingAbility = true;
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;

		FTransform SpawnTransform = FTransform();
		SpawnTransform.SetLocation(GetActorLocation() + (GetActorForwardVector() * 260.f) + (GetActorUpVector() * 60.f));
		SpawnTransform.SetRotation(CameraComp->GetComponentRotation().Quaternion());

		AFireProjectile* Projectile = GetWorld()->SpawnActor<AFireProjectile>(AFireProjectile::StaticClass(), SpawnTransform, SpawnInfo);

		FireRateCounter = FireRate;
	}
}

void AFireTitan::PlaySplashSound()
{
	// Claim SFX
	if (ClaimSFX->IsValidLowLevelFast())
		ClaimSFXComp->SetSound(ClaimSFX);

	ClaimSFXComp->Play();
}