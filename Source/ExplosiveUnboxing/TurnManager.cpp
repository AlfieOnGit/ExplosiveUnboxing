#include "TurnManager.h"

void UTurnManager::ClearCases()
{
	for (int i = 0; i < MAX_CASES; i++) Cases[i] = nullptr;
	CaseCount = 0;
}


void DebugScenario(TArray<int32>& CaseNumbers)
{
    FString Total = TEXT("Around the room I could see mountains of briefcases piled high, each displaying a Number: ");
    for (auto& Case : CaseNumbers)
        Total += FString::FromInt(Case) + TEXT(" ");
    UE_LOG(LogTemp, Warning, TEXT("%s"), *Total);
}


void DebugCaseHints(TArray<FUCaseHint>& AllHints)
{
    UE_LOG(LogTemp, Warning, TEXT("Within each Briefcase I found a Hint: "));
    for (auto& Hints : AllHints)
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Hints.hintText);
    UE_LOG(LogTemp, Warning, TEXT("Just what could this all mean?"));
}


int32 constexpr RangeUpper = MAX_CASES;
int32 constexpr RangeLower = 1;

bool constexpr ReOrderCases = true;
bool constexpr AddCasesLinear = true;

TArray<int32> UTurnManager::SelectBriefCaseData(int32 const BriefCaseCount, int32* Solution)
{
    TArray<int32> FullRange;
    TArray<int32> CaseNumbers;

    int32 MyUpperRange = RangeUpper >= BriefCaseCount ? RangeUpper : BriefCaseCount;

    for (int32 i = RangeLower; i <= RangeUpper; ++i)
        FullRange.Add(i);

    if (!AddCasesLinear) {
        for (int32 i = FullRange.Num() - 1; i > 0; --i)
        {
            int32 RandomIndex = FMath::RandRange(0, i);
            FullRange.Swap(i, RandomIndex);
        }
    }

    for (int32 i = 0; i < BriefCaseCount && i < FullRange.Num(); ++i)
        CaseNumbers.Add(FullRange[i]);

    *Solution = GetSolution(CaseNumbers);
    if (ReOrderCases)
        CaseNumbers.Sort();

    return CaseNumbers;
}


int32 UTurnManager::GetSolution(TArray<int32>& CaseNumbers)
{
    int32 Solution;
    if (CaseNumbers.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, CaseNumbers.Num() - 1);
        Solution = CaseNumbers[RandomIndex];
    }
    else
        Solution = -1;

    return Solution;
}


void UTurnManager::BeginPlay()
{
    Super::BeginPlay();

    if (HintManagerActor)
        MyHintManager = HintManagerActor->FindComponentByClass<UHintManager>();
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("HintManagerActor reference is null!"));
        return;
    }

    int32 solution;
    TArray<int32> CaseNumbers = SelectBriefCaseData(10, &solution);
    auto AllHints = MyHintManager->GetLevelHints(CaseNumbers, solution, hintColTest);

    TArray<FString> HintText;
    for (auto& Hints : AllHints)
        HintText.Add(*Hints.hintText);
    BriefcasePoolManager->SpawnBriefCases(CaseNumbers, HintText, solution);

    DebugScenario(CaseNumbers);
    DebugCaseHints(AllHints);
}