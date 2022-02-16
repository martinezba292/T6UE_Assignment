// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomHUD.h"
#include "Kismet/GameplayStatics.h"
#include "CustomWidget.h"
#include "Team6AssgnmGameModeBase.h"
#include "Components/TextBlock.h"
#include "..\..\Public\UI\CustomHUD.h"
#include "WeaponTurret.h"


void ACustomHUD::BeginPlay() {
  Super::BeginPlay();

  APlayerController* APC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  UUserWidget* temp = CreateWidget(APC, widget_template_, FName("GameWidget"));
  custom_widget_ = Cast<UCustomWidget>(temp);

  ATeam6AssgnmGameModeBase* gm = Cast<ATeam6AssgnmGameModeBase>(GetWorld()->GetAuthGameMode());

  if (gm) {
    //GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Adding Event"));
    gm->OnScoreUpdate.AddDynamic(this, &ACustomHUD::UpdateScore);
    gm->OnScoreUpdate.Broadcast(0);
    gm->OnWeaponChange.AddDynamic(this, &ACustomHUD::UpdatePlayerInfo);
    for (auto turret : gm->turret_instances_) {
      turret->OnAmmoUpdate.AddDynamic(this, &ACustomHUD::UpdateAmmoUI);
    }
  }

  custom_widget_->AddToViewport(0);
}


void ACustomHUD::UpdateScore(uint32 value) {
  FString updated_score = FString::FromInt(value);
  custom_widget_->score_text_->SetText(FText::FromString(updated_score));
}

void ACustomHUD::UpdateAmmoUI(uint32 value)
{
  FString bullets = FString::FromInt(value);
  custom_widget_->turret_bullets_->SetText(FText::FromString(bullets));
}

void ACustomHUD::UpdatePlayerInfo()
{
  AWeaponTurret* player = Cast<AWeaponTurret>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
  if (!player) return;

  FString cadence = FString::SanitizeFloat(player->cadence_);
  cadence.Append(" seconds");
  FString bullets = FString::FromInt(player->current_bullets_);
  FString force = FString::SanitizeFloat(player->bullet_force_);
  FString damage = FString::FromInt(player->GetDamage());

  custom_widget_->turret_name_->SetText(FText::FromString(player->name_));
  custom_widget_->turret_cadence_->SetText(FText::FromString(cadence));
  custom_widget_->turret_bullets_->SetText(FText::FromString(bullets));
  custom_widget_->bullet_force_->SetText(FText::FromString(force));
  custom_widget_->bullet_damage_->SetText(FText::FromString(damage));
}


