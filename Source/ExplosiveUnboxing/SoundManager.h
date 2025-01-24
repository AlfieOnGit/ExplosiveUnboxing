#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoundManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPLOSIVEUNBOXING_API USoundManager : public UActorComponent
{
	GENERATED_BODY()

public:
	/**
	 * Plays sound as sound effect, meaning it will not be interrupted and will play over any currently playing sounds
	 * @param Sound Sound effect. If the input sound is set to looping, it will NEVER stop. Do NOT use this for looping sounds unless you want it to play forever
	 */
	UFUNCTION(BlueprintCallable, Category = "Sounds")
	void PlaySoundEffect(USoundBase* Sound) const;

	/**
	 * Plays a sound until interrupted. Will not loop: If you want looping sounds, set it in the USoundBase properties
	 * @param Sound Target USoundBase* or NULLPTR if you want to stop the current music
	 */
	UFUNCTION(BlueprintCallable, Category = "Sounds")
	void PlayMusic(USoundBase* Sound);

protected:
	UPROPERTY()
	UAudioComponent* CurrentSound = nullptr;
};
