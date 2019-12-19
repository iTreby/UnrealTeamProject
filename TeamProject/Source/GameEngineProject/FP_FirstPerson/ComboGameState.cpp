// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboGameState.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "ComboStatsWidget.h"

AComboGameState::AComboGameState() {
    PrimaryActorTick.bCanEverTick = true;
}

void AComboGameState::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(ResetComboTimerHandle, this, &AComboGameState::ResetCombo, ResetComboInterval, true);

    if (ComboStatsWidget != NULL) {
        auto widget = CreateWidget<UComboStatsWidget>(UGameplayStatics::GetPlayerController(this, 0), ComboStatsWidget);
        widget->comboGameState = this;
        widget->AddToViewport();
	}
}

void AComboGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    DecreaseComboValue(DeltaTime);
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

void AComboGameState::ResetCombo() {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("ResetCombo::Called"));
    CurrentComboLevel = 1;
    StyleLevel = EComboLevel::D;
    CurrentPoint = 0.0f;
}



