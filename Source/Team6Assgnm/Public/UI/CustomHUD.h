// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CustomHUD.generated.h"

class UCustomWidget;
/**
 * 
 */
UCLASS()
class TEAM6ASSGNM_API ACustomHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> widget_template_;

	UPROPERTY(BlueprintReadOnly, Category = "Widget")
		UCustomWidget* custom_widget_;

private:
	void BeginPlay() override;

	//Binding methods
	UFUNCTION()
		void UpdateAmmoUI(uint32 value);

	UFUNCTION()
	  void UpdateScore(uint32 value);

	UFUNCTION()
		void UpdatePlayerInfo();
};
