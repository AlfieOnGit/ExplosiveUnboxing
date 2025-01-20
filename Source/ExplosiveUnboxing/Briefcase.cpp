#include "Briefcase.h"

void UBriefcase::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bEnableClickEvents = true;

	if (Owner) 
		Owner->EnableInput(GetWorld()->GetFirstPlayerController());

	if (Owner)
		Owner->OnClicked.AddDynamic(this, &UBriefcase::OnClick);
}

void UBriefcase::OnClick(AActor* TouchedActor, FKey ButtonPressed)
{
	UE_LOG(LogTemp, Log, TEXT("OnClickTriggered"));

	if (this->Opened)
		return;

	if (this->Selected) 
	{
		if (OnCaseOpenEvent)
			OnCaseOpenEvent->CallEvent.Broadcast(this->Number);
	}
	else {
		if (OnCaseSelectEvent) 
			OnCaseSelectEvent->CallEvent.Broadcast(this->Number);
	}
}


void UBriefcase::ResetBriefcase(int32 NewNumber, bool NewIsDanger, FString NewHintText)
{
	this->Number = NewNumber;
	this->Opened = false;
	this->Selected = false;
	this->IsDanger = NewIsDanger;
	this->HintText = NewHintText;
}

bool UBriefcase::Open()
{
	this->Opened = true;
	return this->IsDanger;
}

