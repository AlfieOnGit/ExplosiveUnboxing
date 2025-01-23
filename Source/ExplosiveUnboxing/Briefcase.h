#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Hint.h"
#include "Engine/DataAsset.h"
#include "Public/OnCaseEvent.h"

#include "GameFramework/Actor.h"

#include "Briefcase.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXPLOSIVEUNBOXING_API UBriefcase : public UActorComponent
{
	GENERATED_BODY()
public:
	UBriefcase() : UBriefcase(-1, false, "") {}

	explicit UBriefcase(int32 InNumber, bool InIsDanger, FString InHintText)
		: Number(InNumber)
		, IsDanger(InIsDanger)
		, HintText(MoveTemp(InHintText)) {
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnCaseEvent* OnCaseClickEvent;

	UFUNCTION(BlueprintCallable, Category = "Briefcase")
	void ResetBriefcase(int32 NewNumber, bool NewIsDanger, FString NewHintText);

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	FString Open();

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	FString GetHintText() { return HintText; }

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void SetSelected(bool InSelected) { this->Selected = InSelected; }

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	bool CanOpen() { return !Opened; }

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	int32 OnSelect() { return Number; }

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnClick();

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	int32 GetCaseNumber() { return Number; }

private:	
	int32 Number;
	bool Opened = false;
	bool Selected = false;
	bool IsDanger = false;
	FString HintText;



protected:
	virtual void BeginPlay() override;
};
