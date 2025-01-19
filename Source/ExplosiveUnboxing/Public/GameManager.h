#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExplosiveUnboxing/TurnManager.h"
#include "GameManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPLOSIVEUNBOXING_API UGameManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	/**
	 * Resets score
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void OnNewGame();
	
	UFUNCTION(BlueprintCallable, Category = "Game")
	void OnPlayerChoose();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void OnGameOver();

	
	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetScore(int const NewScore) { this->Score = NewScore; }

	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "Game")
	int GetScore() const { return Score; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int Score = 0; // Score for current or, if no ongoing round, most recent round

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	UTurnManager* TurnManager;
};
