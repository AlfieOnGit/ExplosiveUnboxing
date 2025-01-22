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
	int32 GetSelectedCase();
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void SetSelectedCase(int32 CaseNumber);
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	bool IsSelectedCase(int32 CaseNumber);

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	int32 GetChosenCase();
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void SetChosenCase(int32 CaseNumber);

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	bool OpenAndCheckCase(int32 CaseNumber);

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	FString GetHintData(int32 CaseNumber);
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	int32 GetRandomUnopenedCase();

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void ClearCases();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	int32 SelectedCase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	int32 PlayerChosenCase;

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

	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
