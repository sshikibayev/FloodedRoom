#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameStateManager.h>
#include <Components/BoxComponent.h>

#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLOODEDROOM_API UInteractionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool isPlayerInOverlap();
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
	UBoxComponent* collision_box;
	UPROPERTY()
	TArray<AActor*> state_managers;
	UPROPERTY()
	AGameStateManager* state_manager;
	UPROPERTY()
	AActor* valve;

	UPROPERTY(EditAnywhere)
	float max_interact_distance{ 300.0f };
	UPROPERTY(EditAnywhere)
	float interact_radius{ 60 };

	float valve_rotation_speed{ 100 };
	bool is_valve_rotating{ false };
	FName interaction_tag{ "Interaction" };
	bool is_player_in_interaction_zone{ false };
	bool is_player_inside_overlap{ false };

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index, bool from_sweep, const FHitResult& hit_result);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index);

	void setupGameStateManager();
	void setupCollision();
	void toggleZoneAndOverlap(bool toggle);
	bool is_actor_valid(AActor* other_actor);
	bool isTraceCaluclationValid();
	void rotateValve(float DeltaTime);
	void startAction();
	void endAction();
};
