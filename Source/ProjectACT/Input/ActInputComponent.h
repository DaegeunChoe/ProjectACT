#pragma once

#include "EnhancedInputComponent.h"
#include "Input/ActInputConfig.h"
#include "ActLogChannel.h"
#include "ActInputComponent.generated.h"

class UInputAction;

UCLASS(Config = Input)
class PROJECTACT_API UActInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UActInputComponent();

	template<class UserClass, typename FuncType>
	void BindNativeAction(const UActInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);

	template<class UserClass, typename FuncType>
	void BindAbilityActions(const UActInputConfig* InputConfig, UserClass* Object, FuncType PressedFunc, FuncType ReleasedFunc, TArray<uint32>* BindHandles = nullptr);
};

template<class UserClass, typename FuncType>
inline void UActInputComponent::BindNativeAction(const UActInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig);

	const UInputAction* InputAction = InputConfig->FindNativeInputActionForTag(InputTag);
	if (!InputAction)
	{
		ACT_LOG(LogAct, Warning, TEXT("InputAction is nullptr"));
		return;
	}

	BindAction(InputAction, TriggerEvent, Object, Func);
}

template<class UserClass, typename FuncType>
inline void UActInputComponent::BindAbilityActions(const UActInputConfig* InputConfig, UserClass* Object, FuncType PressedFunc, FuncType ReleasedFunc, TArray<uint32>* BindHandles)
{
	check(InputConfig);

	for (const FActInputAction& Pair : InputConfig->AbilityInputActions)
	{
		if ((Pair.InputAction) && (Pair.InputTag.IsValid()))
		{
			if (PressedFunc)
			{
				int32 BindHandle = BindAction(Pair.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, Pair.InputTag).GetHandle();
				if (BindHandles)
				{
					BindHandles->Add(BindHandle);
				}
			}
			if (ReleasedFunc)
			{
				int32 BindHandle = BindAction(Pair.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Pair.InputTag).GetHandle();
				if (BindHandles)
				{
					BindHandles->Add(BindHandle);
				}
			}
		}
		else
		{
			ACT_LOG(LogAct, Warning, TEXT("Pair.InputAction is nullptr OR Pair.InputTag is INVALID."));
		}
	}
}
