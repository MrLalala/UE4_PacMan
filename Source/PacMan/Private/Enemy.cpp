// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "PacManCharacter.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Classes/Engine/StaticMesh.h"
#include "Classes/Materials/Material.h"
#include "Engine/Public/TimerManager.h"
#include "Classes/GameFramework/CharacterMovementComponent.h"
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
	// 调整物体相对位置
	EnemyBody->SetRelativeLocation(FVector(0, 0, -50.0f));
	// 绑定到碰撞部件上
	EnemyBody->SetupAttachment(RootComponent);

	GetCapsuleComponent()->SetCapsuleRadius(25.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);


	// 找到自定义的材质
	static ConstructorHelpers::FObjectFinder<UMaterial> M_Etable(TEXT("'/Game/Materials/M_Enemy_Eatable'"));
	if (M_Etable.Succeeded())
	{
		EatableMaterial = M_Etable.Object;
	}
}

void AEnemy::SetEtable()
{
	GetWorldTimerManager().SetTimer(TimeEatable, this, &AEnemy::SetUneatable, 10.0f, false);
	if (bIsEatable)
	{
		return;
	}
	bIsEatable = true;
	EnemyBody->SetMaterial(0, EatableMaterial);

	// 设置最大移动速度
	GetCharacterMovement()->MaxWalkSpeed = 50.0f;

}

void AEnemy::SetUneatable()
{
	if (!bIsEatable)
	{
		return;
	}
	bIsEatable = false;
	EnemyBody->SetMaterial(0, DefaultMaterial);
	GetWorldTimerManager().ClearTimer(TimeEatable);

	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	// 获取当前材质:Index->0
	DefaultMaterial = EnemyBody->GetMaterial(0);
	
	//SetEtable();
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

void AEnemy::SetMove(bool bMoveIt)
{

}

void AEnemy::Killed()
{
	if (bIsDied)
	{
		return;
	}
	bIsDied = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void AEnemy::ReArm()
{
	if (!bIsDied)
	{
		return;
	}
	bIsDied = false;
	SetUneatable();
}

void AEnemy::OnCollision(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(APacManCharacter::StaticClass()))
	{
		if (bIsEatable)
		{
			Killed();
		}
		else
		{
			APacManCharacter* PacMan = Cast<APacManCharacter>(OtherActor);
			PacMan->Killed();
		}
	}
}
