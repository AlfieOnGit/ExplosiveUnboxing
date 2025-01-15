#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoundManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPLOSIVEUNBOXING_API USoundManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	USoundBase* DrumrollSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	USoundBase* BackgroundSound;

	/**
	 * Plays sound as sound effect, meaning it will not be interrupted and will play over any currently playing sounds
	 * @param Sound Sound effect. If the input sound is set to looping, it will NEVER stop. Do NOT use this for looping sounds unless you want it to play forever
	 */
	UFUNCTION(BlueprintCallable, Category = "Sounds")
	void PlaySoundEffect(USoundBase* Sound) const;

	UFUNCTION(BlueprintCallable, Category = "Sounds")
	void PlayMusic(USoundBase* Sound);

protected:
	UPROPERTY()
	UAudioComponent* CurrentSound = nullptr;
	
	virtual void BeginPlay() override; // TODO: Remove, this is just for testing
};
