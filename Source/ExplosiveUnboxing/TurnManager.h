#pragma once

#include "CoreMinimal.h"
#include "Briefcase.h"
#include "Components/ActorComponent.h"
#include "TurnManager.generated.h"

#define MAX_CASES 10


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPLOSIVEUNBOXING_API UTurnManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTurnManager() = default;
// protected:
// 	// Called when the game starts
// 	virtual void BeginPlay() override;
//
// public:	
// 	// Called every frame
// 	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	int GetBriefcaseCount() const { return CaseCount; }
	
	/**
	 * Adds a new briefcase to the end of the briefcase array
	 * @param Briefcase New briefcase
	 */
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void AppendCase(UBriefcase* Briefcase) { Cases[CaseCount++] = Briefcase; }

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void SetCase(int const Index, UBriefcase* Briefcase) { Cases[Index] = Briefcase; }

	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	UBriefcase* GetCase(int const Index) const { return Cases[Index]; }

protected:
	unsigned int CaseCount = 0;
	UBriefcase* Cases[MAX_CASES] { nullptr };
};
