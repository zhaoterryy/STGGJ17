// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ParentTitan.h"
#include "GameFramework/GameMode.h"
#include "STGGJ17GameMode.generated.h"

/**
 * 
 */
UCLASS()
class STGGJ17_API ASTGGJ17GameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ASTGGJ17GameMode();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<USoundCue*> m_BGMusicCues;
	TArray<USoundCue*> m_BGSoundscapesCues;

	UAudioComponent* m_BGMusicComponent;
	UAudioComponent* m_BGSoundscapeComponent;

	AParentTitan* WaterTitan;
	AParentTitan* RockTitan;
	AParentTitan* FireTitan;
};
