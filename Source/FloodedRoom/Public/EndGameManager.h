#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndGameManager.generated.h"

UCLASS()
class FLOODEDROOM_API AEndGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AEndGameManager();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	FTimerHandle end_game_timer_handle;
	UPROPERTY(EditDefaultsOnly)
	float game_lenght{ 5.0f };

	void theGameEnd();
	void showEndGameUI();
};