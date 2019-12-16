// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboGameState.h"
#include "Engine.h"

void AComboGameState::IncreaseComboValue(float bodyPartMultiplier) {
    CurrentPoint += BasePointsToAdd * bodyPartMultiplier;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("IncreaseComboValue::CurrentPoint %f"), CurrentPoint));
    if (CurrentPoint >= LevelPointThreshold) {
        IncreaseLevel();
    }
}

// Increase combo level and reset current point
void AComboGameState::IncreaseLevel() {
    if (CurrentComboLevel < MaxComboLevel) {
        CurrentComboLevel++;
        CurrentPoint -= LevelPointThreshold;
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("AComboGameState::IncreaseLevel::CurrentPoint %f"), CurrentPoint));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("AComboGameState::IncreaseLevel::CurrentComboLevel %d"), CurrentComboLevel));
    } else {
        CurrentPoint = LevelPointThreshold;
    }
}

void AComboGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Tick::CurrentPoint %f"), CurrentPoint));
    DecreaseComboValue(DeltaTime);
}

// Decrease points over time
void AComboGameState::DecreaseComboValue(float DeltaTime) {
    CurrentPoint -= FMath::Clamp(CurrentPoint - DeltaTime * ComboBarDecreasingSpeed, 100.0f, 0.0f);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("DecreaseComboValue::CurrentPoint %f"), CurrentPoint));
    if (CurrentPoint == 0) {
        DecreaseLevel();
    }
}

// Decrease points when miss
void AComboGameState::DecreaseComboValue() {
    CurrentPoint -= MissDecreaseValue;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("DecreaseComboValue::CurrentPoint %f"), CurrentPoint));
    if (CurrentPoint <= 0) {
        DecreaseLevel();
    }
}

void AComboGameState::DecreaseLevel() {
    if (CurrentComboLevel > 1) {
        CurrentComboLevel--;
        CurrentPoint = LevelPointThreshold;
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("AComboGameState::DecreaseLevel::CurrentPoint %f"), CurrentPoint));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("AComboGameState::DecreaseLevel::CurrentComboLevel %d"), CurrentComboLevel));
    } else {
        CurrentPoint = 0;
    }
}



