// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTurret.h"
#include "WeaponTurret.generated.h"

/**
 * 
 */

class ABasicBullet;
UCLASS()
class TEAM6ASSGNM_API AWeaponTurret : public ABaseTurret
{
	GENERATED_BODY()
public:
	AWeaponTurret();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	  USceneComponent* proyectile_root_;

	UPROPERTY(EditAnywhere, Category = "ActorSpawn")
		TSubclassOf<ABasicBullet> template_;

	//Number of bullets spawned by this turret
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 pool_size_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float bullet_force_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float cadence_;

	virtual void Shoot() override;

	//Damage of current bullets for showing on UI
	int32 GetDamage();

protected:
	virtual void BeginPlay() override;

	//Ammunition storage
	TArray<ABasicBullet*> ammo_;

	//Instantiate bullets for the turret to use in BeginPlay
	void CreateBulletPool();

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
