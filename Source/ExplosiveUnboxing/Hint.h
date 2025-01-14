#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Hint.generated.h"

UCLASS(BlueprintType)
class EXPLOSIVEUNBOXING_API ULogic : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    UCondition* condition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    UStatement* statement;
};

UENUM(BlueprintType)
enum class Conditions : uint8
{
    IF UMETA(DisplayName = "If N"),
    OR UMETA(DisplayName = "Or N"),
    MAX
};

UENUM(BlueprintType)
enum class Statements : uint8
{
    THEN UMETA(DisplayName = "It is N"),
    NOT UMETA(DisplayName = "It is not N"),
    MAX
};


UCLASS(BlueprintType)
class EXPLOSIVEUNBOXING_API UStatement : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    int32 probability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    Statements statement;
};

UCLASS(BlueprintType)
class EXPLOSIVEUNBOXING_API UCondition : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    Conditions condition;
};


UCLASS(BlueprintType)
class EXPLOSIVEUNBOXING_API UHint : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    FString hintText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    TArray<ULogic*> logic;
};

USTRUCT(BlueprintType)
struct EXPLOSIVEUNBOXING_API FUCaseHint
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
    UHint* hint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
    int32 caseReference;

    FUCaseHint() : hint(nullptr), caseReference(0) {}
};