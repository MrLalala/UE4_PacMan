// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemy.generated.h"

class AEnemy;
class APacManGameModeBase;
/**
 * 
 */
UCLASS()
class PACMAN_API AAIEnemy : public AAIController
{
	GENERATED_BODY()
	
public:
	// AI开启时的初始化
	void Possess(APawn *) override;
	// 移动停止后的处理
	virtual void OnMoveCompleted(FAIRequestID , const FPathFollowingResult& ) override;

	void SearchNewPoint();

	void GoHome();

	void ReArm();

	void StopMove();
private:
	AEnemy* Bot;

	FVector HomeLocation;

	FTimerHandle DeadTime;

	APacManGameModeBase* GameMode;
};
