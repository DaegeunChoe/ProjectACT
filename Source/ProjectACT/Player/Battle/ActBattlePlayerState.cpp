#include "Player/Battle/ActBattlePlayerState.h"
#include "AbilitySystem/ActAbilitySystemComponent.h"

AActBattlePlayerState::AActBattlePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UActAbilitySystemComponent>(TEXT("ActAbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// AbilitySystemComponent needs to be updated at a high frequency.
	SetNetUpdateFrequency(100.0f);
}

UActAbilitySystemComponent* AActBattlePlayerState::GetActAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAbilitySystemComponent* AActBattlePlayerState::GetAbilitySystemComponent() const
{
	return GetActAbilitySystemComponent();
}
