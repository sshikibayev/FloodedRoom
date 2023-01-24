#include "GameStateManager.h"

AGameStateManager::AGameStateManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameStateManager::BeginPlay()
{
	Super::BeginPlay();

	setState(StateType::Default);
}

void AGameStateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameStateManager::setState(TEnumAsByte<StateType> state)
{
	state_type = state;
	setupCurrentState();
}

void AGameStateManager::setupCurrentState()
{
	switch (state_type)
	{
	case StateType::Default:
		setupDefaultState();
		break;
	case StateType::Interaction:
		setupInteractionState();
		break;
	case StateType::EndGame:
		setupEndGameState();
		break;
	default:
		break;
	}
}

void AGameStateManager::setupDefaultState()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Default state"));
	}
}

void AGameStateManager::setupInteractionState()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Interaction state"));
	}
}

void AGameStateManager::setupEndGameState()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("EndGame state"));
	}
}