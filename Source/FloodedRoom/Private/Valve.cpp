#include "Valve.h"

AValve::AValve()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AValve::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(actor_tag);
}

void AValve::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(game_state){
		setupValveRotation(DeltaTime);
	}
}

void AValve::setupValveRotation(float DeltaTime)
{
	if (game_state->getState() == StateType::Interaction) {
		rotateValve(DeltaTime);
	}
	else {
		restoreValve();
	}
}

void AValve::rotateValve(float DeltaTime)
{
	FQuat quat_rotation = FQuat(FRotator(0, 0, -valve_rotation_speed * DeltaTime));
	AddActorLocalRotation(quat_rotation);
}

void AValve::restoreValve()
{
	if (GetActorRotation() != FRotator::ZeroRotator) {
		SetActorRotation(FRotator::ZeroRotator);
	}
}