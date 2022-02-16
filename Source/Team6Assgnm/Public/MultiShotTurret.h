// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponTurret.h"
#include "MultiShotTurret.generated.h"

/**
 * 
 */
UCLASS()
class TEAM6ASSGNM_API AMultiShotTurret : public AWeaponTurret
{
	GENERATED_BODY()

public:
	AMultiShotTurret();
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 burst_bullets_;

protected:
	virtual void BeginPlay() override;
	virtual void Shoot() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
