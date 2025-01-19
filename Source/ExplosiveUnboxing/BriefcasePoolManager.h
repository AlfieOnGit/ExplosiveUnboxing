#pragma once

#include "CoreMinimal.h"
#include "HintManager.h"
#include "Briefcase.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

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


	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> BriefCasePrefab;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BriefCasePool")
	UHintCollection* hintColTest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BriefCasePool")
	TArray<FVector> CaseSpawnPoints = { FVector(1, 2, 3), FVector(4, 5, 6), FVector(7, 8, 9) };

private: 

	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	void CreateNewBriefCase(FString hint);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
