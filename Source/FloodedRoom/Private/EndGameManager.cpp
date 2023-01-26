#include "EndGameManager.h"

AEndGameManager::AEndGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEndGameManager::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()) {
		GetWorldTimerManager().SetTimer(end_game_timer_handle, this, &AEndGameManager::theGameEnd, game_lenght, false, game_lenght);
	}
}

void AEndGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AEndGameManager::getPlayerWin()
{
	return is_player_win_condition;
}

void AEndGameManager::setPlayerWin(bool is_player_win)
{
	is_player_win_condition = is_player_win;

	if (!is_player_win_condition) {
		win_or_lose_text = "You Lost!";
	}
}

void AEndGameManager::theGameEnd()
{
	GetWorldTimerManager().ClearTimer(end_game_timer_handle);
	game_state->setState(StateType::EndGame);
	setPlayerWin(false);
}