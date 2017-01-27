// Fill out your copyright notice in the Description page of Project Settings.

#include "STGGJ17.h"
#include "HexTile.h"
#include "WaterTitan.h"
#include "RockTitan.h"
#include "FireTitan.h"
#include "STGGJ17GameMode.h"

// Sets default values
AHexTile::AHexTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	BoxColliderComp = CreateDefaultSubobject<UBoxComponent>("BoxCollider");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshContainer(TEXT("StaticMesh'/Game/Arena/hexMesh.hexMesh'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> GrassContainer(TEXT("Material'/Game/Arena/Textures/GRASS_Mat.GRASS_Mat'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> WaterContainer(TEXT("Material'/Game/Arena/Textures/Mat_water.Mat_water'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MagmaContainer(TEXT("Material'/Game/Arena/Textures/magma_Mat.magma_Mat'"));
	
	if (GrassContainer.Succeeded() && WaterContainer.Succeeded() && MagmaContainer.Succeeded())
	{
		GrassMat = GrassContainer.Object;
		MagmaMat = MagmaContainer.Object;
		WaterMat = WaterContainer.Object;
	}

	if (MeshContainer.Succeeded())
	{
		MeshComp->SetStaticMesh(MeshContainer.Object);
		MeshComp->SetRelativeScale3D(FVector(2.f));
		RootComponent = MeshComp;
	}

	BoxColliderComp->InitBoxExtent(FVector(75.f, 75.f, 20.f));
	BoxColliderComp->SetRelativeLocation(FVector(65.f, -111.f, 85.5f));
	BoxColliderComp->SetupAttachment(RootComponent);
	BoxColliderComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxColliderComp->OnComponentBeginOverlap.AddDynamic(this, &AHexTile::OnBeginOverlap);

}

// Called when the game starts or when spawned
void AHexTile::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld()) {
		GameMode = Cast<ASTGGJ17GameMode>(GetWorld()->GetAuthGameMode());
	}
}

// Called every frame
void AHexTile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AHexTile::ChangeMaterial(ETitanElement element)
{
	switch (element)
	{
		case ETitanElement::Water:
		{
			MeshComp->SetMaterial(0, WaterMat);
			break;
		}
		case ETitanElement::Fire:
		{
			MeshComp->SetMaterial(0, MagmaMat);
			break;
		}
		case ETitanElement::Rock:
		{
			MeshComp->SetMaterial(0, GrassMat);
			break;
		}
	}
	if (Role < ROLE_Authority)
	{
		ServerChangeMaterial(element);
	}
}

void AHexTile::ServerChangeMaterial_Implementation(ETitanElement element)
{
	ChangeMaterial(element);
}

bool AHexTile::ServerChangeMaterial_Validate(ETitanElement element)
{
	return true;
}

void AHexTile::OnBeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AParentTitan::StaticClass()))
	{
		ETitanElement TitanElement = Cast<AParentTitan>(OtherActor)->GetElement();
		switch (TitanElement) {
			case ETitanElement::Fire:
				if (MeshComp->GetMaterial(0) == WaterMat) {
					if (GameMode->WaterTitan != nullptr) {
						Cast<AWaterTitan>(GameMode->WaterTitan)->GiveEnergy(10);
					}
				}
				break;
			case ETitanElement::Water:
				if (MeshComp->GetMaterial(0) == GrassMat) {
					if (GameMode->RockTitan != nullptr) {
						Cast<ARockTitan>(GameMode->RockTitan)->GiveEnergy(10);
					}
				}
				break;
			case ETitanElement::Rock:
				if (MeshComp->GetMaterial(0) == MagmaMat) {
					if (GameMode->FireTitan != nullptr) {
						Cast<AFireTitan>(GameMode->FireTitan)->GiveEnergy(10);
					}
				}
				break;
		}
	}
}