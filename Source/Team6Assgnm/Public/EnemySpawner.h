// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class ABaseEnemy;

enum EnemyType {
	kEnemeyType_Base = 0,
	kEnemyType_Sinus = 1,
	kEnemyType_MAX
};

UCLASS()
class TEAM6ASSGNM_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 enemy_pool_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float spawn_interval_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		TArray<TSubclassOf<ABaseEnemy>> enemy_templates_;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CreatePool();
	void Spawn();
	TArray<ABaseEnemy*> enemies_;

};
