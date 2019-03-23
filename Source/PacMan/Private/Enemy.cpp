// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Classes/Engine/StaticMesh.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建一个组件
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	// 创建样子
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NarrowCapsuleObject(TEXT("'/Game/StarterContent/Shapes/Shape_NarrowCapsule'"));

	if (NarrowCapsuleObject.Succeeded())
	{
		EnemyBody->SetStaticMesh(NarrowCapsuleObject.Object);
	}
	// 设置大小
	EnemyBody->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	EnemyBody->SetAllPhysicsPosition(FVector(0, 0, -50.0f));
	// 绑定到碰撞部件上
	EnemyBody->SetupAttachment(RootComponent);

	GetCapsuleComponent()->SetCapsuleRadius(25.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

