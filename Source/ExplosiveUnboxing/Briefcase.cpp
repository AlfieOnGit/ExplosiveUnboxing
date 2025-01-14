#include "Briefcase.h"

UBriefcase::UBriefcase(int const Number, UHint* Hint)
{
	this->Number = Number;
	this->Hint = Hint;
}


UHint* UBriefcase::Open()
{
	this->Opened = true;
	return this->Hint;
}

