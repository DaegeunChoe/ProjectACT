#pragma once

#include "AbilitySystem/ActGameplayAbility.h"
#include "NativeGameplayTags.h"
#include "Ability_DodgeRoll.generated.h"

namespace ActInputTag
{
	PROJECTACT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_DodgdRoll);
}

namespace ActAbilityTag
{
	PROJECTACT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_DodgeRoll);
}

UCLASS()
class PROJECTACT_API UAbility_DodgeRoll : public UActGameplayAbility
{
	GENERATED_BODY()

};
