#pragma once

#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ActCharacter.generated.h"

class UActPawnData;
class UActCharacterInputComponent;
class UActAbilitySystemComponent;
class UAbilitySystemComponent;

UCLASS()
class PROJECTACT_API AActCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AActCharacter();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	const UActPawnData* GetPawnData() const { return PawnData; }

	UActAbilitySystemComponent* GetActAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Act")
	TObjectPtr<UActPawnData> PawnData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Act|Component")
	TObjectPtr<UActCharacterInputComponent> CharacterInputComponent;
};
