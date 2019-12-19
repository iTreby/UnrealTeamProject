// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ComboGameState.generated.h"

UENUM(BlueprintType)
enum class EComboLevel : uint8
{
    D = 1 UMETA(DisplayName="D"),
    C = 2 UMETA(DisplayName="C"),
    B = 3 UMETA(DisplayName="B"),
    A = 4 UMETA(DisplayName="A"),
    S = 5 UMETA(DisplayName="S"),
    SS = 6 UMETA(DisplayName="SS"),
    SSS = 7 UMETA(DisplayName="SSS"),
};

/**
 * Class to handle Combo Meter feature
 */
UCLASS()
class GAMEENGINEPROJECT_API AComboGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
    AComboGameState();

    UPROPERTY(EditAnywhere)
    TSubclassOf<class UComboStatsWidget> ComboStatsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EComboLevel StyleLevel = EComboLevel::D;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float CurrentPoint = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int CurrentComboLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float BasePointsToAdd = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ComboBarDecreasingSpeed = 0.1f;

    // If Player reaches 100 points, proceed to next combo level
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float LevelPointThreshold = 100.0f;

    // Multiplier to determine how much points to decrease when projectile hit misses enemy
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MissDecreaseValue = 2;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ResetComboInterval = 30.0f;

private:
    // Maximum combo level player can reach
    UPROPERTY()
    int MaxComboLevel = 7;

    UPROPERTY()
    FTimerHandle ResetComboTimerHandle;


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    EComboLevel GetComboLevelEnumByIndex(int index);

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void IncreaseComboValue(float bodyPartMultiplier);

    void DecreaseComboValue(float DeltaTime);

    void DecreaseComboValue();

    void IncreaseLevel();

    void DecreaseLevel();

    void ResetCombo();

};
