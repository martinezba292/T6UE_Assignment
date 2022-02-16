// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMove.h"

AEnemyMove::AEnemyMove() {
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemyMove::BeginPlay() {
	Super::BeginPlay();
}

void AEnemyMove::Move(float time) {
	FVector origin = GetActorLocation();
	FVector destination = player_->GetActorLocation();

	FVector direction = (destination - origin);
	direction.Normalize();

	origin += direction * speed_ * time;
	SetActorLocation(origin);
}

void AEnemyMove::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}