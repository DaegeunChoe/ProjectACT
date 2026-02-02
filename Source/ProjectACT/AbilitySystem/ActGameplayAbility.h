#pragma once

#include "Abilities/GameplayAbility.h"
#include "ActGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EActAbilityActivationPolicy : uint8
{
	Trigger,
	Release,
	Hold,
	Spawn
};

UCLASS()
class PROJECTACT_API UActGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	friend class UActAbilitySystemComponent;
	
public:
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Act")
	EActAbilityActivationPolicy ActivationPolicy;
};
