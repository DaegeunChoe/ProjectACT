#pragma once

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ActInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FActInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

UCLASS()
class PROJECTACT_API UActInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UActInputConfig();

	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag) const;
	const UInputAction* FindAbilityActionForTag(const FGameplayTag& InputTag) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FActInputAction> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FActInputAction> AbilityInputActions;
};
