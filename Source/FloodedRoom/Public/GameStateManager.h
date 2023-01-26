#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <StateType.h>
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <Camera/CameraComponent.h>

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

	UPROPERTY()
	UCharacterMovementComponent* move_comp;
	UPROPERTY()
	UCameraComponent* camera;

	void setupComponents(APawn* pawn);
	void disablePlayerInput();
	void enablePlayerInput();
	void setupCurrentState();
	void setupDefaultState();
	void setupOverllapState();
	void setupInteractionState();
	void setupEndGameState();
};