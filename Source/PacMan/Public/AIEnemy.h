// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemy.generated.h"

class AEnemy;
/**
 * 
 */
UCLASS()
class PACMAN_API AAIEnemy : public AAIController
{
	GENERATED_BODY()
	
public:
	// AI����ʱ�ĳ�ʼ��
	void Possess(APawn *) override;
	// �ƶ�ֹͣ��Ĵ���
	virtual void OnMoveCompleted(FAIRequestID , const FPathFollowingResult& ) override;

	void SearchNewPoint();

	void GoHome();

	void ReArm();

	void StopMove();
private:
	AEnemy* Bot;

	FVector HomeLocation;

	FTimerHandle DeadTime;
};
