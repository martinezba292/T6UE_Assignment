// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicBullet.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UparticleSystemComponent;
class AWeaponTurret;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateBulletStorageSignature);

UCLASS()
class TEAM6ASSGNM_API ABasicBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasicBullet();

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* root_;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* body_;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* explosion_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 damage_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float bullet_lifetime_;

	//Set bullet as taken for not be picked for shooting
	void TakeBullet();

	void ReleaseBullet();

	//Bullet is ready to be shooted
	bool IsReady() const;

	//Prepares bullet for shooting
	void EnableBullet();

	//Starts timer of bullet lifetime
	void StartDestroySequence();

	//Hide bullet and deactivate physics and collision
	void HideBullet();

	//Bind events (FUpdateBulletStorageSignature) of bullet count
	void SetTurretOwner(AWeaponTurret* turret);

protected:
	//Called when collision is detected
	void DestroySequence();
	FUpdateBulletStorageSignature OnHideBullet;
	FUpdateBulletStorageSignature OnEnableBullet;


	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent,
											AActor* OtherActor, 
											UPrimitiveComponent* OtherComp,
											int32 OtherBodyIndex, 
											bool bFromSweep, 
											const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool ready_;
	FTimerHandle destroy_timer_;

};
