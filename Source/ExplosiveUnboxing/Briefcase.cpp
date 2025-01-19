#include "Briefcase.h"

void UBriefcase::BeginPlay()
{
	Super::BeginPlay();
}

void UBriefcase::ResetBriefcase(int32 NewNumber, bool NewIsDanger, FString NewHintText)
{
	this->Number = NewNumber;
	this->Opened = false;
	this->IsDanger = NewIsDanger;
	this->HintText = NewHintText;
}

bool UBriefcase::Open(FString OutText)
{
	OutText = this->HintText;
	this->Opened = true;
	return this->IsDanger;
}

