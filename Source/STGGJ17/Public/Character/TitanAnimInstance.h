// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "TitanAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STGGJ17_API UTitanAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UTitanAnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool bTakingDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool bUsingAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool bDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool bUsingStream;
};
