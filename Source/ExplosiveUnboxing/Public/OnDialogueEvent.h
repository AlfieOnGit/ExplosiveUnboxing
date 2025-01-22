#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InDialogue.h"
#include "OnDialogueEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueEvent, UInDialogue*, Dialogue);

UCLASS()
class EXPLOSIVEUNBOXING_API UOnDialogueEvent : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category = "Hints")
	FOnDialogueEvent CallEvent;

	UOnDialogueEvent() = default;
};
