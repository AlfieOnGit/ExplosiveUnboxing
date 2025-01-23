#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InDialogue.h"
#include "DialogueManagerParent.generated.h"


UCLASS()
class EXPLOSIVEUNBOXING_API UDialogueManagerParent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDialogueManagerParent();

	UFUNCTION(BlueprintImplementableEvent, Category = "Output")
	void SetDialogue(UInDialogue* InData);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
