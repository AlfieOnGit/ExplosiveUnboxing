#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OnCaseEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseEvent, int32, CaseNumber);

UCLASS()
class EXPLOSIVEUNBOXING_API UOnCaseEvent : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
	FOnCaseEvent CallEvent;

	UOnCaseEvent() = default;
};
