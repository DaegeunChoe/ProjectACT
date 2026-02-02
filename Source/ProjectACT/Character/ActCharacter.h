#pragma once

#include "GameFramework/Character.h"
#include "ActCharacter.generated.h"

UCLASS()
class PROJECTACT_API AActCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AActCharacter();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
