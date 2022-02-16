// Fill out your copyright notice in the Description page of Project Settings.


#include "Team6AssgnmGameModeBase.h"
#include "BaseTurret.h"


ATeam6AssgnmGameModeBase::ATeam6AssgnmGameModeBase() {

}

void ATeam6AssgnmGameModeBase::AddScore(uint32 value) {
  player_score_ += value;
  OnScoreUpdate.Broadcast(player_score_);
}

void ATeam6AssgnmGameModeBase::ChangeWeapon()
{
  turret_instances_[weapon_type_]->HideTurret();
  ++weapon_type_ %= kTurretType_MAX;
  turret_instances_[weapon_type_]->PossesTurret();
  OnWeaponChange.Broadcast();
}

void ATeam6AssgnmGameModeBase::BeginPlay()
{
  player_score_ = 0;
  weapon_type_ = 0;
  turret_instances_.Reserve(turret_templates_.Num());
  float offset = 100.0f;
  for (auto turret : turret_templates_) {
    auto t = GetWorld()->SpawnActor<ABaseTurret>(turret, FVector(0.0f, 0.0f, 130.0f), FRotator::ZeroRotator);
    if (t) {
      turret_instances_.Add(t);
      t->HideTurret();
    }
  }
}

void ATeam6AssgnmGameModeBase::StartPlay()
{
  Super::StartPlay();
  turret_instances_[weapon_type_]->PossesTurret();
  OnWeaponChange.Broadcast();
}



