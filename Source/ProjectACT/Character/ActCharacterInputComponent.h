#pragma once

#include "Components/ActorComponent.h"
#include "NativeGameplayTags.h"
#include "ActCharacterInputComponent.generated.h"

class UInputComponent;
class UInputMappingContext;
struct FInputActionValue;

namespace ActInputTag
{
	PROJECTACT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	PROJECTACT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Mouse);
	PROJECTACT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Stick);
}

UCLASS()
class PROJECTACT_API UActCharacterInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActCharacterInputComponent();

	void InitializePlayerInput(UInputComponent* PlayerInputComponent);

protected:

	void Input_AbilityAction_Pressed(FGameplayTag InputTag);
	void Input_AbilityAction_Released(FGameplayTag InputTag);

	void Input_NativeAction_Move(const FInputActionValue& InputActionValue);
	void Input_NativeAction_Look_Mouse(const FInputActionValue& InputActionValue);
	void Input_NativeAction_Look_Stick(const FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly, Category = "Act")
	TObjectPtr<UInputMappingContext> DefaultInputMapping;
};
