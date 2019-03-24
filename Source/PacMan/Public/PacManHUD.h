// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PacManHUD.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API APacManHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// 属性, 任意处可编辑, 蓝图可读写, 属于HUDFont目录下
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=HUDFont)
	UFont* Font;

	virtual void DrawHUD() override;
};
