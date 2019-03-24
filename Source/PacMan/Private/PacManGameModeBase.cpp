// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManGameModeBase.h"
#include "Public/EngineUtils.h"
#include "Enemy.h"

void APacManGameModeBase::SetCurrentState(EGameState state)
{
	this->GameState = state;

	switch (state)
	{
	case EGameState::EMenu:
		break;
	case EGameState::EPlaying:
		for (auto iter = Enemys.CreateIterator(); iter; ++iter)
		{
			(*iter)->SetMove(true);
		}
		break;
	case EGameState::EPause:
		for (auto iter = Enemys.CreateIterator(); iter; ++iter)
		{
			(*iter)->SetMove(false);
		}
		break;
	case EGameState::EWin:
		for (auto iter = Enemys.CreateIterator(); iter; ++iter)
		{
			(*iter)->Destroy(true);
		}
		break;
	case EGameState::EGameOver:
		for (auto iter = Enemys.CreateIterator(); iter; ++iter)
		{
			(*iter)->Destroy(true);
		}
		break;
	default:
		break;
	}
}

void APacManGameModeBase::BeginPlay()
{
	this->SetCurrentState(EGameState::EMenu);

	// 迭代器添加
	for (TActorIterator<AEnemy> EnemyIter(GetWorld()); EnemyIter; ++EnemyIter)
	{
		AEnemy* enemy = Cast<AEnemy>(*EnemyIter);
		if (enemy)
		{
			Enemys.Add(enemy);
		}
	}
}

void APacManGameModeBase::SetEnemyCanEatable()
{
	for (auto iter = Enemys.CreateIterator(); iter; ++iter)
	{
		(*iter)->SetEtable();
	}
}