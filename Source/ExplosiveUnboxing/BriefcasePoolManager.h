#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"

#include "HintManager.h"
#include "Briefcase.h"
#include "Hint.h"
#include <stack>

#include "BriefcasePoolManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPLOSIVEUNBOXING_API UBriefcasePoolManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBriefcasePoolManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BriefCasePool")
	UHintManager* MyHintManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
	AActor* HintManagerActor;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> BriefCasePrefab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BriefCasePool")
	UHintCollection* hintColTest;

	UPROPERTY(EditAnywhere, Category = "Spawn Points")
	TArray<AActor*> SpawnPointComponents;

	// Should be in TurnManger, but writing it here 
	TArray<int32> SelectBriefCaseData(int32 BriefCaseCount, int32* Solution);

	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	TArray<UBriefcase*> SpawnBriefCases(TArray<int32>& CaseNumbers, TArray<FString>& hintTexts, int32 Solution);

	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	void CleanPool();


private: 
	// Should be in TurnManger, but writing it here
	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	void AddListenerOnOpen(AActor* OnClickedActor);

	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	AActor* CreateNewBriefCase(const FVector MySpawnPoint, const FRotator MySpawnRot);

	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	AActor* RecycleUnusedBriefCase(const FVector MySpawnPoint, const FRotator MySpawnRot);

	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	UBriefcase* DefineBriefCaseData(AActor* BriefCase, int32 CaseNumber, bool IsDanger, FString HintText);

	TArray<AActor*> ActiveBriefCases;
	std::stack<AActor*> PooledBriefCases;

	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	int32 GetSolution(TArray<int32>& CaseNumbers);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
