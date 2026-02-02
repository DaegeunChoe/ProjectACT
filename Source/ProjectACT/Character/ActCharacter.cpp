#include "Character/ActCharacter.h"

AActCharacter::AActCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AActCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AActCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
