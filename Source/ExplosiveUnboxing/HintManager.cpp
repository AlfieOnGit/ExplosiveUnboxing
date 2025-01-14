#include "HintManager.h"

UHintManager::UHintManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHintManager::BeginPlay() { Super::BeginPlay(); }


TArray<FUCaseHint> UHintManager::GetLevelHints(TArray<int32> caseNumbers, int32 caseSolution, UHintCollection* HintData)
{
    TArray<FUCaseHint> ChosenHints;
    ChosenHints.SetNum(caseNumbers.Num());

    if (HintData->HintCollections.Num() <= 0)
        return ChosenHints;

    for (int i = 0; i < ChosenHints.Num(); i++)
    {
        UHint* hintType = SelectHint(HintData);

        FUCaseHint NewCaseHint;
        NewCaseHint.hint = hintType;
        NewCaseHint.caseReference = 7;
    }

    return ChosenHints;
}

int32 DetermineCaseReference(UHint* hintType, TArray<FUCaseHint>* hints)
{
    return 0;
}

UHint* UHintManager::SelectHint(UHintCollection* HintData)
{
    int32 RandomIndex = FMath::RandRange(0, HintData->HintCollections.Num() - 1);
    return HintData->HintCollections[RandomIndex];
}

