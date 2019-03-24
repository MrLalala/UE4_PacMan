// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManHUD.h"
#include "PacManGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "PacManCharacter.h"

void APacManHUD::DrawHUD()
{
	// 获取当前游戏状态
	APacManGameModeBase* GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
	
	EGameState State = GameMode->GetCurrentState();
	switch (State)
	{
	case EGameState::EMenu:
		this->DrawText(TEXT("Welcome To PacMan!\n\nPress N To Start Game\nPress P Pause Game"), FColor::White, Canvas->SizeX / 2 - 150, Canvas->SizeY / 2 - 150, Font);
		break;
	case EGameState::EPlaying:
		{
			APacManCharacter* PacMan = Cast<APacManCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
			if (PacMan)
			{
				FString LiveString = TEXT("Lives:") + FString::FromInt(PacMan->Lives);
				DrawText(LiveString, FColor::Green, 50, 50, Font);
				FString CollectablesToEat = TEXT("CollectablesToEat:") + FString::FromInt(PacMan->CollectablesToEat);
				DrawText(CollectablesToEat, FColor::Green, Canvas->SizeX - 150, Canvas->SizeY - 150, Font);
			}
		}
		break;
	case EGameState::EPause:
		this->DrawText(TEXT("Press P Continue Game"), FColor::White, Canvas->SizeX / 2 - 150, Canvas->SizeY / 2 - 150, Font);
		break;
	case EGameState::EWin:
		this->DrawText(TEXT("You Win!\n\nPress R Restart Game"), FColor::White, Canvas->SizeX / 2 - 150, Canvas->SizeY / 2 - 150, Font);
		break;
	case EGameState::EGameOver:
		this->DrawText(TEXT("Game Over!\n\nPress R Restart Game"), FColor::White, Canvas->SizeX / 2 - 150, Canvas->SizeY / 2 - 150, Font);
		break;
	default:
		break;
	}
}
