#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Hint.h"
#include "HintCollection.h"

#include "HintManager.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXPLOSIVEUNBOXING_API UHintManager : public UActorComponent
{
	GENERATED_BODY()

public:

	// Example how to use: GetLevelHints({4, 7, 5, 9}, 7, UHintCol Reference)
	UFUNCTION(BlueprintCallable, Category = "Hints")
	TArray<FUCaseHint> GetLevelHints(TArray<int32> caseNumbers, int32 caseSolution, UHintCollection* HintData);


	UHintManager();

protected:
	virtual void BeginPlay() override;
};
