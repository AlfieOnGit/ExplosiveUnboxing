#include "SoundManager.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


void USoundManager::PlaySoundEffect(USoundBase* Sound) const
{
	if (Sound) UGameplayStatics::PlaySound2D(this, Sound);
}


void USoundManager::PlayMusic(USoundBase* Sound)
{
	if (CurrentSound) CurrentSound->SetActive(false);
	CurrentSound = Sound ? UGameplayStatics::SpawnSound2D(this, Sound) : nullptr;
}


void USoundManager::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Playing music!"));
	PlayMusic(BackgroundSound);
	PlaySoundEffect(ExplosionSound);
}
