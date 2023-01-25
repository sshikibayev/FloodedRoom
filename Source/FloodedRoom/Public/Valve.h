#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameStateManager.h>

#include "Valve.generated.h"


UCLASS()
class FLOODEDROOM_API AValve : public AActor
{
	GENERATED_BODY()
	
public:	
	AValve();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGameStateManager* game_state;
	
	UPROPERTY(EditAnywhere)
	float valve_rotation_speed{ 30 };

protected:
	virtual void BeginPlay() override;

private:
	FName actor_tag{ "Interaction" };

	void setupValveRotation(float DeltaTime);
	void rotateValve(float DeltaTime);
	void restoreValve();
};