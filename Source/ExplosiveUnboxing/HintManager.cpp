#include "HintManager.h"
#include <algorithm>

UHintManager::UHintManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHintManager::BeginPlay() { Super::BeginPlay(); }

UHint* SelectHint(UHintCollection* HintData)
{
    int32 RandomIndex = FMath::RandRange(0, HintData->HintCollections.Num() - 1);
    return HintData->HintCollections[RandomIndex];
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

bool SetCaseNumberLiarRand(TArray<bool>& Liars, TArray<bool>& TruthTellers, TArray<int32>& caseNumbers, 
    int32* AssignedCase, int32 HintCount, int32 MaxLiarCount)
{
    int32 Count = GetLiarCount(Liars);
    int32 RandomIndex;
    TArray<int32> AvailableIndices;

    for (int32 i = 0; i < Liars.Num(); ++i) 
        if (Liars[i])
            AvailableIndices.Add(i);
    
    if (Count < MaxLiarCount) 
        for (int32 i = 0; i < HintCount; ++i) 
            if (!TruthTellers[i] && !Liars[i])
                AvailableIndices.Add(i);

    if (!SetToRandomIndexFromSelection(AvailableIndices, caseNumbers, AssignedCase, &RandomIndex))
        return false;
    
    Liars[RandomIndex] = true;
    return true;
}

bool SetCaseNumberTruthfulRand(TArray<bool>& Liars, TArray<bool>& TruthTellers, TArray<int32>& caseNumbers, 
    int32* AssignedCase, int32 HintCount, int32 MaxLiarCount)
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

bool GetCaseNumberBelowDanager(TArray<int32>& CaseNumbers, int32* AssignedCase, int32 HintCount, int32 SolutionCase)
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


bool SetCaseNumberSafeRand(TArray<int32>& CaseNumbers, int32* AssignedCase, int32 HintCount, int32 SolutionCase)
{
    int32 RandomIndex;
    TArray<int32> AvailableIndices;

    for (int32 i = 0; i < HintCount; ++i) 
        if (CaseNumbers[i] != SolutionCase)
            AvailableIndices.Add(i);
    return SetToRandomIndexFromSelection(AvailableIndices, CaseNumbers, AssignedCase, &RandomIndex);
}

bool GetRoles(TArray<ULogicData*>& AllIdentifiers, TArray<ULogicData*>& AllRoles, 
    TArray<ULogicData*>& LogicArray, int32 RolesCount, int32 IdentifierCount, int32 j, int32 LogicSize)
{

    // Check this when testing as it could cause issues
    if (j + IdentifierCount + RolesCount > LogicSize)
        return false;

    for (int k = 0; k < IdentifierCount; k++)
        AllIdentifiers.Add(LogicArray[j + k]);

    for (int k = 0; k < RolesCount; k++)
        AllRoles.Add(LogicArray[j + k + IdentifierCount]);

    return true;
}

bool SolveForEqual(TArray<ULogicData*>& AllIdentifiers, TArray<ULogicData*>& AllRoles, FLogic* LogicStatement, TArray<int32>& CaseNumbers, TArray<int32>& NewSubjectData,
    TArray<bool>& Liars, TArray<bool>& TruthTellers, bool IsNot, int32 MaxLiarCount, int32 CaseSolution, int32 HintCount) 
{
    auto MyIdentifier = AllIdentifiers[0]->LogicStatement;
    auto MyRole = AllRoles[0]->LogicStatement;
    int32 newSubjectValue;

    if (MyIdentifier == &LogicNamespace::CaseNumber)
    {
        if (MyRole == &LogicNamespace::Danger)
        {
            if (!IsNot)
                newSubjectValue = CaseSolution; 
            else {
                if (!SetCaseNumberSafeRand(CaseNumbers, &newSubjectValue, HintCount, CaseSolution))
                    return false;
            }
        }
        else if (MyRole == &LogicNamespace::Safe)
        {
            if (!IsNot) {
                if (!SetCaseNumberSafeRand(CaseNumbers, &newSubjectValue, HintCount, CaseSolution))
                    return false;
            }
            else
                newSubjectValue = CaseSolution;
        }
        else if (MyRole == &LogicNamespace::Lying)
        {
            if (!IsNot) {
                if (!SetCaseNumberLiarRand(Liars, TruthTellers, CaseNumbers, &newSubjectValue, HintCount, MaxLiarCount))
                    return false;
            }
            else
                if (!SetCaseNumberTruthfulRand(Liars, TruthTellers, CaseNumbers, &newSubjectValue, HintCount, MaxLiarCount))
                    return false;
        }
        else if (MyRole == &LogicNamespace::Truthful)
        {
            if (!IsNot) {
                if (!SetCaseNumberTruthfulRand(Liars, TruthTellers, CaseNumbers, &newSubjectValue, HintCount, MaxLiarCount))
                    return false;
            }
            else
                if (!SetCaseNumberTruthfulRand(Liars, TruthTellers, CaseNumbers, &newSubjectValue, HintCount, MaxLiarCount))
                    return false;
        }
    }
    else if (MyIdentifier == &LogicNamespace::Lying)
    {   
        // Find or create a Liar that makes this statement true
        // e.g A Liar is Safe, A Liar is Danger, A Liar is Case11
        // Leave for now as this would be cool, but is not needed 
    }
    else if (MyIdentifier == &LogicNamespace::Colour)
    {
        // Find or create a BriefCase of Colour X that makes this statement true
        // e.g A Green is Safe, A Yellow is Danger, A Red is Case11
        // Leave for now as this would be cool, but is not needed 
    }

    NewSubjectData.Add(newSubjectValue);
    return true;
}

bool SolveForGreater(TArray<ULogicData*>& AllIdentifiers, TArray<ULogicData*>& AllRoles, FLogic* LogicStatement, TArray<int32>& CaseNumbers, TArray<int32>& NewSubjectData,
    TArray<bool>& Liars, TArray<bool>& TruthTellers, bool IsNot, int32 MaxLiarCount, int32 CaseSolution, int32 HintCount)
{
    auto MyIdentifier = AllIdentifiers[0]->LogicStatement;
    auto MyRole = AllRoles[0]->LogicStatement;
    int32 newSubjectValue;

    if (MyIdentifier == &LogicNamespace::CaseNumber)
    {
        if (MyRole == &LogicNamespace::Danger) // Above Case Number is Danger
        {                
            if (!IsNot) {
                if (!GetCaseNumberBelowDanager(CaseNumbers, &newSubjectValue, HintCount, CaseSolution))
                    return false;
            }
            else
                if (!GetCaseNumberAboveDanger(CaseNumbers, &newSubjectValue, HintCount, CaseSolution))
                    return false;           
        }
        else if (MyRole == &LogicNamespace::Safe) // Above Case Number is Safety
        {
            if (!IsNot) {
                if (!GetCaseNumberAboveDanger(CaseNumbers, &newSubjectValue, HintCount, CaseSolution))
                    return false;
            }
            else
                if (!GetCaseNumberBelowDanager(CaseNumbers, &newSubjectValue, HintCount, CaseSolution))
                    return false;
        }
        // Above Case Number is Liar
        else if (MyRole == &LogicNamespace::Lying)
        {
            if (!IsNot) { 
                if (!SetCaseNumberLiarRand(Liars, TruthTellers, CaseNumbers, &newSubjectValue, HintCount, MaxLiarCount))
                    return false;
            }
            else
                if (!SetCaseNumberTruthfulRand(Liars, TruthTellers, CaseNumbers, &newSubjectValue, HintCount, MaxLiarCount))
                    return false;
        }

        // Above Case Number is a Truthful Case
        else if (MyRole == &LogicNamespace::Truthful)
        {
            if (!IsNot) {
                if (!SetCaseNumberTruthfulRand(Liars, TruthTellers, CaseNumbers, &newSubjectValue, HintCount, MaxLiarCount))
                    return false;
            }
            else
                if (!SetCaseNumberTruthfulRand(Liars, TruthTellers, CaseNumbers, &newSubjectValue, HintCount, MaxLiarCount))
                    return false;
        }

    }
    else if (MyIdentifier == &LogicNamespace::Lying)
    {
        // Find or create a Liar that makes this statement true
        // e.g A Liar is Safe, A Liar is Danger, A Liar is Case11
        // Leave for now as this would be cool, but is not needed => 
    } 
    NewSubjectData.Add(newSubjectValue);
    return true;

}

bool SolveForStatement(int j, FLogic* LogicStatement, TArray<int32>& CaseNumbers, TArray<int32>& NewSubjectData, TArray<ULogicData*>& LogicArray,
    TArray<bool>& Liars, TArray<bool>& TruthTellers, int32* SkipCount, bool InConditionLoop, bool IsNot, int32 MaxLiarCount, int32 CaseSolution, 
    int32 HintCount, int32 LogicSize)
{

    if (InConditionLoop)
        return false; // THIS IS A REMINDED TO SOLVE FOR THIS CASE NOT THE INTENTIONAL FUNCTIONALITY

    const FLogicStatement* LogicEquation = static_cast<const FLogicStatement*>(LogicStatement);
    auto IdentifierCount = LogicEquation->IdentifierCount;
    auto RolesCount = LogicEquation->RolesCount;

    TArray<ULogicData*> AllIdentifiers;
    TArray<ULogicData*> AllRoles;

    if (!GetRoles(AllIdentifiers, AllRoles, LogicArray, RolesCount, IdentifierCount, j, LogicSize))
        return false;

    if (LogicStatement == &LogicNamespace::Equal)
        if (!SolveForEqual(AllIdentifiers, AllRoles, LogicStatement, CaseNumbers, NewSubjectData, Liars, TruthTellers, IsNot, MaxLiarCount, CaseSolution, HintCount))
            return false;
    else if (LogicStatement == &LogicNamespace::Greater) 
        if (!SolveForEqual(AllIdentifiers, AllRoles, LogicStatement, CaseNumbers, NewSubjectData, Liars, TruthTellers, IsNot, MaxLiarCount, CaseSolution, HintCount))
            return false;

    SkipCount += IdentifierCount + RolesCount;
    return true;
}

bool CreateHint(int i, FUCaseHint* NewCaseHint, TArray<int32> CaseNumbers, int32 CaseSolution, UHintCollection* HintData, int32 HintCount, TArray<bool>& Liars, TArray<bool>& TruthTellers) {

    UHint* HintType = SelectHint(HintData);
    TArray<int32> NewSubjectData;

    auto LogicArray = HintType->logic;

    bool ConditionMet = false;
    bool InConditionLoop = false;
    bool IsNot = false;

    int32 SkipCount = 0;
    int32 LogicSize = LogicArray.Num();
    int32 MaxLiarCount = HintData->MaxLiarCount;

    for (int j = 0; j < LogicSize; j++)
    {
        auto LogicStatement = LogicArray[j]->LogicStatement;

        if (SkipCount > 0) {
            SkipCount--;
            continue;
        }

        switch (LogicStatement->LogicType)
        {
        case (LogicTypes::MAX):
            break;
        case (LogicTypes::Unassigned):
            break;
        case (LogicTypes::Identifiers):
            break;
        case (LogicTypes::Roles):
            break;

        case (LogicTypes::Conditions):
            if (LogicStatement == &LogicNamespace::If)
            {
                InConditionLoop = true;
                ConditionMet = false;
            }
            if (LogicStatement == &LogicNamespace::Then)
                IsNot = ConditionMet ? false : true;
            break;
        case (LogicTypes::Conjunctive):

            if (InConditionLoop) {
                if (LogicStatement == &LogicNamespace::Or && ConditionMet)
                    SkipCount = 1;
                else if (LogicStatement == &LogicNamespace::And)
                    ConditionMet ? ConditionMet = false : SkipCount = 1; // Force next statment to need to be true or skip next as it not longer factors (does not work for multiple conjunctives- may add if time (x to doubt))
            }
            else {
                // Add and logic for statements idk
            }
            break;

        case (LogicTypes::Basis):
            if (LogicStatement == &LogicNamespace::Is)
                break;
            else if (LogicStatement == &LogicNamespace::Not)
                IsNot = !IsNot;
            break;

        case (LogicTypes::Statements):
            bool FoundSolution = SolveForStatement(j, LogicStatement, CaseNumbers, NewSubjectData, LogicArray, Liars, TruthTellers, 
                &SkipCount, InConditionLoop, IsNot, MaxLiarCount, CaseSolution, HintCount, LogicSize);
            break;
        }
    }

    NewCaseHint->hint = HintType;
    NewCaseHint->SubjectData = NewSubjectData;
    NewCaseHint->hintText = "";
    return true;
}

TArray<FUCaseHint> UHintManager::GetLevelHints(TArray<int32> CaseNumbers, int32 CaseSolution, UHintCollection* HintData)
{
    TArray<FUCaseHint> ChosenHints;   
    TArray<bool> Liars;
    TArray<bool> TruthTellers;

    int32 HintCount = CaseNumbers.Num();

    ChosenHints.SetNum(HintCount);
    Liars.SetNum(HintCount);
    TruthTellers.SetNum(HintCount);

    if (HintData->HintCollections.Num() <= 0)
        return ChosenHints;

    for (int i = 0; i < HintCount; i++)
    {
        FUCaseHint NewCaseHint;
        bool HintPossible = CreateHint(i, &NewCaseHint, CaseNumbers, CaseSolution, HintData, HintCount, Liars, TruthTellers);

        if (!HintPossible) {
            // Somehow deal with this!!!
        }

        ChosenHints.Add(NewCaseHint);
    }

    // Change ChosenHints to reflect liars and truthtellers
    return ChosenHints;
}


