// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Collectables.generated.h"

UCLASS()
class PACMAN_API ACollectables : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectables();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// 通过指定UPROPERTY宏来添加可编辑属性。
	// EditDefaultsOnly: 只能对原型进行修改
	// 网格组件, 指定物体的形状
	UPROPERTY(VisibleAnywhere, Category = Collectable)
	UStaticMeshComponent* pCollectableMesh;
	// 碰撞体组件, 碰撞事件
	UPROPERTY(EditDefaultsOnly, Category = Collectable)
	USphereComponent* pCollision;

	// 超级食物标识
	// EditAnywhere：对原型和实例修改
	UPROPERTY(EditAnyWhere, Category = Collectable)
	bool bIsSuper = false;

};
