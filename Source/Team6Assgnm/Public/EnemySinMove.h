// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "EnemySinMove.generated.h"

/**
 * 
 */
UCLASS()
class TEAM6ASSGNM_API AEnemySinMove : public ABaseEnemy
{
	GENERATED_BODY()
public:
	AEnemySinMove();

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float amplitude_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float frequence_;

protected:
	float accum_time_;
	float last_time_;
	virtual void BeginPlay() override;
	virtual void Move(float time) override;
	virtual void Tick(float DeltaTime) override;
	
};
