#include "DialogueManagerParent.h"

UDialogueManagerParent::UDialogueManagerParent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UDialogueManagerParent::BeginPlay()
{
	Super::BeginPlay();
}

void UDialogueManagerParent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

