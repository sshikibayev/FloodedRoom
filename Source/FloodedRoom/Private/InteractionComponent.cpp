#include "InteractionComponent.h"


UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameStateManager::StaticClass(), state_managers);

	world = GetWorld();
	setupGameStateManager();
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractionComponent::interact()
{
	if (world) {
		if (isTraceCaluclationValid()) {
			startAction();
		}
	}
}

void UInteractionComponent::release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released"));
	endAction();
}

bool UInteractionComponent::isTraceCaluclationValid()
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * max_interact_distance;

	FCollisionShape sphere{ FCollisionShape::MakeSphere(interact_radius) };
	FHitResult hit_result;
	auto is_hit = world->SweepSingleByChannel(
		hit_result,
		start, end,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		sphere
	);

	return is_hit;
}

void UInteractionComponent::setupGameStateManager()
{
	if (state_managers.Num() <= 0) {
		UE_LOG(LogTemp, Error, TEXT("No game state managers were found"));
	}
	else if (state_managers.Num() > 1) {
		UE_LOG(LogTemp, Error, TEXT("More then one game state managers were found"));
	}
	else {
		for (auto manager : state_managers) {
			state_manager = Cast<AGameStateManager>(manager);
		}
	}
}

void UInteractionComponent::startAction()
{
	UE_LOG(LogTemp, Warning, TEXT("action is started"));	
	state_manager->setState(StateType::Interaction);
}

void UInteractionComponent::endAction()
{
	state_manager->setState(StateType::Default);
	UE_LOG(LogTemp, Warning, TEXT("action is ended"));
}