#pragma once

#include "CoreMinimal.h"
#include "Briefcase.h"
#include "BriefcasePoolManager.h"
#include "HintManager.h"
#include "Components/ActorComponent.h"
#include "Public/OnGameEvent.h"
#include "Public/OnCaseEvent.h"

#include "TurnManager.generated.h"

#define MAX_CASES 15


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPLOSIVEUNBOXING_API UTurnManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTurnManager() = default;
	
	TArray<int32> SelectBriefCaseData(int32 BriefCaseCount, int32* Solution);

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	int32 GetSolution(TArray<int32>& CaseNumbers);
	
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

	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void ClearCases();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	AActor* HintManagerActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	AActor* BriefcasePoolManagerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnCaseEvent* OnCaseSelectEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnCaseEvent* OnGameOverEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnCaseEvent* OnSolvedEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnCaseEvent* OnCaseSolutionCheckLoopEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnCaseEvent* OnCaseSolutionChosenEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnCaseEvent* OnNPCInteractEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UOnCaseEvent* OnCaseOpenEvent;
	
protected:	
	unsigned int CaseCount = 0;
	UBriefcase* Cases[MAX_CASES] { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UHintManager* MyHintManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UHintCollection* hintColTest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Briefcases")
	UBriefcasePoolManager* BriefcasePoolManager;

	void SetupListeners();

	// (For Kieran) We need a SetDialogue(DialogueTable*, int32, TArray<int32>, Fstring) Method 
	// DialogueTable*:: reference to the next dialogueTable. 
	//		* (For Alfie) We will need to know what state we are in to work out what dialogue to pass through: 
	//			Easy version, keep track of if first time caseSelected e.t.c (Modular version would probably be another class for a statemachine, but lets ignore that)
	// int32:: some dialogue mentions data like case X which we will need to know (Modular version would be TArray, but I don't think we'll need more than one data point)
	// TArray<int32>:: Some dialogue mentions which case are you choosing so we need a way to get this data
	// Fstring :: Hint text passed through
	// Ideally this would all be a TArray with templated type or a structv passed through- I've written this as the simpliest method, but choose what function paramets would work best

	// At beginning of level (in BeginPlay): 
	// Call func:: SetDialogue(DialogueTable*, CaseNumber, Null)
	// Where CaseNumber is a random first case, & DialogueTable* is intro dialogue
	virtual void BeginPlay() override;

	// A case is clicked; 
	// Invoked from BriefCase
	// Call SetSelected on Case using CaseNumber (coulds be set in Briefcase, but to prevent multi clicks it's safer here in case Open is triggered before SelectDialogue) 
	// Call func:: SetDialogue(DialogueTable*, CaseNumber, Null, "")
	// The DialogueTable* for first selection is different & also changes if CaseNumber recieved by OnSelectCaseEventReciever is different to the originally passed CaseNumber (refer to script)
	// If this is called again before OnCaseOpenEventReciever recieves an event DialogueTable* will change also (refer to script)
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnSelectCaseEventReciever(int32 CaseNumber);

	// A case is opened
	// Invoked from BriefCase (Brief Case now has selected bool to invoke selcted ? OnSelectCaseEvent : OnCaseOpenEvent)
	// Call OpenCase on case
	// Call GetHintText()
	// Call func:: SetDialogue(DialogueTable*, CaseNumber, Null, HintText)
	// DialogueTable* will change if first case opened
	// DialogueTable* will also change if CaseNumber is the Solution (the bomb) (For Kieran: dilaogue with predetermine choice will be easiest to add with a single DialogueTable so we have have to add the 
	//		same text to multiple tables unless you want to look at recursive dialogue tables in dialogue tables)
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnCaseOpenEventReciever(int32 CaseNumber);

	// The player wishes to talk to the Host NPC to select a case 
	// Invoked by OnClick NPC Component
	// Call func::SetDialogue(DialogueTable*, -1, TArray<CaseNumbers>, "")
	// DialogueTable* will change if interacted before OnCaseOpenEventReciever recieves an event for the first time  (refer to script)
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnNPCInteractEventReciever(int32 CaseNumber);

	// The player has selected a choice
	// Invoked by DialogueManager: (For Kieran extend: Dialogue struct to include UEventDataAsset* parameter that we can set in Dialogue tables=> then after dialogue has finished Invoke this event if it is not nullptr)
	// Call OpenCase on case
	// Call GetHintText()
	// call func:: SetDialogue(DialogueTable*, CaseNumber, Null, HintText)
	// Will change if first case opened, or if CaseNumber is solution case (explosion)
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnCaseSolutionChosenEventReciever(int32 CaseNumber);

	// Briefcases are being opened in loop showing if solution was correct
	// Invoked by DialogueManager:
	// Call	OpenCase on case
	// Call GetHintText()
	// call func:: SetDialogue(DialogueTable*, CaseNumber, Null, HintText)
	// DialogueTable* will change if CaseNumber is the only can that is !Opened, or if CaseNumber is solution case (explosion)
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnCaseSolutionCheckLoopEventReciever(int32 CaseNumber);

	// Invoked by DialogueManager:
	// This will have happened after game over dialogue has already triggered so no new game state is required
	// Create new level and set Level 2 intro dialogue or if no level 2 proceed to Vicotry screen
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnSolvedEventReciever(int32 CaseNumber);

	// Invoked by DialogueManager:
	// This will have happened after game over dialogue has already triggered so no new game state is required
	// Proceed to Game Over screen or to main menu
	UFUNCTION(BlueprintCallable, Category = "Briefcases")
	void OnGameOverEventReciever(int32 CaseNumber);


	// Shouldn't be required, but could implement a system where after every dialogue an ResumeGame is Invoked to unpause this TurnManager where the turn manager would pause before calling SetDialogue()
	//void ResumeGameEventReciever();

};
