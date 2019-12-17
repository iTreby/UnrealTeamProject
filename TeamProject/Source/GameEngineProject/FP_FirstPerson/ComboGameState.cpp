// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboGameState.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "ComboStatsWidget.h"


void AComboGameState::BeginPlay()
{
    Super::BeginPlay();
    if (ComboStatsWidget != NULL) {
        auto widget = CreateWidget<UComboStatsWidget>(UGameplayStatics::GetPlayerController(this, 0), ComboStatsWidget);
        widget->comboGameState = this;
        widget->AddToViewport();
	}
}

EComboLevel AComboGameState::GetComboLevelEnumByIndex(int index) {
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EComboLevel"), true);
    if (!EnumPtr) return EComboLevel::D; // Return default
    return static_cast<EComboLevel>(EnumPtr->GetValueByIndex(index));
}

void AComboGameState::IncreaseComboValue(float bodyPartMultiplier) {
    CurrentPoint += BasePointsToAdd * bodyPartMultiplier;
    if (CurrentPoint >= LevelPointThreshold) {
        IncreaseLevel();
    }
}

// Increase combo level and reset current point
void AComboGameState::IncreaseLevel() {

    if (CurrentComboLevel < MaxComboLevel) {
        // Reassign StyleLevel to next level.
        // Since CurrentComboLevel starts at 1, we return the current and not the incremented value
        StyleLevel = GetComboLevelEnumByIndex(CurrentComboLevel);
        CurrentComboLevel++;
        CurrentPoint -= LevelPointThreshold;
    } else {
        CurrentPoint = LevelPointThreshold;
    }
}

// Decrease points over time
void AComboGameState::DecreaseComboValue(float DeltaTime) {
    CurrentPoint = FMath::Clamp(CurrentPoint - DeltaTime * ComboBarDecreasingSpeed, 0.0f, 100.0f);
//    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("DecreaseComboValue::CurrentPoint %f"), CurrentPoint));
    if (CurrentPoint == 0) {
        DecreaseLevel();
    }
}

// Decrease points when miss
void AComboGameState::DecreaseComboValue() {
    CurrentPoint -= MissDecreaseValue;
    if (CurrentPoint <= 0) {
        DecreaseLevel();
    }
}

void AComboGameState::DecreaseLevel() {
    if (CurrentComboLevel > 1) {
        CurrentComboLevel--;
        StyleLevel = GetComboLevelEnumByIndex(CurrentComboLevel);
        CurrentPoint = LevelPointThreshold;
    } else {
        CurrentPoint = 0;
    }
}



