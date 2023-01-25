#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <StateType.h>

#include "GameStateManager.generated.h"

UCLASS()
class FLOODEDROOM_API AGameStateManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameStateManager();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<StateType> getState();

	void setState(TEnumAsByte<StateType> state);

protected:
	virtual void BeginPlay() override;

private:
	TEnumAsByte<StateType> state_type;

	void setupCurrentState();
	void setupDefaultState();
	void setupInteractionState();
	void setupEndGameState();
};