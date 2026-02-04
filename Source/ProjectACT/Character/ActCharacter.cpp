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

UActAbilitySystemComponent* AActCharacter::GetActAbilitySystemComponent() const
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

UAbilitySystemComponent* AActCharacter::GetAbilitySystemComponent() const
{
	return GetActAbilitySystemComponent();
}

