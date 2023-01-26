#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameStateManager.h>

#include "QTEEvent.generated.h"

UCLASS()
class FLOODEDROOM_API AQTEEvent : public AActor
{
	GENERATED_BODY()
		
public:	
	AQTEEvent();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	AGameStateManager* state_manager;

	UPROPERTY(BlueprintReadWrite)
	FString current_key;

	UPROPERTY(BlueprintReadWrite)
	int current_round{ 0 };

	UFUNCTION(BlueprintCallable)
	bool getEventStarted();
	UFUNCTION(BlueprintCallable)
	void timerHasEnd();
	UFUNCTION(BlueprintCallable)
	void skipCurrentTimer();
	UFUNCTION(BlueprintCallable)
	void setKey(FString key);
	UFUNCTION(BlueprintCallable)
	FString getKey();

protected:
	virtual void BeginPlay() override;

private:	
	bool is_event_started{ false };
	bool is_qte_event_started{ false };
	TArray<FString> qte_keys;
	float round_duration{ 2.0f };
	FString key_from_event;
	int max_rounds{ 4 };
	FTimerHandle current_key_timer_handle;

	void setupKeys();
	void startEvent();
	void eventLogic();
	void changeCurrentKey();
};