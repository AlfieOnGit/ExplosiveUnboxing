
#include "BriefcasePoolManager.h"


UBriefcasePoolManager::UBriefcasePoolManager()
{
	
	PrimaryComponentTick.bCanEverTick = true;

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

    TArray<int32> CaseNumbers1 = { 1, 2, 3, 4, 5 };

    FString Total = TEXT("Around the room I could see mountains of briefcases piled high, each displaying a Number: ");
    for (auto& Case : CaseNumbers1)
        Total += FString::FromInt(Case) + TEXT(" ");

    UE_LOG(LogTemp, Warning, TEXT("%s"), *Total);
    auto AllHints = MyHintManager->GetLevelHints(CaseNumbers1, 4, hintColTest);
    UE_LOG(LogTemp, Warning, TEXT("Within each Briefcase I found a Hint: "));

    for (auto& Hints : AllHints)
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Hints.hintText);

    UE_LOG(LogTemp, Warning, TEXT("Just what could this all mean?"));
}


void UBriefcasePoolManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

