#include "GameStateManager.h"

AGameStateManager::AGameStateManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameStateManager::BeginPlay()
{
	Super::BeginPlay();

	auto player_pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (player_pawn) {
		setupComponents(player_pawn);
	}
	

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

TEnumAsByte<StateType> AGameStateManager::getState()
{
	return state_type;
}

void AGameStateManager::setupComponents(APawn* pawn) {
	camera = pawn->FindComponentByClass<UCameraComponent>();
	move_comp = pawn->FindComponentByClass<UCharacterMovementComponent>();
}


void AGameStateManager::disablePlayerInput()
{
	if (move_comp) {
		move_comp->DisableMovement();
	}

	if (camera) {
		camera->Deactivate();
	}
}

void AGameStateManager::enablePlayerInput()
{
	if (move_comp) {
		move_comp->SetMovementMode(MOVE_Walking);
	}

	if (camera) {
		camera->Activate();
	}
}

void AGameStateManager::setupCurrentState()
{
	switch (state_type)
	{
	case StateType::Default:
		setupDefaultState();
		break;
	case StateType::Overlap:
		setupOverllapState();
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
	enablePlayerInput();
}

void AGameStateManager::setupOverllapState()
{
	enablePlayerInput();
}

void AGameStateManager::setupInteractionState()
{
	disablePlayerInput();
}

void AGameStateManager::setupEndGameState()
{
	disablePlayerInput();
}