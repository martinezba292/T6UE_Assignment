// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "EnemyMove.generated.h"

/**
 * 
 */
UCLASS()
class TEAM6ASSGNM_API AEnemyMove : public ABaseEnemy
{
	GENERATED_BODY()
	
public:
	AEnemyMove();

protected:
	virtual void BeginPlay() override;
	virtual void Move(float time) override;

public:
	virtual void Tick(float DeltaTime) override;
};
