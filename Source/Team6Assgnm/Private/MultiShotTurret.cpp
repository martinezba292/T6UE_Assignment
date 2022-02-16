// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiShotTurret.h"
#include "BasicBullet.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include <algorithm>

AMultiShotTurret::AMultiShotTurret() {
  PrimaryActorTick.bCanEverTick = false;
}

void AMultiShotTurret::BeginPlay()
{
  Super::BeginPlay();
}

void AMultiShotTurret::Shoot()
{
  TArray<ABasicBullet*> current_bullets;
  current_bullets.Reserve(burst_bullets_);

  //Take bullets for burst
  for (size_t i = 0; i < burst_bullets_; i++) {
    auto ptr = ammo_.FindByPredicate([](const ABasicBullet* bullet) { return bullet->IsReady(); });
    if (!ptr) {
      for (auto bullet : current_bullets) 
        bullet->ReleaseBullet();
      return;
    }
    ABasicBullet* bullet = *ptr;
    current_bullets.Add(bullet);
    bullet->TakeBullet();
  }

  //Half angle from camera forward vector
  float angle = 40.0f;
  float f_burst_bullets = static_cast<float>(burst_bullets_);

  //Sectors of the angle that the burst will cover
  float sections = (2.0f * angle) / f_burst_bullets;

  //Rotate the forward vector of the camera as many sectors as half of the burst bullet number
  FVector final_dir = player_camera_->GetForwardVector().RotateAngleAxis(-sections * (burst_bullets_ >> 1), FVector::UpVector);

  //Here we simply repeat shooting operations of set location, enable and add impulse
  for (size_t i = 0; i < burst_bullets_; i++) {
    current_bullets[i]->SetActorLocation(proyectile_root_->GetComponentLocation());
    current_bullets[i]->EnableBullet();
    FVector force = final_dir * bullet_force_ * current_bullets[i]->root_->GetMass() ;
    current_bullets[i]->root_->AddImpulse(force);
    current_bullets[i]->StartDestroySequence();
    //Rotate direction for next bullet of the burst
    final_dir = final_dir.RotateAngleAxis(sections, FVector::UpVector);
  }
}

void AMultiShotTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  ABaseTurret::SetupPlayerInputComponent(PlayerInputComponent);
  PlayerInputComponent->BindAction("ShootProyectile", IE_Pressed, this, &AMultiShotTurret::Shoot);
}
