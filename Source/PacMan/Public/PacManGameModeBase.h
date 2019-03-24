// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PacManGameModeBase.generated.h"

/**
 * 游戏规则定义
 */

enum class EGameState: short
{
	EMenu,
	EPlaying,
	EPause,
	EWin,
	EGameOver
};


UCLASS()
class PACMAN_API APacManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	EGameState GetCurrentState() const;
	void SetCurrentState(EGameState);
private:
	EGameState GameState;
};

FORCEINLINE EGameState APacManGameModeBase::GetCurrentState() const
{
	return this->GameState;
}
