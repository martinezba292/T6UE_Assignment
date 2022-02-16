// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Team6AssgnmGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseTurret::ABaseTurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	root_ = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = root_;

	turret_base_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	turret_base_->SetupAttachment(RootComponent);

	turret_rotator_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Middle"));
	turret_rotator_->SetupAttachment(RootComponent);

	cannon_root_ = CreateDefaultSubobject<USceneComponent>(TEXT("CannonRoot"));
	cannon_root_->SetupAttachment(turret_rotator_);
	turret_cannon_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon"));
	turret_cannon_->SetupAttachment(cannon_root_);

	camera_boom_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	camera_boom_->SetupAttachment(cannon_root_);
	camera_boom_->bAbsoluteRotation = false; // Rotation of the character should not affect rotation of boom
	camera_boom_->bDoCollisionTest = false;
	camera_boom_->TargetArmLength = 200.f;
	camera_boom_->SocketOffset = FVector(0.f, 0.f, 75.f);
	camera_boom_->RelativeRotation = FRotator(0.f, 90.f, 0.f);

	player_camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	player_camera_->SetupAttachment(camera_boom_, USpringArmComponent::SocketName);
	player_camera_->bUsePawnControlRotation = false;

	sensibility_ = 0.0f;
}

void ABaseTurret::RecoverBullet()
{
	++current_bullets_;
	if (enable_)
	  OnAmmoUpdate.Broadcast(current_bullets_);
}

void ABaseTurret::SpendBullet()
{
	--current_bullets_;
	OnAmmoUpdate.Broadcast(current_bullets_);
}

void ABaseTurret::Shoot()
{
}

void ABaseTurret::HideTurret()
{
	root_->SetSimulatePhysics(false);
	root_->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorHiddenInGame(true);
	enable_ = false;
}

void ABaseTurret::PossesTurret()
{
	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	root_->SetSimulatePhysics(true);
	root_->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetActorHiddenInGame(false);
	pc->Possess(this);
	enable_ = true;
}

// Called when the game starts or when spawned
void ABaseTurret::BeginPlay()
{
	Super::BeginPlay();
	current_bullets_ = 0;
	enable_ = false;
	turret_rotator_->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	central_yaw_ = turret_rotator_->GetComponentRotation().Yaw;
	central_roll_ = cannon_root_->GetComponentRotation().Roll;
}

void ABaseTurret::HorizontalRotation(float Val) {

	FRotator current = turret_rotator_->GetComponentRotation();
	float rot_range = central_yaw_ - current.Yaw;
	int r = Val < 0.0f && rot_range < hmax_angle_;
	r |= Val > 0.0f && rot_range > -hmax_angle_;
	
	FRotator new_rot = FRotator(0.0f, r * Val * sensibility_, 0.0f);
	turret_rotator_->AddLocalRotation(new_rot);
}

void ABaseTurret::VerticalRotation(float Val)
{
	FRotator current = cannon_root_->GetComponentRotation();
	float rot_range = central_roll_ - current.Roll;
	int r = Val < 0.0f && rot_range < vmax_angle_;
	r |= Val > 0.0f && rot_range > -vmax_angle_;

	FRotator new_rot = FRotator(0.0f, 0.0f, r * Val * sensibility_);
	cannon_root_->AddLocalRotation(new_rot);
}


// Called to bind functionality to input
void ABaseTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &ABaseTurret::HorizontalRotation);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseTurret::VerticalRotation);
	ATeam6AssgnmGameModeBase* gm = Cast<ATeam6AssgnmGameModeBase>(GetWorld()->GetAuthGameMode());
	PlayerInputComponent->BindAction("ChangeWeapon", IE_Pressed, gm, &ATeam6AssgnmGameModeBase::ChangeWeapon);
}

