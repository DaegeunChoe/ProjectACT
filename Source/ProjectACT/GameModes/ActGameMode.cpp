#include "GameModes/ActGameMode.h"
#include "GameModes/ActGameState.h"
#include "Player/ActPlayerController.h"
#include "Player/ActPlayerState.h"
#include "Character/ActCharacter.h"

AActGameMode::AActGameMode()
{
	// fallback class
	GameStateClass = AActGameState::StaticClass();
	DefaultPawnClass = AActCharacter::StaticClass();
	PlayerControllerClass = AActPlayerController::StaticClass();
	PlayerStateClass = AActPlayerState::StaticClass();
}
