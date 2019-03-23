// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManCharacter.h"
#include "Components/InputComponent.h"

// Sets default values
APacManCharacter::APacManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APacManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &APacManCharacter::MoveXAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &APacManCharacter::MoveYAxis);

}


void APacManCharacter::MoveXAxis(float AxisValue)
{
	current.X = AxisValue;
	// 实际控制移动的函数
	AddMovementInput(current);
}

void APacManCharacter::MoveYAxis(float AxisValue)
{
	current.Y = AxisValue;
	AddMovementInput(current);
}

