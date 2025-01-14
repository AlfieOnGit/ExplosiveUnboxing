#pragma once

#include "CoreMinimal.h"
#include "Hint.h"
#include "Engine/DataAsset.h"
#include "Briefcase.generated.h"

/**
 * Data asset briefcase, not the game object
 */
UCLASS()
class EXPLOSIVEUNBOXING_API UBriefcase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UBriefcase() : UBriefcase(-1, nullptr) { }
	
	explicit UBriefcase(int Number, UHint* Hint = nullptr);

	/**
	 * Sets the briefcase to open and returns the hint
	 * @return Hint* or NULLPTR if no hint (i.e. bomb case)
	 */
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	UHint* Open();

	
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	bool ContainsBomb() const { return Hint != nullptr; }
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	bool Opened = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	int Number;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UHint* Hint;
};
