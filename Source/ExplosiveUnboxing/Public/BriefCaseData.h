#pragma once

#include "CoreMinimal.h"
#include "ExplosiveUnboxing/Briefcase.h"
#include "ExplosiveUnboxing/BriefcasePoolManager.h"
#include "ExplosiveUnboxing/HintManager.h"
#include "Components/ActorComponent.h"
#include "BriefCaseData.generated.h"

#define MAX_CASES 15

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPLOSIVEUNBOXING_API UBriefCaseData : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBriefCaseData();


	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	int32 GetSelectedCase() { return SelectedCase; }
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void SetSelectedCase(int32 CaseNumber);

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	int32 GetOpenedCase() { return OpenedCase; }
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void SetOpenedCase(int32 CaseNumber) { OpenedCase = CaseNumber;  }

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	int32 GetChosenCase() { return PlayerChosenCase; }
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void SetChosenCase(int32 CaseNumber) { PlayerChosenCase = CaseNumber; }

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	bool IsSelectedCase(int32 CaseNumber) { return CaseNumber == SelectedCase; }

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	bool OpenAndCheckCase(int32 CaseNumber);

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	FString GetHintData(int32 CaseNumber) { return HintText; }

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	int32 GetRandomUnopenedCase();

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	bool IsSolution(int32 CaseNumber) { return CaseNumber == Solution; }

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void ClearCases();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	int32 SelectedCase = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	int32 OpenedCase = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	int32 PlayerChosenCase = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	FString HintText = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	int32 Solution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UHintManager* MyHintManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UHintCollection* hintColTest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UBriefcasePoolManager* BriefcasePoolManager;

	TArray<UBriefcase*> Cases;
	TArray<int32> SelectBriefCaseData(int32 BriefCaseCount);

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	int32 PickSolution(TArray<int32>& CaseNumbers);

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	UBriefcase* GetCase(int32 CaseNumber);

	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
