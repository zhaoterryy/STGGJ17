// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ParentTitan.h"
#include "WaterTitan.generated.h"

/**
 * 
 */
UCLASS()
class STGGJ17_API AWaterTitan : public AParentTitan
{
	GENERATED_BODY()

public:
	AWaterTitan();

private:
	virtual void FireProjectile() override;
	virtual void PlaySplashSound() override;
};
