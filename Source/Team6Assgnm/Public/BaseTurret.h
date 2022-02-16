// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseTurret.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateUISignature, uint32, newvalue);

UCLASS()
class TEAM6ASSGNM_API ABaseTurret : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseTurret();

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* player_camera_;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		USpringArmComponent* camera_boom_;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* root_;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* turret_base_;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* turret_rotator_;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* turret_cannon_;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USceneComponent* cannon_root_;
		
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float sensibility_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float hmax_angle_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float vmax_angle_;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		FString name_;

	//Number of available bullets for showing on UI
	int32 current_bullets_;

	//Bullet count methods
	//They are called each time a bullet is activated and hidden
	UFUNCTION()
	  void RecoverBullet();
	UFUNCTION()
		void SpendBullet();

	virtual void Shoot();

	virtual void HideTurret();

	virtual void PossesTurret();

	//Event for updating the bullets amount on UI, it is binded on CustomHUD
	FUpdateUISignature OnAmmoUpdate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Turret rotate input
	void HorizontalRotation(float Val);
	void VerticalRotation(float Val);

	//Turret is possesed by player controller
	bool enable_;
	
	float central_yaw_;
	float central_roll_;
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
