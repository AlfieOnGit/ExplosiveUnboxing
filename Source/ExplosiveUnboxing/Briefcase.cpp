#include "Briefcase.h"


void UBriefcase::BeginPlay()
{
	Super::BeginPlay();
}

UBriefcase::UBriefcase(int const Number, UHint* Hint)
{
	PrimaryComponentTick.bCanEverTick = false;

	this->Number = Number;
	this->Hint = Hint;
}


UHint* UBriefcase::Open()
{
	this->Opened = true;
	return this->Hint;
}

