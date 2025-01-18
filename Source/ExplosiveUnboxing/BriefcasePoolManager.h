#pragma once

#include "CoreMinimal.h"
#include "HintManager.h"
#include "Briefcase.h"
#include "Hint.h"


#include "Components/ActorComponent.h"
#include "BriefcasePoolManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPLOSIVEUNBOXING_API UBriefcasePoolManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBriefcasePoolManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BriefCasePool")
	UHintManager* MyHintManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
	AActor* HintManagerActor;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BriefCasePool")
	UHintCollection* hintColTest;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
