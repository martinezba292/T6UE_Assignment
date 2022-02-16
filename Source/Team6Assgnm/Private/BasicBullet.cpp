// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "BaseEnemy.h"
#include "Team6AssgnmGameModeBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "WeaponTurret.h"

// Sets default values
ABasicBullet::ABasicBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	root_ = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionRoot"));
	RootComponent = root_;

	body_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	body_->SetupAttachment(RootComponent);

	explosion_ = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DestroyFeedback"));
	explosion_->SetupAttachment(RootComponent);
}

void ABasicBullet::OverlapBegin(UPrimitiveComponent* OverlappedComponent, 
																AActor* OtherActor, 
																UPrimitiveComponent* OtherComp, 
																int32 OtherBodyIndex, 
																bool bFromSweep, 
																const FHitResult& SweepResult)
{
	ABaseEnemy* enemy = Cast<ABaseEnemy>(OtherActor);
	if (!enemy) {
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(destroy_timer_);
	DestroySequence();
	if (enemy->HurtEnemy(damage_)) {
		ATeam6AssgnmGameModeBase* gm = Cast<ATeam6AssgnmGameModeBase>(GetWorld()->GetAuthGameMode());
		gm->AddScore(enemy->score_);
	}
}

void ABasicBullet::TakeBullet()
{
	ready_ = false;
}

void ABasicBullet::ReleaseBullet()
{
	ready_ = true;
}

bool ABasicBullet::IsReady() const
{
	return ready_;
}

void ABasicBullet::DestroySequence()
{
	explosion_->ActivateSystem();
	body_->SetVisibility(false);
	root_->SetSimulatePhysics(false);
	root_->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FTimerHandle anim_timer;
	GetWorld()->GetTimerManager().SetTimer(anim_timer, this, &ABasicBullet::HideBullet, 1.f, false);
}

void ABasicBullet::HideBullet()
{
	root_->SetSimulatePhysics(false);
	root_->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	explosion_->DeactivateSystem();
	SetActorHiddenInGame(true);
	OnHideBullet.Broadcast();
	ready_ = true;
}

void ABasicBullet::SetTurretOwner(AWeaponTurret* turret)
{
	OnHideBullet.AddDynamic(turret, &ABaseTurret::RecoverBullet);
	OnEnableBullet.AddDynamic(turret, &ABaseTurret::SpendBullet);
}

void ABasicBullet::EnableBullet()
{
	body_->SetVisibility(true);
	root_->SetSimulatePhysics(true);
	root_->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetActorHiddenInGame(false);
	OnEnableBullet.Broadcast();
	ready_ = false;
	explosion_->DeactivateSystem();
}

void ABasicBullet::StartDestroySequence()
{
	GetWorld()->GetTimerManager().SetTimer(destroy_timer_, this, &ABasicBullet::DestroySequence, bullet_lifetime_, false);
}

// Called when the game starts or when spawned
void ABasicBullet::BeginPlay()
{
	Super::BeginPlay();
	root_->OnComponentBeginOverlap.AddDynamic(this, &ABasicBullet::OverlapBegin);
}

