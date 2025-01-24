#include "Briefcase.h"

void UBriefcase::BeginPlay()
{
	Super::BeginPlay();
}

void UBriefcase::OnClick()
{
	if (this->Opened)
		return;

	if (OnCaseClickEvent)
		OnCaseClickEvent->CallEvent.Broadcast(this->Number);
}

void UBriefcase::SetSpriteOpened() 
{
	AActor* Owner = GetOwner();
	if (Owner) {
		USpriteComponent2D* SpriteComponent = Owner->FindComponentByClass<USpriteComponent2D>();
		if (SpriteComponent && OpenedSprite)
			SpriteComponent->SetSprite(OpenedSprite);
	}

}


void UBriefcase::ResetBriefcase(int32 NewNumber, bool NewIsDanger, FString NewHintText, FVector NewPlacement)
{
	this->Number = NewNumber;
	this->Opened = false;
	this->Selected = false;
	this->IsDanger = NewIsDanger;
	this->HintText = NewHintText;
	this->Placement = NewPlacement;
}

FString UBriefcase::Open()
{
	this->Opened = true;
	return this->HintText;
}

