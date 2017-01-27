// Fill out your copyright notice in the Description page of Project Settings.

#include "STGGJ17.h"
#include "ParentProjectile.h"
#include "ParentTitan.h"
#include "HexTile.h"

// Sets default values
AParentProjectile::AParentProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProjMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));

	RootComponent = CollisionComp;

	CollisionComp->InitSphereRadius(20.0f);
	CollisionComp->SetSimulatePhysics(true);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->SetCollisionObjectType(ECC_PhysicsBody);
	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->SetEnableGravity(false);

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AParentProjectile::OnBeginOverlap);

	CollisionComp->BodyInstance.bUseCCD = true;

	ProjMoveComp->InitialSpeed = 2000.0f;
	ProjMoveComp->MaxSpeed = 2000.0f;
	ProjMoveComp->UpdatedComponent = CollisionComp;
	ProjMoveComp->ProjectileGravityScale = 0.f;
	ProjMoveComp->bRotationFollowsVelocity = true;

	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LifeTime = 5.f;
}

// Called when the game starts or when spawned
void AParentProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParentProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	LifeTime -= DeltaTime;

	if (LifeTime < 0.f)
	{
		Destroy();
	}
}

void AParentProjectile::OnBeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AParentTitan::StaticClass()))
	{
		// Impact SFX
		int index = FMath::RandRange(0, ImpactSFX.Num() - 1);
		if (ImpactSFX[index]->IsValidLowLevelFast())
			ImpactSFXComp->SetSound(ImpactSFX[index]);

		ImpactSFXComp->Play();

		Cast<AParentTitan>(OtherActor)->Damage(26);
	}
	Destroy();
}
