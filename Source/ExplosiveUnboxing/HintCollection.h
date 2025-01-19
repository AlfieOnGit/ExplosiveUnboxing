#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Hint.h"

#include "HintCollection.generated.h"


UCLASS(BlueprintType)
class EXPLOSIVEUNBOXING_API UHintCollection : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HintCollections")
    TArray<UHint*> HintCollections;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HintCollections")
    int32 MaxLiarCount;
};
