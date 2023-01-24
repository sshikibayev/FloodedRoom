#include "EndGameManager.h"

AEndGameManager::AEndGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEndGameManager::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()) {
		GetWorldTimerManager().SetTimer(end_game_timer_handle, this, &AEndGameManager::theGameEnd, game_lenght, true, game_lenght);
	}
}

void AEndGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndGameManager::theGameEnd()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("The game has end"));
	}

	GetWorldTimerManager().ClearTimer(end_game_timer_handle);
	showEndGameUI();
}

void AEndGameManager::showEndGameUI()
{

}