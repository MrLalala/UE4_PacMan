// Fill out your copyright notice in the Description page of Project Settings.

#include "AIEnemy.h"
#include "Enemy.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "Engine/Public/TimerManager.h"
//#include "Public/NavigationSystem.h"

void AAIEnemy::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	Bot = Cast<AEnemy>(InPawn);

	// ��ȡ��ʼλ��
	HomeLocation = Bot->GetActorLocation();

	SearchNewPoint();
}

void AAIEnemy::OnMoveCompleted(FAIRequestID RequstId, const FPathFollowingResult & Result)
{
	if (!Bot->bIsDied)
	{
		SearchNewPoint();
	}
}

void AAIEnemy::SearchNewPoint()
{
	UNavigationSystemV1* Navigation = UNavigationSystemV1::GetCurrent(this);
	
	if (Navigation)
	{
		const float SearchRedius = 1000.0f;
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
}