#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"

#include "HintManager.h"
#include "Briefcase.h"
#include "Hint.h"
#include <stack>

#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "SpriteComponent2D.h"
#include "BriefcasePoolManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPLOSIVEUNBOXING_API UBriefcasePoolManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBriefcasePoolManager();

	UPROPERTY(EditAnywhere, Category = "BriefCasePool")
	TSubclassOf<AActor> BriefCasePrefab;

	UPROPERTY(EditAnywhere, Category = "BriefCasePool")
	TArray<AActor*> SpawnPointComponents;

	UPROPERTY(EditAnywhere, Category = "BriefCasePool")
	TArray<UPaperSprite*> BriefcaseSpritesOrdered;

	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	TArray<UBriefcase*> SpawnBriefCases(TArray<int32>& CaseNumbers, TArray<FString>& hintTexts, int32 Solution);

	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	void CleanPool();


private: 

	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	AActor* CreateNewBriefCase(const FVector MySpawnPoint, const FRotator MySpawnRot);

	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	AActor* RecycleUnusedBriefCase(const FVector MySpawnPoint, const FRotator MySpawnRot);

	UFUNCTION(BlueprintCallable, Category = "BriefCasePool")
	UBriefcase* DefineBriefCaseData(AActor* BriefCase, int32 CaseNumber, bool IsDanger, FString HintText);

	TArray<AActor*> ActiveBriefCases;
	std::stack<AActor*> PooledBriefCases;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
