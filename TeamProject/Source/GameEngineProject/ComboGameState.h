// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ComboGameState.generated.h"

UENUM(BlueprintType)
enum class EComboLevel : uint8
{
    D = 1,
    C = 2,
    B = 3,
    A = 4,
    S = 5,
};


/**
 * Class to handle Combo Meter feature
 */
UCLASS()
class GAMEENGINEPROJECT_API AComboGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float CurrentPoint = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int CurrentComboLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float BasePointsToAdd = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ComboBarDecreasingSpeed = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ComboBarIncreasingValue;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool isDecreasingComboBar = true;

    // If Player reaches 100 points, proceed to next combo level
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float LevelPointThreshold = 100.0f;

    // Multiplier to determine how much points to decrease when projectile hit misses enemy
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MissDecreaseValue = 2;

private:
    UPROPERTY()
    // Maximum combo level player can reach (Denote: S)
    int MaxComboLevel = 5;

public:

    virtual void Tick(float DeltaTime) override;

    void IncreaseComboValue(float bodyPartMultiplier);

    void DecreaseComboValue(float DeltaTime);

    void DecreaseComboValue();

    void IncreaseLevel();

    void DecreaseLevel();

};
