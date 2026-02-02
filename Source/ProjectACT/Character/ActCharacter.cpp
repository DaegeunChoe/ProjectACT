#include "Character/ActCharacter.h"
#include "Character/ActCharacterInputComponent.h"
#include "AbilitySystem/ActAbilitySystemComponent.h"
#include "Player/Battle/ActBattlePlayerState.h"

AActCharacter::AActCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	CharacterInputComponent = CreateDefaultSubobject<UActCharacterInputComponent>(TEXT("CharacterInputComponent"));
}

void AActCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AActCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (CharacterInputComponent)
	{
		CharacterInputComponent->InitializePlayerInput(PlayerInputComponent);
	}
}

UActAbilitySystemComponent* AActCharacter::GetActAbilitySystemComponent()
{
	if (!IsValid(CachedAbilitySystemComponent))
	{
		CachedAbilitySystemComponent = nullptr;
		AActBattlePlayerState* BattlePlayerState = GetPlayerState<AActBattlePlayerState>();
		if (IsValid(BattlePlayerState))
		{
			CachedAbilitySystemComponent = BattlePlayerState->GetActAbilitySystemComponent();
			return CachedAbilitySystemComponent;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return CachedAbilitySystemComponent;
	}
}

UAbilitySystemComponent* AActCharacter::GetAbilitySystemComponent()
{
	return GetActAbilitySystemComponent();
}

