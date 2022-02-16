// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Team6AssgnmGameModeBase.generated.h"

class ABaseTurret;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatePlayerScoreSignature, uint32, newValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdatePlayerInfoSignature);

enum TurretType {
	kTurretType_Weapon = 0,
	kTurretType_Quick = 1,
	kTurretType_Multi = 2,
	kTurretType_MAX = 3
};

/**
 * 
 */
UCLASS()
class TEAM6ASSGNM_API ATeam6AssgnmGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATeam6AssgnmGameModeBase();

	//UI score update
	void AddScore(uint32 value);

	//Events for UI update. Binded on CustomHUD
	FUpdatePlayerScoreSignature OnScoreUpdate;
	FUpdatePlayerInfoSignature OnWeaponChange;

	//Storage for turrets instances
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		TArray<TSubclassOf<ABaseTurret>> turret_templates_;

	TArray<ABaseTurret*> turret_instances_;
	void ChangeWeapon();


private:
	virtual void BeginPlay() override;
	virtual void StartPlay() override;
	int8 weapon_type_;
	uint32 player_score_;
};
