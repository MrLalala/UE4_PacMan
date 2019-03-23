// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Collectables.h"
#include "Public/UObject/ConstructorHelpers.h"

// Sets default values
ACollectables::ACollectables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// ��ʼ����ۺ���ײ
	// ͨ��CreateDefaultSubsobject��������
	pCollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pMesh"));
	pCollision = CreateDefaultSubobject<USphereComponent>(TEXT("pSphare"));

	// ������ײ
	SetActorEnableCollision(true);

	// ����ۺ���ײ���
	pCollectableMesh->AttachTo(pCollision);

	// ������������
	// TODO: Ϊʲô�����ã�ͨ�������ҵ���Ӧ����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	// ����ҵõ�
	if (sphere.Succeeded())
	{
		// ��۰�
		pCollectableMesh->SetStaticMesh(sphere.Object);
	}

	// ������۴�С?
	pCollectableMesh->SetWorldScale3D(FVector(0.3, 0.3, 0.3));
	// ������ײ���С
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

