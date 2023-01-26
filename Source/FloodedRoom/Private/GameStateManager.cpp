#include "GameStateManager.h"

AGameStateManager::AGameStateManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameStateManager::BeginPlay()
{
	Super::BeginPlay();

	auto player_pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	camera = player_pawn->FindComponentByClass<UCameraComponent>();
	move_comp = player_pawn->FindComponentByClass<UCharacterMovementComponent>();

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
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Default state"));
	}
	enablePlayerInput();
}

void AGameStateManager::setupOverllapState()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Overlap state"));
	}
	enablePlayerInput();
}

void AGameStateManager::setupInteractionState()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Interaction state"));
	}
	disablePlayerInput();
}

void AGameStateManager::setupEndGameState()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("EndGame state"));
	}
	disablePlayerInput();
}