#include "GameManager.h"

void UGameManager::OnNewGame()
{
	Score = 0;
}


void UGameManager::OnPlayerChoose()
{
	
}


void UGameManager::OnGameOver()
{
	if (TurnManager) TurnManager->ClearCases();
	// Set scene to death screen
}
