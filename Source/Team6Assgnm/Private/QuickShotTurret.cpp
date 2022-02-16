// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickShotTurret.h"

AQuickShotTurret::AQuickShotTurret() {
  PrimaryActorTick.bCanEverTick = false;
}

void AQuickShotTurret::BeginPlay()
{
  Super::BeginPlay();
}

void AQuickShotTurret::Shoot()
{
  Super::Shoot();
  GetWorld()->GetTimerManager().SetTimer(t_cadence_, this, &Super::Shoot, cadence_, true);
}

void AQuickShotTurret::EndBurst()
{
  GetWorld()->GetTimerManager().ClearTimer(t_cadence_);
}

void AQuickShotTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  ABaseTurret::SetupPlayerInputComponent(PlayerInputComponent);
  PlayerInputComponent->BindAction("ShootProyectile", IE_Pressed, this, &AQuickShotTurret::Shoot);
  PlayerInputComponent->BindAction("ShootProyectile", IE_Released, this, &AQuickShotTurret::EndBurst);
}


