// Fill out your copyright notice in the Description page of Project Settings.

#include "STGGJ17.h"
#include "ParentTitan.h"
#include "HexTile.h"
#include "STGGJ17GameMode.h"

// Sets default values
AParentTitan::AParentTitan()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(300.f);
	GetCapsuleComponent()->SetCapsuleRadius(150.f);
	MeshComp = GetMesh();
	MeshComp->SetupAttachment(RootComponent);

	

	CameraBoomComp = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");

	MoveComp = GetCharacterMovement();

	CameraBoomComp->SocketOffset = FVector(100.f, 0.f, 200.f);
	CameraBoomComp->TargetArmLength = 900.f;
	CameraBoomComp->bUsePawnControlRotation = true;
	CameraBoomComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(CameraBoomComp);

	MoveComp->MaxWalkSpeed = 2000.f;

	Health = 100;
	Energy = 0;
}

// Called when the game starts or when spawned
void AParentTitan::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UTitanAnimInstance>(MeshComp->GetAnimInstance());
	//hellooooo
	//if element is water, cast<stggj17gamemode>(Getgamemode())->Water == this;
	switch (Element) {
		case ETitanElement::Fire: {
			Cast<ASTGGJ17GameMode>(GetWorld()->GetAuthGameMode())->FireTitan = this; break;
		}
		case ETitanElement::Water: {
			Cast<ASTGGJ17GameMode>(GetWorld()->GetAuthGameMode())->WaterTitan = this; break;
		}
		case ETitanElement::Rock: {
			Cast<ASTGGJ17GameMode>(GetWorld()->GetAuthGameMode())->RockTitan = this; break;
		}
	}
}

// Called every frame
void AParentTitan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireRateCounter -= DeltaTime;
	if (AnimInstance->bUsingStream) {
		FireStream();
	}
	else if (AnimInstance->bUsingAbility) {
		FireProjectile();
	}

}

// Called to bind functionality to input
void AParentTitan::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &AParentTitan::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AParentTitan::MoveRight);
	InputComponent->BindAxis("Turn", this, &AParentTitan::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AParentTitan::AddControllerPitchInput);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AParentTitan::OnShootProjectile);
	InputComponent->BindAction("Fire", IE_Released, this, &AParentTitan::OnShootProjectile_Release);
	InputComponent->BindAction("ShootStream", IE_Pressed, this, &AParentTitan::OnShootStream);
	InputComponent->BindAction("ShootStream", IE_Released, this, &AParentTitan::OnShootStream_Release);
}

void AParentTitan::MoveForward(float val)
{
	if (val != 0.f)
	{
		const FRotator Rotation = GetActorRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, val);

		//SFX
		if (!MoveSFXComp->IsPlaying())
		{
			if (MoveSFXCue->IsValidLowLevelFast())
				MoveSFXComp->SetSound(MoveSFXCue);

			MoveSFXComp->Play();
		}
	}
}

void AParentTitan::MoveRight(float val)
{
	if (val != 0.f)
	{
		const FRotator Rotation = GetActorRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		AddMovementInput(Direction, val);

		//SFX
		if (!MoveSFXComp->IsPlaying())
		{
			if (MoveSFXCue->IsValidLowLevelFast())
				MoveSFXComp->SetSound(MoveSFXCue);

			MoveSFXComp->Play();
		}
	}
}

void AParentTitan::OnShootProjectile()
{
	AnimInstance->bUsingAbility = true;
	FireProjectile();

	// call on server if client
	if (Role < ROLE_Authority)
	{
		ServerFireProjectile();
	}
}

void AParentTitan::OnShootProjectile_Release()
{
	AnimInstance->bUsingAbility = false;
}

void AParentTitan::ServerFireProjectile_Implementation()
{
	FireProjectile();
}

bool AParentTitan::ServerFireProjectile_Validate()
{
	return true;
}

void AParentTitan::OnShootStream()
{
	AnimInstance->bUsingStream = true;
	FireStream();
}

void AParentTitan::OnShootStream_Release()
{
	AnimInstance->bUsingStream = false;
}

void AParentTitan::ServerFireStream_Implementation()
{
	FireStream();
}

bool AParentTitan::ServerFireStream_Validate()
{
	return true;
}

void AParentTitan::Damage(int damage)
{
	if (Health <= 0.f)
	{
		Destroy();
	}
	else
	{
		Health -= damage;
	}
}

void AParentTitan::FireProjectile()
{
	int index = FMath::RandRange(0, AttackSFX.Num() - 1);
	if (AttackSFX[index]->IsValidLowLevelFast())
		AttackSFXComp->SetSound(AttackSFX[index]);

	AttackSFXComp->Play();
}

void AParentTitan::FireStream()
{
	auto *Hit = new FHitResult;
	FVector Start = GetActorLocation() + GetActorForwardVector() * 200.f;
	FVector rot = CameraComp->GetForwardVector();
	FVector End = rot * 10000.f;

	//FCollisionQueryParams traceParams = FCollisionQueryParams();
	//const FName TraceTag = FName("MyTT");
	//GetWorld()->DebugDrawTraceTag = TraceTag;
	//traceParams.TraceTag = TraceTag;

	if (GetWorld()->LineTraceSingleByChannel(*Hit, Start, End, ECC_Camera)) {
		if (Hit->GetActor()->IsA(AHexTile::StaticClass())) {
			//UE_LOG(LogTemp, Warning, TEXT("hello"));
			PlaySplashSound();
			Cast<AHexTile>(Hit->GetActor())->ChangeMaterial(Element);
		}
	}
}


void AParentTitan::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to every client, no special condition required
	DOREPLIFETIME(AParentTitan, AnimInstance);
	/*DOREPLIFETIME(AParentTitan, bTakingDamage);
	DOREPLIFETIME(AParentTitan, bUsingAbility);
	DOREPLIFETIME(AParentTitan, bUsingStream);
	DOREPLIFETIME(AParentTitan, bDeath);*/
	/* If we did not display the current inventory on the player mesh we could optimize replication by using this replication condition. */
	/* DOREPLIFETIME_CONDITION(ASCharacter, Inventory, COND_OwnerOnly);*/
}
