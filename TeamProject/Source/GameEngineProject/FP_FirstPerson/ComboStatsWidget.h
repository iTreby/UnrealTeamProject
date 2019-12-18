// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ComboGameState.h"
#include "ComboStatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEENGINEPROJECT_API UComboStatsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AComboGameState* comboGameState;


public:
    UFUNCTION(BlueprintCallable)
    float GetComboValueInPercent();

    UFUNCTION(BlueprintCallable)
    FText GetComboLevelDisplay();
};
