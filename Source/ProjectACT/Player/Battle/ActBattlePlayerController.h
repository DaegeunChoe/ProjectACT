#pragma once

#include "Player/ActPlayerController.h"
#include "ActBattlePlayerController.generated.h"

class UActAbilitySystemComponent;

UCLASS()
class PROJECTACT_API AActBattlePlayerController : public AActPlayerController
{
	GENERATED_BODY()

public:
	AActBattlePlayerController();

	UActAbilitySystemComponent* GetActAbilitySystemComponent() const;

	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
};
