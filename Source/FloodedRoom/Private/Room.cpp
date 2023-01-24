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
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Cyan, TEXT("Water started to flood"));
	}

	GetWorldTimerManager().ClearTimer(water_flood_timer_handle);
	is_water_started = true;
}