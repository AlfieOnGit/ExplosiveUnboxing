
#include "BriefcasePoolManager.h"

// As Open events are from the player the player AActor must be passed here so the listener can be set
// They will tell this object when it has been opened
void UBriefcasePoolManager::AddListenerOnOpen(AActor* OnClickedActor)
{
    //OnClickedActor->OnClickedEventName.AddDynamic(this, &UBriefcase::Open);
}

UBriefcasePoolManager::UBriefcasePoolManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBriefcasePoolManager::CleanPool()
{    
    for (AActor* MyBriefCase : ActiveBriefCases) 
    {
        MyBriefCase->SetActorHiddenInGame(true);
        MyBriefCase->SetActorTickEnabled(false);
        PooledBriefCases.push(MyBriefCase);
    }
    ActiveBriefCases.Empty();
}

TArray<UBriefcase*> UBriefcasePoolManager::SpawnBriefCases(TArray<int32>& CaseNumbers, TArray<FString>& HintTexts, int32 Solution)
{
    TArray<UBriefcase*> BriefCases;
    int32 SpawnCount = SpawnPointComponents.Num();
    int SpawnIndex = 0;

    if (SpawnCount < 1) {
        UE_LOG(LogTemp, Warning, TEXT("No Spawn Points have been Setup: Please add pointers to USceneComponents to setup waypoints "));
        AActor* OwnerActor = GetOwner();

        if (OwnerActor)
            SpawnPointComponents.Add(OwnerActor);
        
    }

    for (int i = 0; i < CaseNumbers.Num(); i++)
    {
        AActor* MyBriefCase;
        AActor* SpawnPointActor = SpawnPointComponents[SpawnIndex];
        FVector SpawnLocation = SpawnPointActor->GetActorLocation();
        FRotator SpawnRotation = SpawnPointActor->GetActorRotation();

        if (PooledBriefCases.size() > 0)
            MyBriefCase = RecycleUnusedBriefCase(SpawnLocation, SpawnRotation);
        else
            MyBriefCase = CreateNewBriefCase(SpawnLocation, SpawnRotation);

        if (MyBriefCase) 
        {
            ActiveBriefCases.Add(MyBriefCase);
            UBriefcase* MyBriefcaseComponent = DefineBriefCaseData(MyBriefCase, CaseNumbers[i], CaseNumbers[i] == Solution, HintTexts[i]);

            if (MyBriefcaseComponent)
                BriefCases.Add(MyBriefcaseComponent);
        }

        SpawnIndex = (SpawnIndex + 1) % SpawnCount;
    }
    return BriefCases;
}

UBriefcase* UBriefcasePoolManager::DefineBriefCaseData(AActor* BriefCase, int32 CaseNumber, bool IsDanger, FString HintText)
{
    if (BriefCase)
    {
        UBriefcase* BriefCaseComponent = BriefCase->FindComponentByClass<UBriefcase>();
        if (BriefCaseComponent){
            BriefCaseComponent->ResetBriefcase(CaseNumber, IsDanger, HintText);
            return BriefCaseComponent;
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("There is no UBriefCase Component attatched to this Object: please add one"));
            return nullptr;
        }
    }
    return nullptr;
}

AActor* UBriefcasePoolManager::RecycleUnusedBriefCase(const FVector MySpawnPoint, const FRotator MySpawnRot)
{
    if (PooledBriefCases.size() == 0) 
        return nullptr;

    AActor* MyBriefCase = PooledBriefCases.top();
    PooledBriefCases.pop();

    if (MyBriefCase)
    {
        MyBriefCase->SetActorHiddenInGame(false);
        MyBriefCase->SetActorTickEnabled(true);
        MyBriefCase->SetActorLocation(MySpawnPoint);
        MyBriefCase->SetActorRotation(MySpawnRot);
    }
    return MyBriefCase;
}

AActor* UBriefcasePoolManager::CreateNewBriefCase(const FVector MySpawnPoint, const FRotator MySpawnRot)
{
    if (BriefCasePrefab)
        return GetWorld()->SpawnActor<AActor>(BriefCasePrefab, MySpawnPoint, MySpawnRot);

    UE_LOG(LogTemp, Warning, TEXT("No AActor* instance had been added to the BriefCasePoolManager: please allocate one"));
    return nullptr;
}


void UBriefcasePoolManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// All functions below here will be in TurnManager

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

int32 const RangeUpper = 15;
int32 const RangeLower = 1;

bool const ReOrderCases = true;
bool const AddCasesLinear = true;

TArray<int32> UBriefcasePoolManager::SelectBriefCaseData(int32 BriefCaseCount, int32* Solution)
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

int32 UBriefcasePoolManager::GetSolution(TArray<int32>& CaseNumbers)
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


void UBriefcasePoolManager::BeginPlay()
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
    SpawnBriefCases(CaseNumbers, HintText, solution);

    DebugScenario(CaseNumbers);
    DebugCaseHints(AllHints);
}


