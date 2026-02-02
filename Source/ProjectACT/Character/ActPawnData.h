#pragma once

#include "Engine/DataAsset.h"
#include "ActPawnData.generated.h"

class UActAbilitySet;
class UActInputConfig;

UCLASS(BlueprintType, Const)
class PROJECTACT_API UActPawnData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UActPawnData();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Act")
	TArray<TObjectPtr<UActAbilitySet>> AbilitySets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Act")
	TObjectPtr<UActInputConfig> InputConfig;
};
