// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TitanAnimInstance.h"
#include "GameFramework/Character.h"
#include "ParentTitan.generated.h"

UENUM()
enum class ETitanElement : uint8
{
	Fire,
	Water,
	Rock
};

UCLASS(Abstract)
class STGGJ17_API AParentTitan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AParentTitan();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Damage(int damage);

	void GiveEnergy(int _energy) { Energy += _energy; }
	
	UFUNCTION(BlueprintCallable, Category="Getter")
	int GetHealth() { return Health; }

	ETitanElement GetElement() { return Element; }

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerFireProjectile();

	void ServerFireProjectile_Implementation();

	bool ServerFireProjectile_Validate();

	UFUNCTION(Reliable, Server, WithValidation)
		void ServerFireStream();

	void ServerFireStream_Implementation();

	bool ServerFireStream_Validate();
	
protected:

	ETitanElement Element;
	
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoomComp;

	UCharacterMovementComponent* MoveComp;

	UPROPERTY(Replicated)
	UTitanAnimInstance* AnimInstance;

	//SFX
	TArray<USoundCue*> AttackSFX;
	UAudioComponent* AttackSFXComp;

	TArray<USoundCue*> StreamSFX1;
	UAudioComponent* StreamSFXComp;

	UAudioComponent* ClaimSFXComp;
	USoundCue* ClaimSFX;

	USoundCue* MoveSFXCue;
	UAudioComponent* MoveSFXComp;

	const float FireRate = 0.5f;
	float FireRateCounter;

	virtual void FireProjectile();

	virtual void FireStream();

	virtual void PlaySplashSound() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Energy;

private:
	void MoveForward(float val);
	void MoveRight(float val);

	void OnShootProjectile();
	void OnShootProjectile_Release();

	void OnShootStream();
	void OnShootStream_Release();
};
