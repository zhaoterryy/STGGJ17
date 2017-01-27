// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ParentTitan.h"
#include "RockTitan.generated.h"

/**
 * 
 */
UCLASS()
class STGGJ17_API ARockTitan : public AParentTitan
{
	GENERATED_BODY()
	
public:
	ARockTitan();
	
private:
	virtual void FireProjectile() override;
	virtual void PlaySplashSound() override;
};
