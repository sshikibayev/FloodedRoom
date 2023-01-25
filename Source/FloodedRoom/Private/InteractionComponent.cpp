#include "InteractionComponent.h"


UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();
	setupGameStateManager();
	setupCollision();
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (is_valve_rotating) {
		rotateValve(DeltaTime);
	}
}

void UInteractionComponent::setupGameStateManager()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameStateManager::StaticClass(), state_managers);

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
void UInteractionComponent::setupCollision()
{
	collision_box = GetOwner()->FindComponentByClass<UBoxComponent>();
	if (collision_box) {
		collision_box->SetCollisionProfileName(TEXT("Trigger"));

		collision_box->OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::OnBeginOverlap);
		collision_box->OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::OnEndOverlap);
	}
}
bool UInteractionComponent::isPlayerInOverlap()
{	
	return is_player_in_interaction_zone;
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

void UInteractionComponent::OnBeginOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index, bool from_sweep, const FHitResult& hit_result)
{	
	if (is_actor_valid(other_actor)) {
		if (!is_player_inside_overlap) {
			toggleZoneAndOverlap(true);
		}
	}
	else {
		is_player_in_interaction_zone = false;
	}
}

void UInteractionComponent::OnEndOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index)
{
	toggleZoneAndOverlap(false);
}

void UInteractionComponent::toggleZoneAndOverlap(bool toggle)
{
	is_player_inside_overlap = toggle;
	is_player_in_interaction_zone = toggle;
}

bool UInteractionComponent::is_actor_valid(AActor* other_actor)
{
	bool is_actor_valid = other_actor && other_actor != GetOwner();
	bool is_actor_has_valid_tag = other_actor->ActorHasTag(interaction_tag);

	return is_actor_valid && is_actor_has_valid_tag;
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

	valve = hit_result.GetActor();

	return is_hit;
}

void UInteractionComponent::rotateValve(float DeltaTime)
{
	if (valve) {
		FQuat quat_rotation = FQuat(FRotator(0, 0, -valve_rotation_speed * DeltaTime));
		valve->AddActorLocalRotation(quat_rotation);
	}
}

void UInteractionComponent::startAction()
{
	is_player_in_interaction_zone = false;
	state_manager->setState(StateType::Interaction);
	is_valve_rotating = true;
}

void UInteractionComponent::endAction()
{
	state_manager->setState(StateType::Default);
	is_valve_rotating = false;
	toggleZoneAndOverlap(true);
	if (valve) {
		valve->SetActorRotation(FRotator::ZeroRotator);
	}
}