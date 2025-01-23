#include "TurnManager.h"


void UTurnManager::BeginPlay()
{
    Super::BeginPlay();

    if (AActor* Owner = GetOwner())
        BriefCaseDataManager = Owner->FindComponentByClass<UBriefCaseData>();
    SetupListeners();
    SetDialogue(IntroDialogue);
    FirstSelected = BriefCaseDataManager->GetRandomUnopenedCase();
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

// Using the cpp interface should also work, but Unity crashes ://
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

bool PlayerChoosing = false;
bool FirstSelect = true;
bool FirstInteraction = true;

void UTurnManager::OnCaseClickEventReciever(int32 CaseNumber)
{
    UE_LOG(LogTemp, Warning, TEXT("A case has been clciked"));

    if (!PlayerChoosing) {
        if (BriefCaseDataManager->IsSelectedCase(CaseNumber))
        {
            // Player is opening case
            SetDialogue(IntroDialogue);
        }
        else 
        {
            // Player is selecting case
            if (FirstSelect) 
            {
                BriefCaseDataManager->SetSelectedCase(CaseNumber);
                SetDialogue(IntroDialogue);
                FirstSelect = false;
            }
            else {
                BriefCaseDataManager->SetSelectedCase(CaseNumber);
                SetDialogue(IntroDialogue);
            }
        }
    }
    else 
    {
        // The player is choosing a case for solution
        BriefCaseDataManager->SetChosenCase(CaseNumber);
        SetDialogue(IntroDialogue);
    }
}

void UTurnManager::OnNPCInteractEventReciever()
{
    SetDialogue(IntroDialogue);
}


void UTurnManager::OnChooseSolutionEventReciever()
{
    PlayerChoosing = true;
}

void UTurnManager::OnSolutionCheckLoopEventReciever() 
{
    int ToOpen = BriefCaseDataManager->GetRandomUnopenedCase();
    if (BriefCaseDataManager->OpenAndCheckCase(ToOpen))
        SetDialogue(IntroDialogue);
    else 
        SetDialogue(IntroDialogue);
}


void UTurnManager::OnSolvedEventReciever() {}

void UTurnManager::OnGameOverEventReciever() {}

