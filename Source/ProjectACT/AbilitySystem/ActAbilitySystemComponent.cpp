#include "AbilitySystem/ActAbilitySystemComponent.h"
#include "AbilitySystem/ActGameplayAbility.h"

UActAbilitySystemComponent::UActAbilitySystemComponent()
{
}

void UActAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
	{
		bool HasTagExact = AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag);
		if (AbilitySpec.Ability && HasTagExact)
		{
			InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
			InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
		}
	}
}

void UActAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
	{
		bool HasTagExact = AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag);
		if (AbilitySpec.Ability && HasTagExact)
		{
			InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
			InputHeldSpecHandles.Remove(AbilitySpec.Handle);
		}
	}
}

void UActAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();

	for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
	{
		const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle);
		if (!AbilitySpec)
		{
			continue;
		}

		if ((AbilitySpec->Ability) && (!AbilitySpec->IsActive()))
		{
			const UActGameplayAbility* ActAbilityCDO = Cast<UActGameplayAbility>(AbilitySpec->Ability);
			if ((ActAbilityCDO) && (ActAbilityCDO->ActivationPolicy == EActAbilityActivationPolicy::Hold))
			{
				AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
	{
		FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle);
		if (!AbilitySpec)
		{
			continue;
		}

		if (AbilitySpec->Ability)
		{
			AbilitySpec->InputPressed = true;
			if (AbilitySpec->IsActive())
			{
				AbilitySpecInputPressed(*AbilitySpec);
			}
			else
			{
				const UActGameplayAbility* ActAbilityCDO = Cast<UActGameplayAbility>(AbilitySpec->Ability);
				if ((ActAbilityCDO) && (ActAbilityCDO->ActivationPolicy == EActAbilityActivationPolicy::Trigger))
				{
					AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
				}
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles)
	{
		FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle);
		if (!AbilitySpec)
		{
			continue;
		}

		if (AbilitySpec->Ability)
		{
			AbilitySpec->InputPressed = false;
			if (AbilitySpec->IsActive())
			{
				AbilitySpecInputReleased(*AbilitySpec);
			}
			else
			{
				const UActGameplayAbility* ActAbilityCDO = Cast<UActGameplayAbility>(AbilitySpec->Ability);
				if ((ActAbilityCDO) && (ActAbilityCDO->ActivationPolicy == EActAbilityActivationPolicy::Release))
				{
					AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
				}
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate)
	{
		TryActivateAbility(AbilitySpecHandle);
	}

	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void UActAbilitySystemComponent::ClearAbilityInput()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}
