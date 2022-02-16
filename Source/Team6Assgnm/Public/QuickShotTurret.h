// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponTurret.h"
#include "QuickShotTurret.generated.h"

/**
 * 
 */
UCLASS()
class TEAM6ASSGNM_API AQuickShotTurret : public AWeaponTurret
{
	GENERATED_BODY()

public:
	AQuickShotTurret();

protected:
	virtual void BeginPlay() override;
	virtual void Shoot() override;
	void EndBurst();
	FTimerHandle t_cadence_;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
};
