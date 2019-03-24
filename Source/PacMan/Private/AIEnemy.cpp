// Fill out your copyright notice in the Description page of Project Settings.

#include "AIEnemy.h"
#include "Enemy.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "Engine/Public/TimerManager.h"
#include "PacManGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PacManGameModeBase.h"

void AAIEnemy::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	Bot = Cast<AEnemy>(InPawn);

	// 获取初始位置
	HomeLocation = Bot->GetActorLocation();

	// 获取当前GameMode
	this->GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));

	SearchNewPoint();
}

void AAIEnemy::OnMoveCompleted(FAIRequestID RequstId, const FPathFollowingResult & Result)
{
	if (!Bot->bIsDied && this->GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		SearchNewPoint();
	}
}

void AAIEnemy::SearchNewPoint()
{
	UNavigationSystemV1* Navigation = UNavigationSystemV1::GetCurrent(this);
	
	if (Navigation)
	{
		const float SearchRedius = 10000.0f;
		FNavLocation RandomPt;
		const bool bFound = Navigation->GetRandomReachablePointInRadius(Bot->GetActorLocation(), SearchRedius, RandomPt);
		if (bFound)
		{
			MoveToLocation(RandomPt);
		}
	}
}

void AAIEnemy::GoHome()
{
	MoveToLocation(HomeLocation);
	GetWorldTimerManager().SetTimer(DeadTime, this, &AAIEnemy::ReArm, 10.0f, false);
}

void AAIEnemy::ReArm()
{
	GetWorldTimerManager().ClearTimer(DeadTime);
	Bot->ReArm();
}

void AAIEnemy::StopMove()
{
	StopMovement();
	// 强制暂停
	//this->MoveToLocation(this->Bot->GetActorLocation());
}