// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManCharacter.h"
#include "Components/InputComponent.h"
#include "PacManGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

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
	this->GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
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

	PlayerInputComponent->BindAction("Restart", IE_Released, this, &APacManCharacter::_Restart);
	PlayerInputComponent->BindAction("Pause", IE_Released, this, &APacManCharacter::_Pause);
	PlayerInputComponent->BindAction("NewGame", IE_Released, this, &APacManCharacter::_NewGame);
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

void APacManCharacter::_Restart()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
	UE_LOG(LogTemp, Warning, TEXT("Restart Click"));
}

void APacManCharacter::_Pause()
{
	EGameState state = this->GameMode->GetCurrentState();
	if (state == EGameState::EPlaying)
	{
		this->GameMode->SetCurrentState(EGameState::EPause);
	}
	else if (state == EGameState::EPause)
	{
		this->GameMode->SetCurrentState(EGameState::EPlaying);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Pause Click"));
}

void APacManCharacter::_NewGame()
{
	if (this->GameMode->GetCurrentState() == EGameState::EMenu)
	{
		this->GameMode->SetCurrentState(EGameState::EPlaying);
	}
	UE_LOG(LogTemp, Warning, TEXT("NewGame Click"));
}

