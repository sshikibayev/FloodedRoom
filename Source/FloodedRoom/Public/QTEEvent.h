#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStateManager.h"

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

	UFUNCTION(BlueprintCallable)
	bool getEventStarted();

	UFUNCTION(BlueprintCallable)
	void setKey(FString key);
	UFUNCTION(BlueprintCallable)
	FString getKey();

	UFUNCTION(BlueprintCallable)
	void skipCurrentTimer();
	UFUNCTION(BlueprintCallable)
	void timerHasEnd();
	
	

protected:
	virtual void BeginPlay() override;

private:	
	bool is_event_started{ false };
	bool is_qte_event_started{ false };
	float round_duration{ 2.0f };
	int max_rounds{ 4 };
	int current_round{ 0 };

	TArray<FString> qte_keys;
	FString key_from_event;
	FTimerHandle current_key_timer_handle;

	void setupKeys();
	void startEvent();
	void eventLogic();
	void resetEventKeys();
	void changeCurrentKey();
	void setupNextRound();
};