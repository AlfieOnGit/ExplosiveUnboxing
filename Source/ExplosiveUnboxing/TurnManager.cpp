#include "TurnManager.h"


void UTurnManager::BeginPlay()
{
    Super::BeginPlay();

    if (AActor* Owner = GetOwner())
        BriefCaseDataManager = Owner->FindComponentByClass<UBriefCaseData>();
    SetupListeners();
    SetDialogue(IntroDialogue);
    FirstSelected = BriefCaseDataManager->GetRandomUnopenedCase();
    BriefCaseDataManager->SetSelectedCase(FirstSelected);
}

void UTurnManager::SetupListeners()
{
    if (OnCaseClickEvent)
        OnCaseClickEvent->CallEvent.AddDynamic(this, &UTurnManager::OnCaseClickEventReciever);
    if (OnGameOverEvent)
        OnGameOverEvent->CallEvent.AddDynamic(this, &UTurnManager::OnGameOverEventReciever);
    if (OnSolvedEvent)
        OnSolvedEvent->CallEvent.AddDynamic(this, &UTurnManager::OnSolvedEventReciever);
    if (OnSolutionCheckLoopEvent)
        OnSolutionCheckLoopEvent->CallEvent.AddDynamic(this, &UTurnManager::OnSolutionCheckLoopEventReciever);
    if (OnChooseSolutionEvent)
        OnChooseSolutionEvent->CallEvent.AddDynamic(this, &UTurnManager::OnChooseSolutionEventReciever);
    if (OnNPCInteractEvent)
        OnNPCInteractEvent->CallEvent.AddDynamic(this, &UTurnManager::OnNPCInteractEventReciever);
}

void  UTurnManager::SetDialogue(UInDialogue* dialogue) 
{
    if (UFunction* TriggerFunction = DialogueManager->FindFunction(TEXT("SetDialogue")))
    {
        struct FSetDialogueParams
        {
            UInDialogue* newDialogue;
        };

        uint8* ParamsBuffer = static_cast<uint8*>(FMemory_Alloca(TriggerFunction->ParmsSize));
        FMemory::Memzero(ParamsBuffer, TriggerFunction->ParmsSize);
        FSetDialogueParams* Params = reinterpret_cast<FSetDialogueParams*>(ParamsBuffer);
        Params->newDialogue = dialogue;
        DialogueManager->ProcessEvent(TriggerFunction, ParamsBuffer);
    }
}

void  UTurnManager::SetMenu(bool HasWon)
{
    if (UFunction* TriggerFunction = DialogueManager->FindFunction(TEXT("OpenMenu")))
    {
        struct FSetDialogueParams
        {
            bool HasWon;
        };

        uint8* ParamsBuffer = static_cast<uint8*>(FMemory_Alloca(TriggerFunction->ParmsSize));
        FMemory::Memzero(ParamsBuffer, TriggerFunction->ParmsSize);
        FSetDialogueParams* Params = reinterpret_cast<FSetDialogueParams*>(ParamsBuffer);
        Params->HasWon = HasWon;
        DialogueManager->ProcessEvent(TriggerFunction, ParamsBuffer);
    }
}

void UTurnManager::OnCaseClickEventReciever(int32 CaseNumber)
{
    if (Chosen)
        return;

    if (!PlayerChoosing) {
        if (BriefCaseDataManager->IsSelectedCase(CaseNumber))
        {
            BriefCaseDataManager->OpenAndCheckCase(CaseNumber);
            FirstOpen ? SetDialogue(FirstOpenCase) : SetDialogue(OpenCase);
            FirstOpen = false;
            FirstSelect = false;
        }
        else 
        {                
            BriefCaseDataManager->SetSelectedCase(CaseNumber);
            FirstSelect ? SetDialogue(FirstChangeSelection) : SetDialogue(SelectedCase);
            FirstSelect = false;
        }
    }
    else // The player has chosen a case for solution
    {
        Chosen = true;
        BriefCaseDataManager->SetChosenCase(CaseNumber);
        int ToOpen = BriefCaseDataManager->GetRandomUnopenedCase();
        BriefCaseDataManager->OpenAndCheckCase(ToOpen);
        SetDialogue(OpenCaseLoopFirst);
    }
}

void UTurnManager::OnNPCInteractEventReciever()
{
    FirstInteraction ? SetDialogue(HostFirstConversation) : SetDialogue(HostConversation);
    FirstInteraction = false;
}

void UTurnManager::OnChooseSolutionEventReciever()
{
    PlayerChoosing = true;
}

void UTurnManager::OnSolutionCheckLoopEventReciever() 
{

    int ToOpen = BriefCaseDataManager->GetRandomUnopenedCase();
    BriefCaseDataManager->OpenAndCheckCase(ToOpen);
    BriefCaseDataManager->IsSolution(ToOpen) ? SetDialogue(OpenCaseLoopFinal) : SetDialogue(OpenCaseLoop);
}


void UTurnManager::OnSolvedEventReciever() { SetMenu(true); }

void UTurnManager::OnGameOverEventReciever() { SetMenu(false); }

