#pragma once

#include "Player/ActPlayerState.h"
#include "AbilitySystemInterface.h"
#include "ActBattlePlayerState.generated.h"

class UAbilitySystemComponent;
class UActAbilitySystemComponent;

UCLASS()
class PROJECTACT_API AActBattlePlayerState : public AActPlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AActBattlePlayerState();

	UActAbilitySystemComponent* GetActAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Act|Component")
	TObjectPtr<UActAbilitySystemComponent> AbilitySystemComponent;
};
