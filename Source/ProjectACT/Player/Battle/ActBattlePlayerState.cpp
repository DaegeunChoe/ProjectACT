#include "Player/Battle/ActBattlePlayerState.h"
#include "AbilitySystem/ActAbilitySystemComponent.h"
#include "AbilitySystem/ActAbilitySet.h"
#include "Character/ActCharacter.h"
#include "Character/ActPawnData.h"

AActBattlePlayerState::AActBattlePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UActAbilitySystemComponent>(TEXT("ActAbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// AbilitySystemComponent needs to be updated at a high frequency.
	SetNetUpdateFrequency(100.0f);
}

void AActBattlePlayerState::BeginPlay()
{
	if (!OnPawnSet.IsAlreadyBound(this, &ThisClass::OnPawnReady))
	{
		OnPawnSet.AddDynamic(this, &ThisClass::OnPawnReady);
	}
}

void AActBattlePlayerState::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	if (OnPawnSet.IsAlreadyBound(this, &ThisClass::OnPawnReady))
	{
		OnPawnSet.RemoveDynamic(this, &ThisClass::OnPawnReady);
	}
}

UActAbilitySystemComponent* AActBattlePlayerState::GetActAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAbilitySystemComponent* AActBattlePlayerState::GetAbilitySystemComponent() const
{
	return GetActAbilitySystemComponent();
}

void AActBattlePlayerState::OnPawnReady(APlayerState* Player, APawn* NewPawn, APawn* OldPawn)
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	AActCharacter* Character = GetPawn<AActCharacter>();
	if (!IsValid(Character))
	{
		return;
	}

	const UActPawnData* PawnData = Character->GetPawnData();
	if (!IsValid(PawnData))
	{
		return;
	}
	CachedPawnData = PawnData;

	GrantedHandles.TakeFromAbilitySystem(AbilitySystemComponent);

	AbilitySystemComponent->InitAbilityActorInfo(this, Character);

	for (const UActAbilitySet* AbilitySet : PawnData->AbilitySets)
	{
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, &GrantedHandles, this);
		}
	}
}
