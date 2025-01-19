#include "HintManager.h"
#include <algorithm>

// Note: a lot of data is modified in If statements: 'If(!Func) return false' still does the data modifications in Func
UHintManager::UHintManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHintManager::BeginPlay() 
{ 
    Super::BeginPlay(); 
}

UHint* SelectHint(UHintCollection* HintData)
{
    int32 RandomIndex = FMath::RandRange(0, HintData->HintCollections.Num() - 1);
    return HintData->HintCollections[RandomIndex];
}

// Adds Random data for If Statement Logic where the Logic cannot be made to return true. 
void AddRandomizedHintSubjectData(TArray<int32>& NewSubjectData, TArray<int32>& CaseNumbers, int32 RandomCount, int32 HintCount) 
{
    for (int i = 0; i < RandomCount; i++) {
        int32 RandomIndex = FMath::RandRange(0, HintCount - 1);
        NewSubjectData.Add(CaseNumbers[RandomIndex]);
    }
}

bool SetToRandomIndexFromSelection(TArray<int32>& AvailableIndices, TArray<int32>& caseNumbers, int32* AssignedCase, int32* RandomIndex) {
    if (AvailableIndices.Num() > 0) {
        *RandomIndex = AvailableIndices[FMath::RandRange(0, AvailableIndices.Num() - 1)];
        *AssignedCase = caseNumbers[*RandomIndex];
        return true;
    }
    return false;
}

int32 GetLiarCount(TArray<bool>& Liars)
{
    int32 Count = 0;
    for (bool b : Liars)
        Count += b ? 1 : 0;
    return Count;
}

bool GetSafeCase(TArray<int32>& CaseNumbers, int32* AssignedCase, int32 HintCount, int32 SolutionCase)
{
    int32 RandomIndex;
    TArray<int32> AvailableIndices;

    for (int32 i = 0; i < HintCount; ++i)
        if (CaseNumbers[i] != SolutionCase)
            AvailableIndices.Add(i);
    return SetToRandomIndexFromSelection(AvailableIndices, CaseNumbers, AssignedCase, &RandomIndex);
}

bool GetLyingCase(TArray<bool>& Liars, TArray<bool>& TruthTellers, TArray<int32>& caseNumbers, 
    int32* AssignedCase, int32 HintCount, int32 MaxLiarCount)
{
    int32 Count = GetLiarCount(Liars);
    int32 RandomIndex;
    TArray<int32> AvailableIndices;

    for (int32 i = 0; i < HintCount; ++i) 
        if (Liars[i] || (Count < MaxLiarCount && !TruthTellers[i]))
            AvailableIndices.Add(i);
    
    if (!SetToRandomIndexFromSelection(AvailableIndices, caseNumbers, AssignedCase, &RandomIndex))
        return false;
    
    Liars[RandomIndex] = true;
    return true;
}

bool GetDangerousLiar(TArray<bool>& Liars, TArray<bool>& TruthTellers, TArray<int32>& caseNumbers,
    int32* AssignedCase, int32 SolutionCase, int32 HintCount, int32 MaxLiarCount)
{
    int32 Count = GetLiarCount(Liars);

    for (int32 i = 0; i < HintCount; ++i) 
    {
        if (caseNumbers[i] != SolutionCase)
            continue;
        else if (Liars[i] || (Count < MaxLiarCount && !TruthTellers[i])) 
        {
            Liars[i] = true;
            *AssignedCase = caseNumbers[i];
            return true;
        }
    }
    return false;
}

bool GetSafeLiar(TArray<bool>& Liars, TArray<bool>& TruthTellers, TArray<int32>& caseNumbers,
    int32* AssignedCase, int32 SolutionCase, int32 HintCount, int32 MaxLiarCount)
{
    int32 Count = GetLiarCount(Liars);
    TArray<int32> AvailableIndices;
    int32 RandomIndex;

    for (int32 i = 0; i < HintCount; ++i)
    {
        if (caseNumbers[i] == SolutionCase)
            continue;
        else if (Liars[i] || (Count < MaxLiarCount && !TruthTellers[i]))
            AvailableIndices.Add(i);
    }
    if (!SetToRandomIndexFromSelection(AvailableIndices, caseNumbers, AssignedCase, &RandomIndex))
        return false;

    Liars[RandomIndex] = true;
    return true;
}

bool GetDangerousTruthTeller(TArray<bool>& Liars, TArray<bool>& TruthTellers, TArray<int32>& caseNumbers,
    int32* AssignedCase, int32 SolutionCase, int32 HintCount)
{
    for (int32 i = 0; i < HintCount; ++i)
    {
        if (caseNumbers[i] != SolutionCase)
            continue;
        else if (!Liars[i])
        {
            TruthTellers[i] = true;
            *AssignedCase = caseNumbers[i];
            return true;
        }
    }
    return false;
}

bool GetSafeTruthTeller(TArray<bool>& Liars, TArray<bool>& TruthTellers, TArray<int32>& caseNumbers,
    int32* AssignedCase, int32 SolutionCase, int32 HintCount)
{
    TArray<int32> AvailableIndices;
    int32 RandomIndex;

    for (int32 i = 0; i < HintCount; ++i)
    {
        if (caseNumbers[i] == SolutionCase)
            continue;
        else if (!Liars[i])
            AvailableIndices.Add(i);
    }
    if (!SetToRandomIndexFromSelection(AvailableIndices, caseNumbers, AssignedCase, &RandomIndex))
        return false;

    TruthTellers[RandomIndex] = true;
    return true;
}


bool GetTruthfulCase(TArray<bool>& Liars, TArray<bool>& TruthTellers, TArray<int32>& caseNumbers, 
    int32* AssignedCase, int32 HintCount)
{
    TArray<int32> AvailableIndices;    
    int32 RandomIndex;

    for (int32 i = 0; i < HintCount; ++i) 
        if (!Liars[i])
            AvailableIndices.Add(i);

    if (!SetToRandomIndexFromSelection(AvailableIndices, caseNumbers, AssignedCase, &RandomIndex))
        return false;

    TruthTellers[RandomIndex] = true;
    return true;
}

bool GetCaseNumberBelowDanger(TArray<int32>& CaseNumbers, int32* AssignedCase, int32 HintCount, int32 SolutionCase)
{
    int32 RandomIndex;
    TArray<int32> AvailableIndices;

    for (int32 i = 0; i < HintCount; ++i)
        if (CaseNumbers[i] < SolutionCase)
            AvailableIndices.Add(i);
    return SetToRandomIndexFromSelection(AvailableIndices, CaseNumbers, AssignedCase, &RandomIndex);
}

bool GetCaseNumberAboveDanger(TArray<int32>& CaseNumbers, int32* AssignedCase, int32 HintCount, int32 SolutionCase)
{
    int32 RandomIndex;
    TArray<int32> AvailableIndices;

    for (int32 i = 0; i < HintCount; ++i) 
        if (CaseNumbers[i] > SolutionCase)
            AvailableIndices.Add(i);
    return SetToRandomIndexFromSelection(AvailableIndices, CaseNumbers, AssignedCase, &RandomIndex);
}

bool IsPlayerVisible(FLogic* MyIdentifier)
{
    const FLogicIdentifier* OtherIdentifier = static_cast<const FLogicIdentifier*>(MyIdentifier);
    return OtherIdentifier->PlayerVisible;
}


bool GetBoolFromText(const TArray<FString>& Text, int32 Index)
{
    if (Text.IsValidIndex(Index)) 
    {
        const FString& Value = Text[Index];
        return Value == "1" || Value.ToLower() == "true";
    }
    return false; 
}

void AddBasisText(TArray<FString>& Text, TArray<int32>& BasisIndexes, bool IsNot)
{
    FString BoolString = IsNot ? TEXT("true") : TEXT("false");
    Text.Add(BoolString);
    BasisIndexes.Add(Text.Num() - 1);
}

// Given example Case Number X, This function adds a marker to add X to X & set it when all X's are known
// Given a logic statment can fail, all values of X are not set till later
void AddIdentifyingRoleText(TArray<FString>& Text, TArray<int32>& SubjectIndexes, FLogic* MyIdentifier)
{
    auto Role = MyIdentifier;
    Text.Add(Role->DisplayLogic);

    if (Role->LogicType == LogicTypes::Identifiers)
    {
        if (IsPlayerVisible(Role)) {
            Text.Add(TEXT("Subject"));
            SubjectIndexes.Add(Text.Num() - 1);
        }    
        else 
            SubjectIndexes.Add(-1);
    }
}

void AddText(TArray<FString>& Text, TArray<int32>& BasisIndexes, TArray<int32>& SubjectIndexes, LogicStatmentTypes StatementType, 
    TArray<FLogic*>& MyRole, TArray<FLogic*>& MyIdentifiers, bool IsNot)
{
    switch (StatementType)
    {
    case (LogicStatmentTypes::Is): {
        AddIdentifyingRoleText(Text, SubjectIndexes, MyIdentifiers[0]);
        AddBasisText(Text, BasisIndexes, IsNot);
        AddIdentifyingRoleText(Text, SubjectIndexes, MyRole[0]);
        break;
    }
    case (LogicStatmentTypes::IsGreater): {
        AddIdentifyingRoleText(Text, SubjectIndexes, MyIdentifiers[0]);
        AddBasisText(Text, BasisIndexes, IsNot);
        Text.Add(TEXT("greater than "));
        AddIdentifyingRoleText(Text, SubjectIndexes, MyRole[0]);
        break;
    }
    case (LogicStatmentTypes::IsLess): {
        AddIdentifyingRoleText(Text, SubjectIndexes, MyIdentifiers[0]);
        AddBasisText(Text, BasisIndexes, IsNot);
        Text.Add(TEXT("less than "));
        AddIdentifyingRoleText(Text, SubjectIndexes, MyRole[0]);
        break;
    }
    case (LogicStatmentTypes::IsBetween): {
        Text.Add(TEXT("Between "));
        AddIdentifyingRoleText(Text, SubjectIndexes, MyIdentifiers[0]);
        Text.Add(TEXT("and "));
        AddIdentifyingRoleText(Text, SubjectIndexes, MyIdentifiers[1]);
        AddBasisText(Text, BasisIndexes, IsNot);
        AddIdentifyingRoleText(Text, SubjectIndexes, MyRole[0]);
        break;
    }
    case (LogicStatmentTypes::IsPosOffset): {
        AddIdentifyingRoleText(Text, SubjectIndexes, MyIdentifiers[0]);
        Text.Add(TEXT("plus "));
        AddIdentifyingRoleText(Text, SubjectIndexes, MyIdentifiers[1]);
        AddBasisText(Text, BasisIndexes, IsNot);
        AddIdentifyingRoleText(Text, SubjectIndexes, MyRole[0]);
        break;
    }
    case (LogicStatmentTypes::IsNegOffset): {
        AddIdentifyingRoleText(Text, SubjectIndexes, MyIdentifiers[0]);
        Text.Add(TEXT("minus "));
        AddIdentifyingRoleText(Text, SubjectIndexes, MyIdentifiers[1]);
        AddBasisText(Text, BasisIndexes, IsNot);
        AddIdentifyingRoleText(Text, SubjectIndexes, MyRole[0]);
        break;
    }
        default:
            break;
    }
}

bool CaseNumberEquals(FLogic* MyRole, int32* newSubjectValue, TArray<int32>& CaseNumbers, TArray<bool>& Liars, 
    TArray<bool>& TruthTellers, bool IsNot, int32 CaseSolution, int32 HintCount, int32 MaxLiarCount)
{
    if (*MyRole == LogicNamespace::Danger) // Case X is Danger
    {
        if (!IsNot)
            *newSubjectValue = CaseSolution;
        else if (IsNot) {
            if (!GetSafeCase(CaseNumbers, newSubjectValue, HintCount, CaseSolution))
                return false;
        }
    }
    else if (*MyRole == LogicNamespace::Safe) // Case X is Safe
    {
        if (!IsNot) {
            if (!GetSafeCase(CaseNumbers, newSubjectValue, HintCount, CaseSolution))
                return false;
        }
        else if (IsNot) {
            *newSubjectValue = CaseSolution;
        }
    }
    else if (*MyRole == LogicNamespace::Lying) // Case X is Lying
    {
        if (!IsNot) {
            if (!GetLyingCase(Liars, TruthTellers, CaseNumbers, newSubjectValue, HintCount, MaxLiarCount))
                return false;
        }
        else if (IsNot) {
            if (!GetTruthfulCase(Liars, TruthTellers, CaseNumbers, newSubjectValue, HintCount))
                return false;
        }
    }
    else if (*MyRole == LogicNamespace::Truthful) // Case X is Truthful
    {
        if (!IsNot) {
            if (!GetTruthfulCase(Liars, TruthTellers, CaseNumbers, newSubjectValue, HintCount))
                return false;
        }
        else if (IsNot) {
            if (!GetLyingCase(Liars, TruthTellers, CaseNumbers, newSubjectValue, HintCount, MaxLiarCount))
                return false;
        }
    }
    return true;
}

bool LiarEquals(FLogic* MyRole, int32* newSubjectValue, TArray<int32>& CaseNumbers, TArray<bool>& Liars,
    TArray<bool>& TruthTellers, bool IsNot, int32 CaseSolution, int32 HintCount, int32 MaxLiarCount)
{
    if (*MyRole == LogicNamespace::Danger) // A Liar is Danger
    {
        if (!IsNot) {
            if (!GetDangerousLiar(Liars, TruthTellers, CaseNumbers, newSubjectValue, CaseSolution, HintCount, MaxLiarCount))
                return false;
        }
        else if (IsNot) {
            if (!GetSafeLiar(Liars, TruthTellers, CaseNumbers, newSubjectValue, CaseSolution, HintCount, MaxLiarCount))
                return false;
        }
    }
    else if (*MyRole == LogicNamespace::Safe) // A Liar is Safe
    {
        if (!IsNot) {
            if (!GetSafeLiar(Liars, TruthTellers, CaseNumbers, newSubjectValue, CaseSolution, HintCount, MaxLiarCount))
                return false;
        }
        else if (IsNot) {
            if (!GetDangerousLiar(Liars, TruthTellers, CaseNumbers, newSubjectValue, CaseSolution, HintCount, MaxLiarCount))
                return false;
        }
    }
    else if (*MyRole == LogicNamespace::CaseNumber) // Liar is Case X
    {
        if (!IsNot) {
            if (!GetLyingCase(Liars, TruthTellers, CaseNumbers, newSubjectValue, HintCount, MaxLiarCount))
                return false;
        }
        else if (IsNot) {
            if (!GetTruthfulCase(Liars, TruthTellers, CaseNumbers, newSubjectValue, HintCount))
                return false;
        }
    }
    return true;
}

bool TruthfulEquals(FLogic* MyRole, int32* newSubjectValue, TArray<int32>& CaseNumbers, TArray<bool>& Liars,
    TArray<bool>& TruthTellers, bool IsNot, int32 CaseSolution, int32 HintCount, int32 MaxLiarCount)
{
    if (*MyRole == LogicNamespace::Danger) // A Truthful is Danger
    {
        if (!IsNot) {
            if (!GetDangerousTruthTeller(Liars, TruthTellers, CaseNumbers, newSubjectValue, CaseSolution, HintCount))
                return false;
        }
        else if (IsNot) {
            if (!GetSafeTruthTeller(Liars, TruthTellers, CaseNumbers, newSubjectValue, CaseSolution, HintCount))
                return false;
        }
    }
    else if (*MyRole == LogicNamespace::Safe) // A Truthful is Safe
    {
        if (!IsNot) {
            if (!GetSafeTruthTeller(Liars, TruthTellers, CaseNumbers, newSubjectValue, CaseSolution, HintCount))
                return false;
        }
        else if (IsNot) {
            if (!GetDangerousTruthTeller(Liars, TruthTellers, CaseNumbers, newSubjectValue, CaseSolution, HintCount))
                return false;
        }
    }
    else if (*MyRole == LogicNamespace::CaseNumber) // A Truthful is Case X
    {
        if (!IsNot) {
            if (!GetTruthfulCase(Liars, TruthTellers, CaseNumbers, newSubjectValue, HintCount))
                return false;
        }
        else if (IsNot) {
            if (!GetLyingCase(Liars, TruthTellers, CaseNumbers, newSubjectValue, HintCount, MaxLiarCount))
                return false;
        }
    }
    return true;
}

bool CaseNumberGreater(FLogic* MyRole, TArray<int32>& NewSubjectData, TArray<int32>& CaseNumbers, TArray<bool>& Liars,
    TArray<bool>& TruthTellers, int32* SubjectCount, bool IsNot, int32 CaseSolution, int32 HintCount, int32 MaxLiarCount)
{
    int32 FirstSubject;
    if (*MyRole == LogicNamespace::Danger) // Above Case Number is Danger
    {
        if (!IsNot) {
            if (!GetCaseNumberAboveDanger(CaseNumbers, &FirstSubject, HintCount, CaseSolution))
                return false;
        }
        else if (IsNot) {
            if (!GetCaseNumberBelowDanger(CaseNumbers, &FirstSubject, HintCount, CaseSolution))
                return false;
        }
    }
    else if (*MyRole == LogicNamespace::Safe) // Above Case Number is Safety
    {
        if (!IsNot) {
            if (!GetCaseNumberAboveDanger(CaseNumbers, &FirstSubject, HintCount, CaseSolution))
                return false;
        }
        else if (IsNot) {
            if (!GetCaseNumberBelowDanger(CaseNumbers, &FirstSubject, HintCount, CaseSolution))
                return false;
        }
    }
    else if (*MyRole == LogicNamespace::Lying) // Above Case Number is Liar
    {        
        int32 SecondSubject;
        ++*SubjectCount;
        if (!GetLyingCase(Liars, TruthTellers, CaseNumbers, &SecondSubject, HintCount, MaxLiarCount))
            return false;

        if (!IsNot) {
            if (!GetCaseNumberAboveDanger(CaseNumbers, &FirstSubject, HintCount, SecondSubject))
                return false;
        }
        else if (IsNot) {
            if (!GetCaseNumberBelowDanger(CaseNumbers, &FirstSubject, HintCount, SecondSubject))
                return false;
        }
        NewSubjectData.Add(SecondSubject);
    }
    else if (*MyRole == LogicNamespace::Truthful) // Above Case Number is a Truthful Case
    {        
        int32 SecondSubject;

        ++*SubjectCount;
        if (!GetTruthfulCase(Liars, TruthTellers, CaseNumbers, &SecondSubject, HintCount))
            return false;

        if (!IsNot) {
            if (!GetCaseNumberAboveDanger(CaseNumbers, &FirstSubject, HintCount, SecondSubject))
                return false;
        }
        else if (IsNot) {
            if (!GetCaseNumberBelowDanger(CaseNumbers, &FirstSubject, HintCount, SecondSubject))
                return false;
        }
        NewSubjectData.Add(SecondSubject);
    }
    NewSubjectData.Add(FirstSubject);
    return true;
}

bool SolveForEqual(TArray<FLogic*>& AllIdentifiers, TArray<FLogic*>& AllRoles, FLogic* LogicStatement, TArray<int32>& CaseNumbers, TArray<int32>& NewSubjectData,
    TArray<bool>& Liars, TArray<bool>& TruthTellers, TArray<FString>& Text, TArray<int32>& BasisIndexes, TArray<int32>& SubjectIndexes, int32* SubjectCount, bool IsNot, int32 MaxLiarCount, int32 CaseSolution, int32 HintCount)
{
    auto MyIdentifier = AllIdentifiers[0];
    auto MyRole = AllRoles[0];
    int32 newSubjectValue;

    AddText(Text, BasisIndexes, SubjectIndexes, LogicStatmentTypes::Is, AllRoles, AllIdentifiers, IsNot);

    if (*MyIdentifier == LogicNamespace::CaseNumber) {
        if (!CaseNumberEquals(MyRole, &newSubjectValue, CaseNumbers, Liars, TruthTellers, IsNot, CaseSolution, HintCount, MaxLiarCount))
            return false;
    }
    else if (*MyIdentifier == LogicNamespace::Lying) {
        if (!LiarEquals(MyRole, &newSubjectValue, CaseNumbers, Liars, TruthTellers, IsNot, CaseSolution, HintCount, MaxLiarCount))
            return false;
    }
    else if (*MyIdentifier == LogicNamespace::Truthful) {
        if (!TruthfulEquals(MyRole, &newSubjectValue, CaseNumbers, Liars, TruthTellers, IsNot, CaseSolution, HintCount, MaxLiarCount))
            return false;
    }
    else if (*MyIdentifier == LogicNamespace::Colour)
    {
        // [EXTENSION] Not required for Jam scope
        // Find or create a BriefCase of Colour X that makes this statement true
        // e.g A Green is Safe, A Yellow is Danger, A Red is Case11
    }

    NewSubjectData.Add(newSubjectValue);
    return true;
}

bool SolveForGreater(TArray<FLogic*>& AllIdentifiers, TArray<FLogic*>& AllRoles, FLogic* LogicStatement, TArray<int32>& CaseNumbers, TArray<int32>& NewSubjectData,
    TArray<bool>& Liars, TArray<bool>& TruthTellers, TArray<FString>& Text, TArray<int32>& BasisIndexes, TArray<int32>& SubjectIndexes, int32* SubjectCount, bool IsNot, int32 MaxLiarCount, int32 CaseSolution, int32 HintCount)
{
    auto MyIdentifier = AllIdentifiers[0];
    auto MyRole = AllRoles[0];

    AddText(Text, BasisIndexes, SubjectIndexes, LogicStatmentTypes::IsGreater, AllRoles, AllIdentifiers, IsNot);

    if (*MyIdentifier == LogicNamespace::CaseNumber) {
        if (!CaseNumberGreater(MyRole, NewSubjectData, CaseNumbers, Liars, TruthTellers, SubjectCount, IsNot, CaseSolution, HintCount, MaxLiarCount))
            return false;
    }
    else if (*MyIdentifier == LogicNamespace::Lying)
    {
        return false;
        // [EXTENSION] Not required for Jam scope
        // Find or create a Liar that makes this statement true
        // e.g A Liar is Above a Safe case, A Liar is above Danger, A Liar is Above Case 11
    } 
    // As some Statements Require two data subjects they are added in Logic Functions
    return true;
}

bool SolveForLess(TArray<FLogic*>& AllIdentifiers, TArray<FLogic*>& AllRoles, FLogic* LogicStatement, TArray<int32>& CaseNumbers, TArray<int32>& NewSubjectData,
    TArray<bool>& Liars, TArray<bool>& TruthTellers, TArray<FString>& Text, TArray<int32>& BasisIndexes, TArray<int32>& SubjectIndexes, int32* SubjectCount, bool IsNot, int32 MaxLiarCount, int32 CaseSolution, int32 HintCount)
{
    auto MyIdentifier = AllIdentifiers[0];
    auto MyRole = AllRoles[0];

    AddText(Text, BasisIndexes, SubjectIndexes, LogicStatmentTypes::IsLess, AllRoles, AllIdentifiers, IsNot);
    IsNot = !IsNot; // Using !IsNot to use Greater logic as Less than logic (only modifies IsNot as copy)

    if (*MyIdentifier == LogicNamespace::CaseNumber)
        if (!CaseNumberGreater(MyRole, NewSubjectData, CaseNumbers, Liars, TruthTellers, SubjectCount, IsNot, CaseSolution, HintCount, MaxLiarCount))
            return false;
    else if (*MyIdentifier == LogicNamespace::Lying)
    {
        // [EXTENSION] Not required for Jam scope
        return false;
    }
    return true;
}

bool GetRoles(TArray<FLogic*>& AllIdentifiers, TArray<FLogic*>& AllRoles,
    TArray<FLogic*>& LogicArray, int32 RolesCount, int32 IdentifierCount, int32 j, int32 LogicSize)
{
    if (j + IdentifierCount + RolesCount > LogicSize) 
    {
        UE_LOG(LogTemp, Warning, TEXT("This HintType contains an Invalid IdentifierCount OR RolesCount for its LogicStatement. "));
        return false;
    }

    for (int k = 1; k < IdentifierCount + 1; k++) 
    {
        if (LogicArray[j + k]->LogicType != LogicTypes::Identifiers) 
        {
            UE_LOG(LogTemp, Warning, TEXT("This HintType contains an Invalid Sequence: Valid Identifiers are expected after Statements"));
            return false;
        }
        AllIdentifiers.Add(LogicArray[j + k]);
    }

    for (int k = 1; k < RolesCount + 1; k++) 
    {
        auto LogicType = LogicArray[j + k + IdentifierCount]->LogicType;
        if (LogicType != LogicTypes::Identifiers && LogicType != LogicTypes::Roles)
        {
            UE_LOG(LogTemp, Warning, TEXT("This HintType contains an Invalid Sequence: Valid Identifiers OR Roles are expected after the primary Identifiers"));
            return false;
        }
        AllRoles.Add(LogicArray[j + k + IdentifierCount]);
    }
    return true;
}

bool SolveForStatement(int j, FLogic* LogicStatement, TArray<int32>& CaseNumbers, TArray<int32>& NewSubjectData, TArray<FLogic*>& LogicArray,
    TArray<bool>& Liars, TArray<bool>& TruthTellers, TArray<FString>& Text, TArray<int32>& BasisIndexes, TArray<int32>& SubjectIndexes, 
    int32* SkipCount, int32* SubjectCount, bool InConditionLoop, bool IsNot, int32 MaxLiarCount, int32 CaseSolution, int32 HintCount, int32 LogicSize)
{

    const FLogicStatement* LogicEquation = static_cast<const FLogicStatement*>(LogicStatement);

    auto IdentifierCount = LogicEquation->IdentifierCount;
    auto RolesCount = LogicEquation->RolesCount;

    SkipCount += IdentifierCount + RolesCount;
    TArray<FLogic*> AllIdentifiers;
    TArray<FLogic*> AllRoles;

    if (!GetRoles(AllIdentifiers, AllRoles, LogicArray, RolesCount, IdentifierCount, j, LogicSize))
        return false;

    if (*LogicStatement == LogicNamespace::Equal) {
        if (!SolveForEqual(AllIdentifiers, AllRoles, LogicStatement, CaseNumbers, NewSubjectData, Liars, TruthTellers, Text, BasisIndexes, SubjectIndexes, SubjectCount, IsNot, MaxLiarCount, CaseSolution, HintCount))
            return false;
    }
    else if (*LogicStatement == LogicNamespace::Greater){
        if (!SolveForGreater(AllIdentifiers, AllRoles, LogicStatement, CaseNumbers, NewSubjectData, Liars, TruthTellers, Text, BasisIndexes, SubjectIndexes, SubjectCount, IsNot, MaxLiarCount, CaseSolution, HintCount))
            return false;
    }
    else if (*LogicStatement == LogicNamespace::Less) {
        if (!SolveForLess(AllIdentifiers, AllRoles, LogicStatement, CaseNumbers, NewSubjectData, Liars, TruthTellers, Text, BasisIndexes, SubjectIndexes, SubjectCount, IsNot, MaxLiarCount, CaseSolution, HintCount))
            return false;
    }
    else if (*LogicStatement == LogicNamespace::Between)
        return false;
    else if (*LogicStatement == LogicNamespace::PlusOffset)
        return false;
    else if (*LogicStatement == LogicNamespace::NegOffset)
        return false;
    else 
        UE_LOG(LogTemp, Warning, TEXT("The Statement could not be recognized from defined Logics."));
    return true;
}

TArray<FLogic*> GenerateLogicArray(const TArray<AllLogic>& LogicEnumArray, UHint* HintType)
{
    TArray<FLogic*> LogicArray;
    for (auto& Var : LogicEnumArray)
    {
        LogicArray.Add(LogicNamespace::GetLogicByEnum(Var));
    }
    return LogicArray;
}

bool ProcessConditionLogic(int32 j, FLogic* LogicStatement, bool& InConditionLoop, bool& ConditionMet,
    TArray<ConjunctivesTypes>& MyConjunctives, TArray<bool>& LogicTruths, TArray<FString>& Text)
{
    if (*LogicStatement == LogicNamespace::If)
    {
        Text.Add(TEXT("if "));
        InConditionLoop = true;
        return true;
    }

    if (*LogicStatement == LogicNamespace::Then)
    {
        Text.Add(TEXT("then "));
        int StatementIndex = 0;
        ConditionMet = LogicTruths[StatementIndex];

        for (auto& Var : MyConjunctives)
        {
            StatementIndex++;
            if (Var == ConjunctivesTypes::AND)
                ConditionMet = ConditionMet && LogicTruths[StatementIndex];
            else if (Var == ConjunctivesTypes::OR)
                ConditionMet = ConditionMet || LogicTruths[StatementIndex];
        }
        MyConjunctives.Empty();
        LogicTruths.Empty();
        InConditionLoop = false;
    }

    return false;
}

void ProcessConjunctiveLogic(FLogic* LogicStatement, TArray<ConjunctivesTypes>& MyConjunctives, TArray<FString>& Text)
{
    if (*LogicStatement == LogicNamespace::Or)
    {
        Text.Add(TEXT("or "));
        MyConjunctives.Add(ConjunctivesTypes::OR);
    }
    else if (*LogicStatement == LogicNamespace::And)
    {
        Text.Add(TEXT("and "));
        MyConjunctives.Add(ConjunctivesTypes::AND);
    }
}

bool ProcessStatementLogic(int32 j, FUCaseHint* NewCaseHint, int32 MaxLiarCount, int32 CaseSolution,
    int32 HintCount, int32 LogicSize, TArray<int32>& CaseNumbers,
    TArray<FLogic*>& LogicArray, TArray<bool>& Liars, TArray<bool>& TruthTellers,
    TArray<FString>& Text, bool InConditionLoop, bool IsNot, int32& SkipCount)
{
    int32 SubjectCount = 1;
    bool FoundSolution = SolveForStatement(j, LogicArray[j], CaseNumbers, NewCaseHint->SubjectData, LogicArray,
        Liars, TruthTellers, Text, InConditionLoop ? NewCaseHint->ConditionBasisIndex : NewCaseHint->BasisIndex,
        NewCaseHint->SubjectIndexes, &SkipCount, &SubjectCount, InConditionLoop, IsNot, MaxLiarCount, CaseSolution,
        HintCount, LogicSize);

    return FoundSolution;
}

void AddSubjectDataToText(FUCaseHint* NewCaseHint, TArray<int32>& SubjectIndexes, TArray<int32>& NewSubjectData,
    TArray<FString>& Text)
{
    int Index = 0;
    for (auto& SubjectIndex : SubjectIndexes)
    {
        if (SubjectIndex == -1) {
            Index++;
            continue;
        }
        Text[SubjectIndex] = FString("") + FString::FromInt(NewSubjectData[Index]);
        Index++;
    }
}


bool CreateHint(int i, FUCaseHint* NewCaseHint, TArray<int32>& CaseNumbers, int32 CaseSolution,
    int32 MaxLiarCount, int32 HintCount, TArray<bool>& Liars, TArray<bool>& TruthTellers, UHint* HintType)
{
    bool ConditionMet = true;
    bool InConditionLoop = false;
    bool IsNot = false;

    TArray<FString> Text;
    TArray<ConjunctivesTypes> MyConjunctives;
    TArray<bool> LogicTruths;
    TArray<AllLogic> LogicEnumArray = HintType->logic;
    TArray<FLogic*> LogicArray = GenerateLogicArray(LogicEnumArray, HintType);

    int32 SkipCount = 0;
    int32 LogicSize = LogicEnumArray.Num();

    Text.Add(TEXT("I am brief Case ") + FString::FromInt(CaseNumbers[i]) + TEXT(" I know: "));

    for (int j = 0; j < LogicSize; j++)
    {
        if (!LogicArray[j])
        {
            UE_LOG(LogTemp, Warning, TEXT("The LogicArray is invalid at index %d: Please reallocate the correct Logic in the Hint's DataAsset"), j);
            return false;
        }

        auto LogicStatement = LogicArray[j];

        if (!LogicStatement)
        {
            UE_LOG(LogTemp, Warning, TEXT("The LogicStatement is invalid at index %d: Please reallocate the correct Logic in the Hint's DataAsset"), j);
            return false;
        }

        switch (LogicStatement->LogicType)
        {
        case LogicTypes::Identifiers: 
            break;
        case LogicTypes::Roles:
            break;
        case LogicTypes::Conditions: {

            if (ProcessConditionLogic(j, LogicStatement, InConditionLoop, ConditionMet, MyConjunctives, LogicTruths, Text))
                continue;
            break;
        }
        case LogicTypes::Basis: {
            if (*LogicStatement == LogicNamespace::Not)
                IsNot = !IsNot;
            break;
        }
        case LogicTypes::Conjunctive: {
            ProcessConjunctiveLogic(LogicStatement, MyConjunctives, Text);
            break;
        }
        case LogicTypes::Statements: {
            bool FoundSolution = ProcessStatementLogic(j, NewCaseHint, MaxLiarCount, CaseSolution, HintCount, LogicSize,
                CaseNumbers, LogicArray, Liars, TruthTellers, Text, InConditionLoop, IsNot, SkipCount);

            LogicTruths.Add(FoundSolution);

            if (!FoundSolution)
                AddRandomizedHintSubjectData(NewCaseHint->SubjectData, CaseNumbers, 1, HintCount);
            break;
        }
        default:
            UE_LOG(LogTemp, Warning, TEXT("Logic has no assigned LogicType"));
            return false;
        }
    }

    AddSubjectDataToText(NewCaseHint, NewCaseHint->SubjectIndexes, NewCaseHint->SubjectData, Text);

    NewCaseHint->Text = Text;
    NewCaseHint->BasisIndex = NewCaseHint->BasisIndex;
    NewCaseHint->ConditionBasisIndex = NewCaseHint->ConditionBasisIndex;

    return true;
}

template <typename T>
void ShuffleArray(TArray<T>& Array)
{
    const int32 LastIndex = Array.Num() - 1;
    for (int32 i = LastIndex; i > 0; --i)
    {
        int32 RandomIndex = FMath::RandRange(0, i);
        Array.Swap(i, RandomIndex);
    }
}

void GenerateHints(int32 HintCount, TArray<int32>& CaseNumbers, int32 CaseSolution, int32 MaxLiarCount,
    TArray<bool>& Liars, TArray<bool>& TruthTellers, UHintCollection* HintData, TArray<FUCaseHint>& ChosenHints)
{
    for (int i = 0; i < HintCount; i++)
    {
        FUCaseHint NewCaseHint;
        TArray<UHint*> RandomizedHintArray = HintData->HintCollections;
        ShuffleArray(RandomizedHintArray);

        bool HintPossible = false;

        for (UHint* HintType : RandomizedHintArray)
        {
            HintPossible = CreateHint(i, &NewCaseHint, CaseNumbers, CaseSolution, MaxLiarCount, HintCount, Liars, TruthTellers, HintType);
            if (HintPossible)
                break;
        }

        if (!HintPossible) {
            UE_LOG(LogTemp, Warning, TEXT("Not all Hints could be generated:: The Hint Collection may have Hints that prevent future Hints from being solved. Either rerun in case of solvable variant or edit your Hint Collection"));
            return;
        }
        ChosenHints.Add(NewCaseHint);
    }
}

void ProcessHintText(TArray<FUCaseHint>& ChosenHints, TArray<bool>& Liars)
{
    for (int i = 0; i < ChosenHints.Num(); i++)
    {
        for (auto& ConditionBasisIndex : ChosenHints[i].ConditionBasisIndex) {
            bool basis = GetBoolFromText(ChosenHints[i].Text, ConditionBasisIndex);
            ChosenHints[i].Text[ConditionBasisIndex] = basis ? TEXT(" is not ") : TEXT(" is ");
        }

        for (auto& BasisIndex : ChosenHints[i].BasisIndex) {
            bool basis = GetBoolFromText(ChosenHints[i].Text, BasisIndex);
            basis = Liars[i] ? !basis : basis;
            ChosenHints[i].Text[BasisIndex] = basis ? TEXT(" is not ") : TEXT(" is ");
        }

        for (auto& textItem : ChosenHints[i].Text)
        {
            ChosenHints[i].hintText += textItem;
        }
    }
}

TArray<FUCaseHint> UHintManager::GetLevelHints(TArray<int32>& CaseNumbers, int32 CaseSolution, UHintCollection* HintData)
{
    TArray<FUCaseHint> ChosenHints;   
    TArray<bool> Liars;
    TArray<bool> TruthTellers;

    int32 HintCount = CaseNumbers.Num();
    int32 MaxLiarCount = HintData->MaxLiarCount;

    Liars.SetNum(HintCount);
    TruthTellers.SetNum(HintCount);

    if (HintData->HintCollections.Num() <= 0) 
    {
        UE_LOG(LogTemp, Warning, TEXT("No Hints could be generated as the Referenced Collection is Empty."));
        return ChosenHints;
    }

    GenerateHints(HintCount, CaseNumbers, CaseSolution, MaxLiarCount, Liars, TruthTellers, HintData, ChosenHints);
    ProcessHintText(ChosenHints, Liars);

    return ChosenHints;
}


