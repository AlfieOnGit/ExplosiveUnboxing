#include "Briefcase.h"

void UBriefcase::BeginPlay()
{
	Super::BeginPlay();
}

void UBriefcase::OnClick()
{
	UE_LOG(LogTemp, Log, TEXT("OnClickTriggered"));

	if (this->Opened)
		return;

	if (OnCaseClickEvent)
		OnCaseClickEvent->CallEvent.Broadcast(this->Number);
}


void UBriefcase::ResetBriefcase(int32 NewNumber, bool NewIsDanger, FString NewHintText)
{
	this->Number = NewNumber;
	this->Opened = false;
	this->Selected = false;
	this->IsDanger = NewIsDanger;
	this->HintText = NewHintText;
}

FString UBriefcase::Open()
{
	this->Opened = true;
	return this->HintText;
}

