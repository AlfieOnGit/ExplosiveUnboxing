#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Public/OnGameEvent.h"
#include "Public/OnCaseEvent.h"
#include "Public/InDialogue.h"
#include "Public/OnDialogueEvent.h"
#include "Public/IDialogueManager.h"
#include "Public/BriefCaseData.h"

#include "Misc/OutputDeviceNull.h"
#include "TurnManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPLOSIVEUNBOXING_API UTurnManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTurnManager() = default;

	// Dialogue refs:: refactor in the future to move this out of this class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UInDialogue* IntroDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UInDialogue* FirstOpenCase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UInDialogue* FirstChangeSelection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UInDialogue* HostFirstConversation;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UInDialogue* HostConversation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UInDialogue* SelectedCase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UInDialogue* ChangeSelectedCase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UInDialogue* OpenCase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UInDialogue* OpenCaseLoopFirst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UInDialogue* OpenCaseLoop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UInDialogue* OpenCaseLoopFinal;




	// To listen
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnCaseEvent* OnCaseClickEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnGameEvent* OnNPCInteractEvent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnGameEvent* OnChooseSolutionEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnGameEvent* OnSolutionCheckLoopEvent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnGameEvent* OnGameOverEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnGameEvent* OnSolvedEvent;
	
protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UBriefCaseData* BriefCaseDataManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	AActor* DialogueManager;

	int32 FirstSelected;
	void SetupListeners();
	void SetDialogue(UInDialogue* dialogue);
	void SetMenu(bool HasWon);


	bool PlayerChoosing = false;
	bool FirstSelect = true;
	bool Chosen = false;
	bool FirstOpen = true;
	bool FirstInteraction = true;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnCaseClickEventReciever(int32 CaseNumber);

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnNPCInteractEventReciever();

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnChooseSolutionEventReciever();

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnSolutionCheckLoopEventReciever();

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnSolvedEventReciever();

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnGameOverEventReciever();

	// Shouldn't be required, but could implement a system where after every dialogue an ResumeGame is Invoked to unpause this TurnManager where the turn manager would pause before calling SetDialogue()
	//void ResumeGameEventReciever();
};
