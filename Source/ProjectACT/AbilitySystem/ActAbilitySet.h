#pragma once

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "ActAbilitySet.generated.h"

class UActAbilitySystemComponent;
class UActGameplayAbility;
class UActGameplayEffect;
class UAttributeSet;

USTRUCT(BlueprintType)
struct FActAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UActGameplayAbility> Ability = nullptr;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FActAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UActGameplayEffect> GameplayEffect = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};

USTRUCT(BlueprintType)
struct FActAbilitySet_AttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeSet> AttributeSet;
};

USTRUCT(BlueprintType)
struct FActAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:
	void AddGameplayAbilityHandle(const FGameplayAbilitySpecHandle& InHandle);
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& InHandle);
	void AddAttributeSet(UAttributeSet* InSet);

	void TakeFromAbilitySystem(UActAbilitySystemComponent* ActASC);

protected:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;
};

UCLASS()
class PROJECTACT_API UActAbilitySet : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UActAbilitySet();

	void GrantAttributeSet(UActAbilitySystemComponent* ActASC, FActAbilitySet_GrantedHandles* OutGrantedHandles) const;
	void GrantGameplayEffect(UActAbilitySystemComponent* ActASC, FActAbilitySet_GrantedHandles* OutGrantedHandles) const;
	void GrantAbility(UActAbilitySystemComponent* ActASC, FActAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const;

	void GiveToAbilitySystem(UActAbilitySystemComponent* ActASC, FActAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;

protected:
	UPROPERTY(EditDefaultsOnly, Meta = (TitleProperty = Ability))
	TArray<FActAbilitySet_GameplayAbility> GrantedGameplayAbilities;

	UPROPERTY(EditDefaultsOnly, Meta = (TitleProperty = Ability))
	TArray<FActAbilitySet_GameplayEffect> GrantedGameplayEffects;

	UPROPERTY(EditDefaultsOnly, Meta = (TitleProperty = Ability))
	TArray<FActAbilitySet_AttributeSet> GrantedAttributeSets;
};
