#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameStateManager.h>

#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLOODEDROOM_API UInteractionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void interact();
	UFUNCTION(BlueprintCallable)
		void release();
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	UWorld* world;
	UPROPERTY()
	TArray<AActor*> state_managers;
	UPROPERTY()
	AGameStateManager* state_manager;

	UPROPERTY(EditAnywhere)
	float max_interact_distance{ 400.0f };
	UPROPERTY(EditAnywhere)
	float interact_radius{ 100 };

	bool isTraceCaluclationValid();
	void setupGameStateManager();
	void startAction();
	void endAction();
};
