#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Hint.generated.h"

UENUM(BlueprintType, Category = "Logic")
enum class LogicTypes : uint8
{ 
    Unassigned UMETA(DisplayName = "Unassigned"), // Default
    Conjunctive UMETA(DisplayName = "Conjunctive"), // And, Or, ..
    Conditions UMETA(DisplayName = "Conditions"), // If => then
    Statements UMETA(DisplayName = "Statements"), // Logic statement
    Basis UMETA(DisplayName = "Basis"), // Not, Is   
    Identifiers UMETA(DisplayName = "Identifiers"), // Identifiers to find: IDENTIFIER is STATEMENT given ROLES
    Roles UMETA(DisplayName = "Roles"), // A parent class for IDENTIFIERS, IDENTIFIERS can be roles, but not vice versa. Roles can not be solved for as they are already known with a single answer
    MAX
};

UENUM(BlueprintType, Category = "Logic")
enum class ConjunctivesTypes : uint8
{
    OR UMETA(DisplayName = "Or"),
    AND UMETA(DisplayName = "And")
};


UENUM(BlueprintType, Category = "Logic")
enum class LogicStatmentTypes : uint8
{
    Is,
    IsGreater,
    IsLess,
    IsBetween,
    IsPosOffset,
    IsNegOffset
};


USTRUCT(BlueprintType)
struct FLogic
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    FString Logic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    FString DisplayLogic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    LogicTypes LogicType;

    FLogic()
        : Logic(TEXT("Default Logic"))
        , DisplayLogic(TEXT("Default Display Logic"))
        , LogicType(LogicTypes::Unassigned) {
    }

    FLogic(const FString& InLogic, const FString& InDisplayLogic, LogicTypes InLogicType)
        : Logic(InLogic)
        , DisplayLogic(InDisplayLogic)
        , LogicType(InLogicType) {
    }

    virtual ~FLogic() = default;

    virtual bool operator==(const FLogic& Other) const
    {
        if (LogicType != Other.LogicType)
            return false;
        return Logic == Other.Logic && DisplayLogic == Other.DisplayLogic;
    }
};

USTRUCT(BlueprintType)
struct FLogicRoles : public FLogic
{
    GENERATED_BODY()

    FLogicRoles(const FString& InLogic, const FString& InDisplayLogic, LogicTypes InLogicType)
        : FLogic(InLogic, InDisplayLogic, InLogicType) {
    }

    FLogicRoles()
        : FLogic(TEXT("Default Subject Logic"), TEXT("Default Subject Display Logic"), LogicTypes::Roles) {
    }

    virtual ~FLogicRoles() = default;

    virtual bool operator==(const FLogic& Other) const override
    {
        if (LogicType != Other.LogicType)
            return false;
        return FLogic::operator==(Other);
    }
};

USTRUCT(BlueprintType)
struct FLogicIdentifier : public FLogicRoles
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    bool PlayerVisible;

    FLogicIdentifier(const FString& InLogic, const FString& InDisplayLogic, const LogicTypes InLogicType, bool InPlayerVisible)
        : FLogicRoles(InLogic, InDisplayLogic, InLogicType)
        , PlayerVisible(InPlayerVisible) {
    }
    FLogicIdentifier()
        : FLogicRoles(TEXT("Default Subject Logic"), TEXT("Default Subject Display Logic"), LogicTypes::Identifiers)
        , PlayerVisible(false) {
    }

    virtual ~FLogicIdentifier() = default;

    virtual bool operator==(const FLogic& Other) const override
    {
        if (LogicType != Other.LogicType)
            return false;

        if (Other.LogicType == LogicTypes::Identifiers)
        {
            const FLogicIdentifier& OtherIdentifier = static_cast<const FLogicIdentifier&>(Other);
            return FLogicRoles::operator==(Other) && PlayerVisible == OtherIdentifier.PlayerVisible;
        }
        return false;
    }
};


USTRUCT(BlueprintType)
struct FLogicStatement : public FLogic
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    int32 Probability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    int32 RolesCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    int32 IdentifierCount;

    FLogicStatement()
        : FLogic(TEXT("Default Statement Logic"), TEXT("Default Statement Display Logic"), LogicTypes::Statements)
        , Probability(0)
        , RolesCount(0)
        , IdentifierCount(0) {
    }

    FLogicStatement(const FString& InLogic, const FString& InDisplayLogic, int32 InProbability, int32 InRolesCount, int32 InIdentifiersCount)
        : FLogic(InLogic, InDisplayLogic, LogicTypes::Statements)
        , Probability(InProbability)
        , RolesCount(InRolesCount)
        , IdentifierCount(InIdentifiersCount) {
    }

    virtual ~FLogicStatement() = default;

    virtual bool operator==(const FLogic& Other) const override
    {
        if (LogicType != Other.LogicType)
            return false;

        if (Other.LogicType == LogicTypes::Statements)
        {
            const FLogicStatement& OtherStatement = static_cast<const FLogicStatement&>(Other);

            return FLogic::operator==(Other) &&
                Probability == OtherStatement.Probability &&
                RolesCount == OtherStatement.RolesCount &&
                IdentifierCount == OtherStatement.IdentifierCount;
        }

        return false;
    }
};

UENUM(BlueprintType, Category = "Logic")
enum class AllLogic : uint8
{
    If, 
    Then,
    And,
    Or,
    Is,
    Not,
    Probably,
    CaseNumber,
    Colour,
    Truthful,
    Lying,
    Danger,
    Safe,
    Equal,
    Greater,
    Less,
    PlusOffset,
    NegOffset,
    Between
};

namespace LogicNamespace
{
    static FLogic If(TEXT("IF"), TEXT("If"), LogicTypes::Conditions);
    static FLogic Then(TEXT("THEN"), TEXT("Then"), LogicTypes::Conditions);

    static FLogic And(TEXT("AND"), TEXT("And"), LogicTypes::Conjunctive);
    static FLogic Or(TEXT("OR"), TEXT("Or"), LogicTypes::Conjunctive);

    static FLogic Is(TEXT("IS"), TEXT("Is"), LogicTypes::Basis);
    static FLogic Not(TEXT("NOT"), TEXT("Not"), LogicTypes::Basis);
    static FLogic Probably(TEXT("PROBABLY"), TEXT("Probably"), LogicTypes::Basis);


    static FLogicIdentifier CaseNumber(TEXT("CASENUMBER"), TEXT("the Case Number "), LogicTypes::Identifiers, true);
    static FLogicIdentifier Colour(TEXT("COLOUR"), TEXT("the Case Colour "), LogicTypes::Identifiers, true);

    static FLogicIdentifier Truthful(TEXT("TRUTHFUL"), TEXT("a Truthful case "), LogicTypes::Identifiers, false);
    static FLogicIdentifier Lying(TEXT("LYING"), TEXT("a Lying case "), LogicTypes::Identifiers, false);

    static FLogicRoles Danger(TEXT("DANGER"), TEXT("the Dangerous case "), LogicTypes::Roles);
    static FLogicRoles Safe(TEXT("SAFE"), TEXT("a Safe case "), LogicTypes::Roles);

    static FLogicStatement Equal(TEXT("IDENTIFIER EQUALS ROLE"), TEXT("An Identifier is Equal to Role"), 100, 1, 1);
    static FLogicStatement Greater(TEXT("IDENTIFIER GREATERTHAN ROLE"), TEXT("An Identifier is Greater than Role"), 100, 1, 1);
    static FLogicStatement Less(TEXT("IDENTIFIER LESSTHAN ROLE"), TEXT("An Identifier is Less than Role"), 100, 1, 1);
    static FLogicStatement PlusOffset(TEXT("IDENTIFIER PLUS IDENTIFIER IS ROLE"), TEXT("An Identifier plus an Identifier is Equal to Role"), 100, 1, 2);
    static FLogicStatement NegOffset(TEXT("IDENTIFIER MINUS IDENTIFIER IS ROLE"), TEXT("An Identifier minus an Identifier is Equal to Role"), 100, 1, 2);
    static FLogicStatement Between(TEXT("IDENTIFIER EQUALS ROLE"), TEXT("Between Identifier & Identifier is Role"), 100, 1, 2);

    static FLogic* GetLogicByEnum(AllLogic LogicType)
    {
        switch (LogicType)
        {
        case AllLogic::If: return &If;
        case AllLogic::Then: return &Then;
        case AllLogic::And: return &And;
        case AllLogic::Or: return &Or;
        case AllLogic::Is: return &Is;
        case AllLogic::Not: return &Not;
        case AllLogic::Probably: return &Probably;
        case AllLogic::CaseNumber: return &CaseNumber;
        case AllLogic::Colour: return &Colour;
        case AllLogic::Truthful: return &Truthful;
        case AllLogic::Lying: return &Lying;
        case AllLogic::Danger: return &Danger;
        case AllLogic::Safe: return &Safe;
        case AllLogic::Equal: return &Equal;
        case AllLogic::Greater: return &Greater;
        case AllLogic::Less: return &Less;
        case AllLogic::PlusOffset: return &PlusOffset;
        case AllLogic::NegOffset: return &NegOffset;
        case AllLogic::Between: return &Between;
        default:
            return nullptr; 
        }
    }
}


UCLASS(BlueprintType)
class EXPLOSIVEUNBOXING_API UHint : public UDataAsset
{
    GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    TArray<AllLogic> logic;
    UHint() = default;
};



USTRUCT(BlueprintType)
struct EXPLOSIVEUNBOXING_API FUCaseHint
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
    UHint* hint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
    TArray<int32> SubjectData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    FString hintText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    TArray<FString> Text;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    TArray<int32> BasisIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    TArray<int32> ConditionBasisIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hints")
    TArray<int32> SubjectIndexes;

    FUCaseHint() : hint(nullptr) {}
};