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

	// �����������
	//UPROPERTY(����Ȩ��, Category=���)
	UPROPERTY(VisibleAnywhere, Category=Body)
	UStaticMeshComponent* EnemyBody;

	void SetEtable();
	void SetUneatable();

	// �����ƶ�
	void SetMove(bool);
	// �����ص�
	void Killed();
	// ��ʼ״̬
	void ReArm();

	// ��ײ����
	UFUNCTION()
	void OnCollision(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool bIsDied = false;
private:
	UPROPERTY(EditAnywhere, Category = Body)
	UMaterialInterface* DefaultMaterial;
	UPROPERTY(VisibleAnywhere, Category = Body)
	UMaterialInterface* EatableMaterial;

	// ��ʱ������
	FTimerHandle TimeEatable;

	// ��ǰ״̬
	bool bIsEatable = false;
	// ����״̬
	
};
