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
