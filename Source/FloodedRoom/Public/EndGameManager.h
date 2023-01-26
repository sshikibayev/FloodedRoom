#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameStateManager.h>

#include "EndGameManager.generated.h"


UCLASS()
class FLOODEDROOM_API AEndGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AEndGameManager();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGameStateManager* game_state;

	UPROPERTY(BlueprintReadWrite)
	FString win_or_lose_text {"You Win!" };

	UFUNCTION(BlueprintCallable)
	bool getPlayerWin();

	void setPlayerWin(bool is_player_win);
	

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	FTimerHandle end_game_timer_handle;
	UPROPERTY(EditDefaultsOnly)
	float game_lenght{ 5.0f };

	bool is_player_win_condition{ true };

	void theGameEnd();
};