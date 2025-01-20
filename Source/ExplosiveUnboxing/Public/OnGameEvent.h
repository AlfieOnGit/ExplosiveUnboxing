#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OnGameEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEvent);

UCLASS()
class EXPLOSIVEUNBOXING_API UOnGameEvent : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
	FOnGameEvent CallEvent;

	UOnGameEvent() = default;
};
