#include "Character/ActCharacterInputComponent.h"
#include "Character/ActCharacter.h"
#include "Character/ActPawnData.h"
#include "Input/ActInputConfig.h"
#include "Input/ActInputComponent.h"
#include "Player/ActPlayerController.h"
#include "AbilitySystem/ActAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "ActLogChannel.h"

namespace ActInputTag
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Move, "InputTag.Move", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Look_Mouse, "InputTag.Look.Mouse", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Look_Stick, "InputTag.Look.Stick", "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_DirectionFix, "InputTag.DirectionFix", "");
}

UActCharacterInputComponent::UActCharacterInputComponent()
{
}

void UActCharacterInputComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const AActCharacter* Owner = GetOwner<AActCharacter>();
	if (!IsValid(Owner))
	{
		ACT_LOG(LogAct, Warning, TEXT("Owner is INVALID"));
		return;
	}

	const APlayerController* PlayerController = Owner->GetController<APlayerController>();
	if (!IsValid(PlayerController))
	{
		ACT_LOG(LogAct, Warning, TEXT("PlayerController is INVALID"));
		return;
	}

	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->GetLocalPlayer());
	if (!IsValid(LocalPlayer))
	{
		ACT_LOG(LogAct, Warning, TEXT("LocalPlayer is INVALID"));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!IsValid(Subsystem))
	{
		ACT_LOG(LogAct, Warning, TEXT("Subsystem is INVALID"));
		return;
	}

	const UActPawnData* PawnData = Owner->GetPawnData();
	if (!IsValid(PawnData))
	{
		ACT_LOG(LogAct, Warning, TEXT("PawnData is INVALID"));
		return;
	}

	const UActInputConfig* InputConfig = PawnData->InputConfig;
	if (!IsValid(InputConfig))
	{
		ACT_LOG(LogAct, Warning, TEXT("PawnData->InputConfig is INVALID"));
		return;
	}

	UInputMappingContext* InputMappingContext = DefaultInputMapping;
	if (!IsValid(InputMappingContext))
	{
		ACT_LOG(LogAct, Warning, TEXT("DefaultInputMapping is INVALID"));
		return;
	}

	int32 DefaultMappingPriority = 0;
	Subsystem->AddMappingContext(InputMappingContext, DefaultMappingPriority);

	UActInputComponent* ActInputComponent = Cast<UActInputComponent>(PlayerInputComponent);
	if (!IsValid(ActInputComponent))
	{
		ACT_LOG(LogAct, Warning, TEXT("ActInputComponent is INVALID"));
		return;
	}

	ActInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityAction_Pressed, &ThisClass::Input_AbilityAction_Released);

	ActInputComponent->BindNativeAction(InputConfig, ActInputTag::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_NativeAction_Move);
	ActInputComponent->BindNativeAction(InputConfig, ActInputTag::InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_NativeAction_Look_Mouse);
	ActInputComponent->BindNativeAction(InputConfig, ActInputTag::InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ThisClass::Input_NativeAction_Look_Stick);
}

void UActCharacterInputComponent::Input_AbilityAction_Pressed(FGameplayTag InputTag)
{
	AActCharacter* Owner = GetOwner<AActCharacter>();
	if (!IsValid(Owner))
	{
		ACT_LOG(LogAct, Warning, TEXT("Owner is INVALID"));
		return;
	}

	UActAbilitySystemComponent* ActASC = Owner->GetActAbilitySystemComponent();
	if (!IsValid(ActASC))
	{
		ACT_LOG(LogAct, Warning, TEXT("ActASC is INVALID"));
		return;
	}

	ActASC->AbilityInputTagPressed(InputTag);
}

void UActCharacterInputComponent::Input_AbilityAction_Released(FGameplayTag InputTag)
{
	AActCharacter* Owner = GetOwner<AActCharacter>();
	if (!IsValid(Owner))
	{
		ACT_LOG(LogAct, Warning, TEXT("Owner is INVALID"));
		return;
	}

	UActAbilitySystemComponent* ActASC = Owner->GetActAbilitySystemComponent();
	if (!IsValid(ActASC))
	{
		ACT_LOG(LogAct, Warning, TEXT("ActASC is INVALID"));
		return;
	}

	ActASC->AbilityInputTagReleased(InputTag);
}

void UActCharacterInputComponent::Input_NativeAction_Move(const FInputActionValue& InputActionValue)
{
	AActCharacter* Owner = GetOwner<AActCharacter>();
	if (!IsValid(Owner))
	{
		ACT_LOG(LogAct, Warning, TEXT("Owner is INVALID"));
		return;
	}

	const AController* Controller = Owner->GetController<AController>();
	if (!IsValid(Controller))
	{
		ACT_LOG(LogAct, Warning, TEXT("Controller is INVALID"));
		return;
	}

	const FVector2D Value = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

	if (Value.X != 0.0f)
	{
		const FVector ForwardVector = MovementRotation.RotateVector(FVector::ForwardVector);
		Owner->AddMovementInput(ForwardVector, Value.X);
	}

	if (Value.Y != 0.0f)
	{
		const FVector RightVector = MovementRotation.RotateVector(FVector::RightVector);
		Owner->AddMovementInput(RightVector, Value.Y);
	}
}

void UActCharacterInputComponent::Input_NativeAction_Look_Mouse(const FInputActionValue& InputActionValue)
{
	AActCharacter* Owner = GetOwner<AActCharacter>();
	if (!IsValid(Owner))
	{
		ACT_LOG(LogAct, Warning, TEXT("Owner is INVALID"));
		return;
	}

	const AController* Controller = Owner->GetController<AController>();
	if (!IsValid(Controller))
	{
		ACT_LOG(LogAct, Warning, TEXT("Controller is INVALID"));
		return;
	}

	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		Owner->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		Owner->AddControllerPitchInput(Value.Y);
	}
}

void UActCharacterInputComponent::Input_NativeAction_Look_Stick(const FInputActionValue& InputActionValue)
{
	// TODO
}
