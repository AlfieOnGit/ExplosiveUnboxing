#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InDialogue.h"
#include "IDialogueManager.generated.h"

UINTERFACE(MinimalAPI)
class UIDialogueManager : public UInterface
{
	GENERATED_BODY()
};


class EXPLOSIVEUNBOXING_API IIDialogueManager
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetNewDialogue(UInDialogue* InData);

};
