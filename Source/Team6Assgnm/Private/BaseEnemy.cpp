// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	enemy_root_ = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = enemy_root_;

	enemy_body_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	enemy_body_->SetupAttachment(RootComponent);
}

void ABaseEnemy::DestroyEnemy() {
	current_life_ = 0;
	enemy_root_->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
}

void ABaseEnemy::ActivateEnemy() {
	current_life_ = max_life_;
	player_ = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	enemy_root_->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetActorTickEnabled(true);
	SetActorHiddenInGame(false);
}

bool ABaseEnemy::HurtEnemy(int damage)
{
	current_life_ -= damage;
	if (current_life_ <= 0) {
		DestroyEnemy();
		return true;
	}
	return false;
}

void ABaseEnemy::Move(float time)
{
}

int32 ABaseEnemy::GetCurrentLife() const
{
	return current_life_;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	ActivateEnemy();
}



// Called every frame
//void ABaseEnemy::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}

