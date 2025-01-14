#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Hint.generated.h"

UCLASS(BlueprintType)
class EXPLOSIVEUNBOXING_API ULogic : public UObject
{
    GENERATED_BODY()
};

UENUM(BlueprintType, Category = "Hints")
enum class Conditions : uint8
{
    IF UMETA(DisplayName = "If N"),
    WHILE UMETA(DisplayName = "While N"),
    MAX
};

UENUM(BlueprintType, Category = "Hints")
enum class Conjunctives : uint8
{
    OR UMETA(DisplayName = "Or"),
    AND UMETA(DisplayName = "And"),
    MAX
};

UENUM(BlueprintType, Category = "Hints")
enum class Subject : uint8
{
    SOLUTION UMETA(DisplayName = "Solution"),
    DANGER UMETA(DisplayName = "Danger"),   
    MAX
};

UCLASS(BlueprintType)
class EXPLOSIVEUNBOXING_API USubjects: public ULogic
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    Subject subject;
};

UCLASS(BlueprintType)
class EXPLOSIVEUNBOXING_API UCondition : public ULogic
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    Conditions condition;
};
UCLASS(BlueprintType)
class EXPLOSIVEUNBOXING_API UConjunctive : public ULogic
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    Conjunctives conjunctive;
};



UENUM(BlueprintType, Category = "Hints")
enum class Statements : uint8
{
    EQUAL UMETA(DisplayName = "CASENUMBER is P"),
    NOT UMETA(DisplayName = "CASENUMBER is not P"),

    GREATER UMETA(DisplayName = "N is greater than CASENUMBER"),
    LESS UMETA(DisplayName = "N is less than CASENUMBER"),

    LYING UMETA(DisplayName = "CASENUMBER is lying"),
    TRUTHFUL UMETA(DisplayName = "CASENUMBER is truthful"),

    PLUSOFFSET UMETA(DisplayName = "CASENUMBER is P plus NUMBER"),
    NEGATIVEOFFSET UMETA(DisplayName = "CASENUMBER is P negative NUMBER"),


    MAX
};


UCLASS(BlueprintType)
class EXPLOSIVEUNBOXING_API UStatement : public ULogic
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    UStatement* inverse;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    int32 probability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    TArray<USubjects*> subjects;
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