#include "Player/Battle/ActBattlePlayerState.h"
#include "AbilitySystem/ActAbilitySystemComponent.h"
#include "AbilitySystem/ActAbilitySet.h"
#include "Character/ActCharacter.h"
#include "Character/ActPawnData.h"
#include "ActLogChannel.h"

AActBattlePlayerState::AActBattlePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UActAbilitySystemComponent>(TEXT("ActAbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// AbilitySystemComponent needs to be updated at a high frequency.
	SetNetUpdateFrequency(100.0f);

	if (!OnPawnSet.IsAlreadyBound(this, &ThisClass::OnPawnReady))
	{
		OnPawnSet.AddDynamic(this, &ThisClass::OnPawnReady);
	}
}

void AActBattlePlayerState::BeginPlay()
{
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
		ACT_LOG(LogAct, Warning, TEXT("AbilitySystemComponent is nullptr"));
		return;
	}

	AActCharacter* Character = GetPawn<AActCharacter>();
	if (!IsValid(Character))
	{
		ACT_LOG(LogAct, Warning, TEXT("Character is INVALID"));
		return;
	}

	const UActPawnData* PawnData = Character->GetPawnData();
	if (!IsValid(PawnData))
	{
		ACT_LOG(LogAct, Warning, TEXT("PawnData is INVALID"));
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
