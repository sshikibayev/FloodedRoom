#include "Room.h"

ARoom::ARoom()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARoom::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()) {
		GetWorldTimerManager().SetTimer(water_flood_timer_handle, this, &ARoom::startWaterFlood, flood_timer, false, flood_timer);
	}
}

void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARoom::startWaterFlood()
{
	GetWorldTimerManager().ClearTimer(water_flood_timer_handle);
	is_water_started = true;
}