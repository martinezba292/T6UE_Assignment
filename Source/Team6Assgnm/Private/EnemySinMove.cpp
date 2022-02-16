// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySinMove.h"

AEnemySinMove::AEnemySinMove() {
  PrimaryActorTick.bCanEverTick = true;
}


void AEnemySinMove::BeginPlay() {
  Super::BeginPlay();
  accum_time_ = 0.0f;
  last_time_ = accum_time_;
}

void AEnemySinMove::Move(float time)
{
  FVector destination = GetActorLocation();
  accum_time_ += time;
  float alpha_time = FMath::Sin(accum_time_ * frequence_);
  destination.X += (20.0f * (alpha_time - last_time_)) * amplitude_;
  last_time_ = alpha_time;
  FVector direction = player_->GetActorLocation() - GetActorLocation();
  direction.Normalize();
  destination += (direction * speed_ * time);
  SetActorLocation(destination);
}

void AEnemySinMove::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  Move(DeltaTime);
}
