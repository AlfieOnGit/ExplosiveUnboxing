
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
        USpriteComponent2D* SpriteComponent = BriefCase->FindComponentByClass<USpriteComponent2D>();

        if (CaseNumber > 0 && CaseNumber < 11)
            SpriteComponent->SetSprite(BriefcaseSpritesOrdered[CaseNumber]);
        else
            SpriteComponent->SetSprite(BriefcaseSpritesOrdered[0]);

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

void UBriefcasePoolManager::BeginPlay()
{
    Super::BeginPlay();
}


