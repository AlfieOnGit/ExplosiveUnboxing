#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EventDataAsset.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCustomEvent, int32, CaseNumber);

UCLASS()
class EXPLOSIVEUNBOXING_API UEventDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
	FOnCustomEvent CallEvent;

	UEventDataAsset() = default;
};
