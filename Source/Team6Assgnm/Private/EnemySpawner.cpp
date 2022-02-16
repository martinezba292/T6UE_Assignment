// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "EnemyMove.h"
#include "EnemySinMove.h"
#include <functional>

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	CreatePool();
	Spawn();
	FTimerHandle spawn_timer;
	GetWorld()->GetTimerManager().SetTimer(spawn_timer, this, &AEnemySpawner::Spawn, spawn_interval_, true);
}

void AEnemySpawner::CreatePool()
{
	auto lamb = [&]() {
		return GetWorld()->SpawnActor<AEnemyMove>(enemy_templates_[kEnemeyType_Base], 
																							FVector::ZeroVector, 
																							FRotator::ZeroRotator);
	};

	auto lamb2 = [&]() {
		return GetWorld()->SpawnActor<AEnemySinMove>(enemy_templates_[kEnemyType_Sinus], 
																								 FVector::ZeroVector, 
																								 FRotator::ZeroRotator);
	};

	std::function<ABaseEnemy* ()>spawner[kEnemyType_MAX] = { lamb, lamb2 };
	for (size_t i = 0; i < enemy_pool_; i++) {
		int32 enemy_type = FMath::RandRange(0, (kEnemyType_MAX-1));
		ABaseEnemy* e = spawner[enemy_type]();
		if (e) {
			enemies_.Add(e);
			e->DestroyEnemy();
		}
	}
}

void AEnemySpawner::Spawn()
{
	auto next_enemy = enemies_.FindByPredicate([](const ABaseEnemy* enemy) { return enemy->GetCurrentLife() <= 0; });
	if (!next_enemy) {
		return;
	}

	ABaseEnemy* e = *next_enemy;
	e->SetActorLocation(GetActorLocation());
	e->ActivateEnemy();
}

