// Fill out your copyright notice in the Description page of Project Settings.

#include "STGGJ17.h"
#include "WaterTitan.h"
#include "WaterProjectile.h"

AWaterTitan::AWaterTitan()
{
	Element = ETitanElement::Water;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshContainer(TEXT("SkeletalMesh'/Game/Characters/WaterTitan/Titan_Water_Rig_v01.Titan_Water_Rig_v01'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimContainer(TEXT("AnimBlueprint'/Game/Characters/WaterTitan/Animations/WaterAnimBP.WaterAnimBP_C'"));

	if (MeshContainer.Succeeded())
	{
		MeshComp->SetSkeletalMesh(MeshContainer.Object);
		MeshComp->SetAnimInstanceClass(AnimContainer.Object);
		MeshComp->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		MeshComp->SetRelativeLocation(FVector(40.f, 0.f, -60.f));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Missing mesh"));
	}

	//Movement SFX
	static ConstructorHelpers::FObjectFinder<USoundCue> movementCueLoader(TEXT("SoundCue'/Game/Audio/Water_Elemental_-Movement_Cue.Water_Elemental_-Movement_Cue'"));
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
	static ConstructorHelpers::FObjectFinder<USoundCue> attackCueLoader(TEXT("SoundCue'/Game/Audio/Water_Elemental_-Watergun_Shoot_Cue.Water_Elemental_-Watergun_Shoot_Cue'"));
	if (attackCueLoader.Succeeded())
	{
		AttackSFX.Add(attackCueLoader.Object);
		AttackSFXComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackSFX"));
		AttackSFXComp->bAutoActivate = false;
		AttackSFXComp->SetupAttachment(RootComponent);
		AttackSFXComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	// Claim SFX
	static ConstructorHelpers::FObjectFinder<USoundCue> claimCueLoader2(TEXT("SoundCue'/Game/Audio/Water_Elemental_-_Territory_Claim_Cue.Water_Elemental_-_Territory_Claim_Cue'"));

	if (claimCueLoader2.Succeeded())
	{
		ClaimSFX = (claimCueLoader2.Object);
		ClaimSFXComp = CreateDefaultSubobject<UAudioComponent>(TEXT("ClaimSFX"));
		ClaimSFXComp->bAutoActivate = false;
		ClaimSFXComp->SetupAttachment(RootComponent);
		ClaimSFXComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

void AWaterTitan::FireProjectile()
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
			
		AWaterProjectile* Projectile = GetWorld()->SpawnActor<AWaterProjectile>(AWaterProjectile::StaticClass(), SpawnTransform, SpawnInfo);
		
		FireRateCounter = FireRate;
	}
}

void AWaterTitan::PlaySplashSound()
{
	// Claim SFX
	if (ClaimSFX->IsValidLowLevelFast())
		ClaimSFXComp->SetSound(ClaimSFX);

	ClaimSFXComp->Play();
}

