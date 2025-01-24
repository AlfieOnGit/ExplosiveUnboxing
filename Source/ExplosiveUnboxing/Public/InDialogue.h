#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OnGameEvent.h"
#include "InDialogue.generated.h"

UENUM(BlueprintType, Category = "Logic")
enum class OnTableEnd : uint8
{
    EndDialogue UMETA(DisplayName = "End Dialogue"),
    SwitchByYesNo UMETA(DisplayName = "Switch by Yes or No"),
    SwitchByIsNotGameOver UMETA(DisplayName = "Switch by IsGameOver"),
    ContinueToFirstOption UMETA(DisplayName = "Continue to first Option"),
    LoopUntilSolution UMETA(DisplayName = "Loop until solution then")
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
    OnTableEnd OnTableEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UInDialogue* DialogueYesChoice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UInDialogue* DialogueNoChoice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UInDialogue* DialogueSecretChoice;
};
