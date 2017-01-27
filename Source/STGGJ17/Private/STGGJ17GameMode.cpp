// Fill out your copyright notice in the Description page of Project Settings.

#include "STGGJ17.h"
#include "STGGJ17GameMode.h"
#include "RockTitan.h"
#include "WaterTitan.h"
#include "FireTitan.h"

ASTGGJ17GameMode::ASTGGJ17GameMode()
{
	DefaultPawnClass = ARockTitan::StaticClass();

	static ConstructorHelpers::FObjectFinder<USoundCue> warDrumsCueLoader(TEXT("SoundCue'/Game/Audio/Intense_Wardrums_Gameplay_LOOP_Cue.Intense_Wardrums_Gameplay_LOOP_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> warDrumsCueLoader2(TEXT("SoundCue'/Game/Audio/Heavy_Wardrums_Gameplay_Short_LOOP_Cue.Heavy_Wardrums_Gameplay_Short_LOOP_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> soundscapeCueLoader(TEXT("SoundCue'/Game/Audio/Soundscape_-_No_Rain_Windy_Mountain_Storm_Cue.Soundscape_-_No_Rain_Windy_Mountain_Storm_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> soundscapeCueLoader2(TEXT("SoundCue'/Game/Audio/Windy_Mountain_Soundscape_-_Gameplay_Cue.Windy_Mountain_Soundscape_-_Gameplay_Cue'"));

	if (warDrumsCueLoader.Succeeded() && warDrumsCueLoader2.Succeeded())
	{
		m_BGMusicCues.Add(warDrumsCueLoader.Object);
		m_BGMusicCues.Add(warDrumsCueLoader2.Object);
		m_BGMusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMusic"));
	}

	if (soundscapeCueLoader.Succeeded() && soundscapeCueLoader2.Succeeded())
	{
		m_BGSoundscapesCues.Add(soundscapeCueLoader.Object);
		m_BGSoundscapesCues.Add(soundscapeCueLoader2.Object);
		m_BGSoundscapeComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BGSoundscape"));
	}

}

// Called when the game starts or when spawned
void ASTGGJ17GameMode::BeginPlay()
{
	Super::BeginPlay();

	// Begin war drums sound for gameplay
	m_BGMusicComponent->bAutoActivate = false;

	//m_BGMusicComponent->SetupAttachment(RootComponent);
	m_BGMusicComponent->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));

	// War Drums sound
	int index = FMath::RandRange(0, m_BGMusicCues.Num() - 1);
	if (m_BGMusicCues[index]->IsValidLowLevelFast())
		m_BGMusicComponent->SetSound(m_BGMusicCues[index]);

	m_BGMusicComponent->Play();

	// Begin Music for gameplay
	m_BGSoundscapeComponent->bAutoActivate = false;
	//m_BGSoundscapeComponent->SetupAttachment(RootComponent);
	m_BGSoundscapeComponent->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));

	// War Drums sound
	int index2 = FMath::RandRange(0, m_BGSoundscapesCues.Num() - 1);
	if (m_BGSoundscapesCues[index2]->IsValidLowLevelFast())
		m_BGSoundscapeComponent->SetSound(m_BGSoundscapesCues[index2]);

	m_BGSoundscapeComponent->Play();
}
