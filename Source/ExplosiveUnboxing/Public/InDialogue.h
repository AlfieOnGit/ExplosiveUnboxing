#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OnGameEvent.h"
#include "InDialogue.generated.h"


USTRUCT(BlueprintType)
struct FUDialogueOption
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    FString OptionText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    UDataTable* NextDialogue;

    FUDialogueOption()
        : OptionText(TEXT("Default Logic"))
        , NextDialogue(nullptr) {
    }
};

UCLASS(BlueprintType, Blueprintable)
class EXPLOSIVEUNBOXING_API UInDialogue : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UDataTable* Table;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UOnGameEvent* Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    TArray<FUDialogueOption> DialogueChoice;
};
