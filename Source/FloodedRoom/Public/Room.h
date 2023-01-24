#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Room.generated.h"

UCLASS()
class FLOODEDROOM_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	ARoom();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	FTimerHandle water_flood_timer_handle;
	UPROPERTY(EditAnywhere)
	float flood_timer{ 5.0f };

	void startWaterFlood();
};