// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponTurret.h"
#include "BasicBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"

AWeaponTurret::AWeaponTurret() 
{
  PrimaryActorTick.bCanEverTick = false;
  proyectile_root_ = CreateDefaultSubobject<USceneComponent>(TEXT("ProyectileSpawner"));
  proyectile_root_->SetupAttachment(turret_cannon_);
}

void AWeaponTurret::Shoot()
{
  auto ptr = ammo_.FindByPredicate([](const ABasicBullet* bullet) { return bullet->IsReady(); });
  if (!ptr) return;

  ABasicBullet* current_bullet = *ptr;
  current_bullet->SetActorLocation(proyectile_root_->GetComponentLocation());
  current_bullet->EnableBullet();
  FVector force = player_camera_->GetForwardVector() * bullet_force_ * current_bullet->root_->GetMass();
  current_bullet->root_->AddImpulse(force);
  current_bullet->StartDestroySequence();
}

int32 AWeaponTurret::GetDamage()
{
  if (ammo_.IsValidIndex(0))
    return ammo_[0]->damage_;

  return 0;
}

void AWeaponTurret::CreateBulletPool()
{
  ammo_.Reserve(pool_size_);
  for (size_t i = 0; i < pool_size_; i++) {
    ABasicBullet* b = GetWorld()->SpawnActor<ABasicBullet>(template_, FVector::ZeroVector, FRotator::ZeroRotator);
    b->SetTurretOwner(this);
    ammo_.Add(b);
    b->HideBullet();
  }
}

void AWeaponTurret::BeginPlay()
{
  Super::BeginPlay();
  CreateBulletPool();
}

void AWeaponTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  PlayerInputComponent->BindAction("ShootProyectile", IE_Pressed, this, &AWeaponTurret::Shoot);
  
}
