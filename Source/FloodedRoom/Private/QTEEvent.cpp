#include "QTEEvent.h"

AQTEEvent::AQTEEvent()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AQTEEvent::BeginPlay()
{
	Super::BeginPlay();
	setupKeys();
}

void AQTEEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (state_manager) {
		startEvent();
	}
}
void AQTEEvent::setupKeys() {
	qte_keys.Reset();
	qte_keys.Add("w");
	qte_keys.Add("a");
	qte_keys.Add("s");
	qte_keys.Add("d");
}
bool AQTEEvent::getEventStarted()
{
	return is_event_started;
}

void AQTEEvent::startEvent()
{
	if (state_manager->getState() == StateType::Interaction) {
		is_event_started = true;
		eventLogic();
	}
	else {
		is_event_started = false;
	}
}

void AQTEEvent::eventLogic()
{
	if (!is_qte_event_started) {
		is_qte_event_started = true;
		current_round = 0;
		current_key = qte_keys[current_round];
		GetWorldTimerManager().SetTimer(current_key_timer_handle, this, &AQTEEvent::changeCurrentKey, round_duration, true, round_duration);
	}
}

void AQTEEvent::changeCurrentKey()
{
	if (current_key != key_from_event) {
		timerHasEnd();
	}

	current_round++;

	if (current_round < qte_keys.Num()) {
		current_key = qte_keys[current_round];
	}
	else {
		timerHasEnd();
	}
}

void AQTEEvent::skipCurrentTimer()
{
	GetWorldTimerManager().ClearTimer(current_key_timer_handle);
	GetWorldTimerManager().SetTimer(current_key_timer_handle, this, &AQTEEvent::changeCurrentKey, round_duration, true, 0.1);

	if (current_round + 1 >= max_rounds) {
		state_manager->setState(StateType::EndGame);
	}
}

FString AQTEEvent::getKey()
{
	return key_from_event;
}

void AQTEEvent::setKey(FString key)
{
	key_from_event = key;
}

void AQTEEvent::timerHasEnd()
{
	GetWorldTimerManager().ClearTimer(current_key_timer_handle);

	is_qte_event_started = false;
	current_round = 0;
	current_key = "";
	key_from_event = "";
	if (state_manager->getState() != StateType::EndGame) {
		state_manager->setState(StateType::Overlap);
	}
}