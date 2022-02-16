// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class TEAM6ASSGNM_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEnemy();

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* enemy_root_;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* enemy_body_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	  int32 max_life_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 speed_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 score_;

	UFUNCTION()
		virtual bool HurtEnemy(int damage);

	virtual void Move(float time);

	int32 GetCurrentLife() const;

	void DestroyEnemy();
	void ActivateEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 current_life_;
	APawn* player_;
};
