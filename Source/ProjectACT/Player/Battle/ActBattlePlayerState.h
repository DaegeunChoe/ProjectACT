#pragma once

#include "Player/ActPlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/ActAbilitySet.h"
#include "ActBattlePlayerState.generated.h"

class UAbilitySystemComponent;
class UActAbilitySystemComponent;
class UActPawnData;

UCLASS()
class PROJECTACT_API AActBattlePlayerState : public AActPlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AActBattlePlayerState();

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	UActAbilitySystemComponent* GetActAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UFUNCTION()
	void OnPawnReady(APlayerState* Player, APawn* NewPawn, APawn* OldPawn);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Act|Component")
	TObjectPtr<UActAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	FActAbilitySet_GrantedHandles GrantedHandles;

private:
	UPROPERTY()
	TObjectPtr<const UActPawnData> CachedPawnData = nullptr;
};
