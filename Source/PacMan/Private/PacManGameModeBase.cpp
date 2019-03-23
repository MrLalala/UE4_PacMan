// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManGameModeBase.h"

void APacManGameModeBase::SetCurrentState(EGameState state)
{
	this->GameState = state;
}

void APacManGameModeBase::BeginPlay()
{
	this->SetCurrentState(EGameState::EPlaying);
}