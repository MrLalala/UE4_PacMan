// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class PACMAN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 敌人外形组件
	//UPROPERTY(访问权限, Category=类别)
	UPROPERTY(VisibleAnywhere, Category=Body)
	UStaticMeshComponent* EnemyBody;

	void SetEtable();
	void SetUneatable();

private:
	UPROPERTY(EditAnywhere, Category = Body)
	UMaterialInterface* DefaultMaterial;
	UPROPERTY(VisibleAnywhere, Category = Body)
	UMaterialInterface* EatableMaterial;

	// 定时器任务
	FTimerHandle TimeEatable;

	// 当前状态
	bool bIsEatable = false;
};
