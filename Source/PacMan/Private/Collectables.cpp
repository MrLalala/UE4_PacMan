// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Collectables.h"
#include "Public/UObject/ConstructorHelpers.h"

// Sets default values
ACollectables::ACollectables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// 初始化外观和碰撞
	// 通过CreateDefaultSubsobject创建对象
	pCollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pMesh"));
	pCollision = CreateDefaultSubobject<USphereComponent>(TEXT("pSphare"));

	// 开启碰撞
	SetActorEnableCollision(true);

	// 绑定外观和碰撞体积
	pCollectableMesh->AttachTo(pCollision);

	// 设置球体外形
	// TODO: 为什么这样用？通过反射找到对应的类
	static ConstructorHelpers::FObjectFinder<UStaticMesh> sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	// 如果找得到
	if (sphere.Succeeded())
	{
		// 外观绑定
		pCollectableMesh->SetStaticMesh(sphere.Object);
	}

	// 设置外观大小?
	pCollectableMesh->SetWorldScale3D(FVector(0.3, 0.3, 0.3));
	// 设置碰撞体大小
	pCollision->SetSphereRadius(16);
}

// Called when the game starts or when spawned
void ACollectables::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

