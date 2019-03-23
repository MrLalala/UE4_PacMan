// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PacManCharacter.generated.h"

class APacManGameModeBase;

UCLASS()
class PACMAN_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// �����¼�����
	void _Restart();
	void _Pause();
	void _NewGame();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// ��ӳ�亯��
	void MoveXAxis(float);
	void MoveYAxis(float);

private:
	// ��ǰ�ٶ�
	FVector current;
	APacManGameModeBase* GameMode;
};
