#include "AbilitySystem/ActAbilitySet.h"
#include "AbilitySystem/ActAbilitySystemComponent.h"
#include "AbilitySystem/ActGameplayAbility.h"
#include "AbilitySystem/ActGameplayEffect.h"
#include "AttributeSet.h"
#include "ActLogChannel.h"

void FActAbilitySet_GrantedHandles::AddGameplayAbilityHandle(const FGameplayAbilitySpecHandle& InHandle)
{
	if (InHandle.IsValid())
	{
		AbilitySpecHandles.Add(InHandle);
	}
}

void FActAbilitySet_GrantedHandles::AddGameplayEffectHandle(const FActiveGameplayEffectHandle& InHandle)
{
	if (InHandle.IsValid())
	{
		GameplayEffectHandles.Add(InHandle);
	}
}

void FActAbilitySet_GrantedHandles::AddAttributeSet(UAttributeSet* InSet)
{
	if (InSet)
	{
		GrantedAttributeSets.Add(InSet);
	}
}

void FActAbilitySet_GrantedHandles::TakeFromAbilitySystem(UActAbilitySystemComponent* ActASC)
{
	check(ActASC);

	if (!ActASC->IsOwnerActorAuthoritative())
	{
		ACT_LOG(LogAct, Warning, TEXT("ActASC is NOT Authoritative"));
		return;
	}

	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			ActASC->ClearAbility(Handle);
		}
	}

	for (const FActiveGameplayEffectHandle& Handle : GameplayEffectHandles)
	{
		if (Handle.IsValid())
		{
			ActASC->RemoveActiveGameplayEffect(Handle);
		}
	}

	for (UAttributeSet* Set : GrantedAttributeSets)
	{
		if (Set)
		{
			ActASC->RemoveSpawnedAttribute(Set);
		}
	}

	AbilitySpecHandles.Reset();
	GameplayEffectHandles.Reset();
	GrantedAttributeSets.Reset();
}

UActAbilitySet::UActAbilitySet()
{
}

void UActAbilitySet::GrantAttributeSet(UActAbilitySystemComponent* ActASC, FActAbilitySet_GrantedHandles* OutGrantedHandles) const
{
	for (const FActAbilitySet_AttributeSet& Item : GrantedAttributeSets)
	{
		if (!IsValid(Item.AttributeSet))
		{
			ACT_LOG(LogAct, Warning, TEXT("Item.AttributeSet is INVALID"));
			continue;
		}

		UAttributeSet* NewSet = NewObject<UAttributeSet>(ActASC->GetOwner(), Item.AttributeSet);
		if (!NewSet)
		{
			ACT_LOG(LogAct, Warning, TEXT("NewSet is nullptr"));
			continue;
		}

		ActASC->AddAttributeSetSubobject(NewSet);

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAttributeSet(NewSet);
		}
	}
}

void UActAbilitySet::GrantGameplayEffect(UActAbilitySystemComponent* ActASC, FActAbilitySet_GrantedHandles* OutGrantedHandles) const
{
	for (const FActAbilitySet_GameplayEffect& Item : GrantedGameplayEffects)
	{
		if (!IsValid(Item.GameplayEffect))
		{
			ACT_LOG(LogAct, Warning, TEXT("Item.GameplayEffect is INVALID"));
			continue;
		}

		UActGameplayEffect* EffectCDO = Item.GameplayEffect->GetDefaultObject<UActGameplayEffect>();
		if (!EffectCDO)
		{
			ACT_LOG(LogAct, Warning, TEXT("EffectCDO is nullptr"));
			continue;
		}
		
		FActiveGameplayEffectHandle GameplayEffectHandle = ActASC->ApplyGameplayEffectToSelf(EffectCDO, Item.EffectLevel, ActASC->MakeEffectContext());

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddGameplayEffectHandle(GameplayEffectHandle);
		}
	}
}

void UActAbilitySet::GrantAbility(UActAbilitySystemComponent* ActASC, FActAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const
{
	for (const FActAbilitySet_GameplayAbility& Item : GrantedGameplayAbilities)
	{
		if (!IsValid(Item.Ability))
		{
			ACT_LOG(LogAct, Warning, TEXT("Item.Ability is INVALID"));
			continue;
		}

		UActGameplayAbility* AbilityCDO = Item.Ability->GetDefaultObject<UActGameplayAbility>();
		if (!AbilityCDO)
		{
			ACT_LOG(LogAct, Warning, TEXT("AbilityCDO is nullptr"));
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilityCDO, Item.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(Item.InputTag);

		FGameplayAbilitySpecHandle AbilitySpecHandle = ActASC->GiveAbility(AbilitySpec);

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddGameplayAbilityHandle(AbilitySpecHandle);
		}
	}
}

void UActAbilitySet::GiveToAbilitySystem(UActAbilitySystemComponent* ActASC, FActAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const
{
	check(ActASC);

	if (!ActASC->IsOwnerActorAuthoritative())
	{
		ACT_LOG(LogAct, Warning, TEXT("ActASC is NOT Authoritative"));
		return;
	}

	GrantAttributeSet(ActASC, OutGrantedHandles);
	GrantAbility(ActASC, OutGrantedHandles, SourceObject);
	GrantGameplayEffect(ActASC, OutGrantedHandles);
}
