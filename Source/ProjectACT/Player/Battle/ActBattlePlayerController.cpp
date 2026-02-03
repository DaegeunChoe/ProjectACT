#include "Player/Battle/ActBattlePlayerController.h"
#include "Player/Battle/ActBattlePlayerState.h"
#include "AbilitySystem/ActAbilitySystemComponent.h"

AActBattlePlayerController::AActBattlePlayerController()
{
}

UActAbilitySystemComponent* AActBattlePlayerController::GetActAbilitySystemComponent() const
{
	AActBattlePlayerState* BattlePlayerState = GetPlayerState<AActBattlePlayerState>();
	if (IsValid(BattlePlayerState))
	{
		return BattlePlayerState->GetActAbilitySystemComponent();
	}
	else
	{
		return nullptr;
	}
}

void AActBattlePlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (UActAbilitySystemComponent* ActASC = GetActAbilitySystemComponent())
	{
		ActASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}
