// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManCharacter.h"
#include "Components/InputComponent.h"
#include "PacManGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Public/Collectables.h"
#include "Components/CapsuleComponent.h"
#include "Public/EngineUtils.h"

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

	//����ײ�¼�
	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnCollision);

	//������������������
	for (TActorIterator<ACollectables> collIter(GetWorld()); collIter; ++collIter)
	{
		CollectablesToEat++;
	}
	UE_LOG(LogTemp, Warning, TEXT("Total CollectablesToEat:%d"), CollectablesToEat);
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

	// ���ƶ��¼�
	PlayerInputComponent->BindAxis("MoveX", this, &APacManCharacter::MoveXAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &APacManCharacter::MoveYAxis);

	// �󶨰����¼�
	PlayerInputComponent->BindAction("Restart", IE_Released, this, &APacManCharacter::_Restart);
	PlayerInputComponent->BindAction("Pause", IE_Released, this, &APacManCharacter::_Pause);
	PlayerInputComponent->BindAction("NewGame", IE_Released, this, &APacManCharacter::_NewGame);
}


void APacManCharacter::MoveXAxis(float AxisValue)
{
	current.X = AxisValue;
	// ʵ�ʿ����ƶ��ĺ���
	AddMovementInput(current);
}

void APacManCharacter::MoveYAxis(float AxisValue)
{
	current.Y = AxisValue;
	AddMovementInput(current);
}

void APacManCharacter::OnCollision(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		// �����ײ����ʳ��
		if (OtherActor->IsA(ACollectables::StaticClass()))
		{
			OtherActor->Destroy();
			CollectablesToEat--;
			if (CollectablesToEat == 0)
			{
				GameMode->SetCurrentState(EGameState::EWin);
			}
			UE_LOG(LogTemp, Warning, TEXT("Remain:%d"), CollectablesToEat);
		}
	}
	
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

