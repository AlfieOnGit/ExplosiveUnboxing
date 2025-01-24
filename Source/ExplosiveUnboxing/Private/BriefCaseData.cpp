#include "BriefCaseData.h"

UBriefCaseData::UBriefCaseData()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBriefCaseData::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


UBriefcase* UBriefCaseData::GetCase(int32 CaseNumber) {
    for (auto& Case : Cases)
    {
        if (Case->GetCaseNumber() == CaseNumber)
            return Case;
    }
    return nullptr;
}

void UBriefCaseData::SetSelectedCase(int32 CaseNumber)
{
    SelectedCase = CaseNumber; 
    // Move case to table(); => to be done
}

int32 UBriefCaseData::GetRandomUnopenedCase()
{
    for (auto& Case : Cases)
    {
        auto CaseNumber = Case->GetCaseNumber();
        if (Case->CanOpen() && CaseNumber != PlayerChosenCase)
            return CaseNumber;
    }
    return PlayerChosenCase;
}

bool UBriefCaseData::OpenAndCheckCase(int32 CaseNumber) 
{
    // Move case to pile(); => to be done
    auto Case = GetCase(CaseNumber);
    HintText = Case->Open();
    SelectedCase = -1;
    OpenedCase = CaseNumber;
    return true;
}


void UBriefCaseData::ClearCases()
{
    Cases.Empty();
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

TArray<int32> UBriefCaseData::SelectBriefCaseData(int32 const BriefCaseCount)
{
    TArray<int32> FullRange;
    TArray<int32> CaseNumbers;

    int32 MyUpperRange = RangeUpper >= BriefCaseCount ? RangeUpper : BriefCaseCount;

    for (int32 i = RangeLower; i <= MyUpperRange; ++i)
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

    Solution = PickSolution(CaseNumbers);
    if (ReOrderCases)
        CaseNumbers.Sort();

    return CaseNumbers;
}


int32 UBriefCaseData::PickSolution(TArray<int32>& CaseNumbers)
{
    int32 NewSolution;
    if (CaseNumbers.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, CaseNumbers.Num() - 1);
        NewSolution = CaseNumbers[RandomIndex];
    }
    else
        NewSolution = -1;

    return NewSolution;
}

void UBriefCaseData::BeginPlay()
{
    Super::BeginPlay();

    if (AActor* Owner = GetOwner())
    {
        MyHintManager = Owner->FindComponentByClass<UHintManager>();
        BriefcasePoolManager = Owner->FindComponentByClass<UBriefcasePoolManager>();
    }

    TArray<int32> CaseNumbers = SelectBriefCaseData(10);
    auto AllHints = MyHintManager->GetLevelHints(CaseNumbers, Solution, hintColTest);

    TArray<FString> HintTextArray;
    for (auto& Hints : AllHints)
        HintTextArray.Add(*Hints.hintText);
    Cases = BriefcasePoolManager->SpawnBriefCases(CaseNumbers, HintTextArray, Solution);

    UE_LOG(LogTemp, Warning, TEXT("%d"), Solution);

    //DebugScenario(CaseNumbers);
    //DebugCaseHints(AllHints);
}