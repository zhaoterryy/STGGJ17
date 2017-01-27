// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ParentTitan.h"
#include "FireTitan.generated.h"

/**
 * 
 */
UCLASS()
class STGGJ17_API AFireTitan : public AParentTitan
{
	GENERATED_BODY()
	
public:
	AFireTitan();

private:
	virtual void FireProjectile() override;
	virtual void PlaySplashSound() override;
};
