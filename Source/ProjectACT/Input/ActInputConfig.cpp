#include "Input/ActInputConfig.h"

UActInputConfig::UActInputConfig()
{
}

const UInputAction* UActInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FActInputAction& Pair : NativeInputActions)
	{
		if ((Pair.InputAction) && (Pair.InputTag == InputTag))
		{
			return Pair.InputAction;
		}
	}
	return nullptr;
}

const UInputAction* UActInputConfig::FindAbilityActionForTag(const FGameplayTag& InputTag) const
{
	for (const FActInputAction& Pair : AbilityInputActions)
	{
		if ((Pair.InputAction) && (Pair.InputTag == InputTag))
		{
			return Pair.InputAction;
		}
	}
	return nullptr;
}
