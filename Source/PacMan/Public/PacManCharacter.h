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

	// 按键事件函数
	void _Restart();
	void _Pause();
	void _NewGame();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// 轴映射函数
	void MoveXAxis(float);
	void MoveYAxis(float);

	// 碰撞函数
	/*
		UPrimitiveComponent:
		AActor:碰撞的类
		UPrimitiveComponent:
		int:
		bool: 是不是扫荡(一般用不到)
		FHitResult: 扫荡的结果(一般用不到)
	*/
	UFUNCTION()
	void OnCollision(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 死亡处理
	void Killed();

private:
	// 当前速度
	FVector current;
	APacManGameModeBase* GameMode;

	// 剩余食物数
	int CollectablesToEat = 0;
	// 生命值
	int Lives;
	// 出生点
	FVector StartPos;
};
