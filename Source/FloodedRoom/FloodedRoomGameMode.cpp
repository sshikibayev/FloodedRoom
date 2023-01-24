// Copyright Epic Games, Inc. All Rights Reserved.

#include "FloodedRoomGameMode.h"
#include "FloodedRoomCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFloodedRoomGameMode::AFloodedRoomGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
