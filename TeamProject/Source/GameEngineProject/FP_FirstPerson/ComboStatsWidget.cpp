// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboStatsWidget.h"

float UComboStatsWidget::GetComboValueInPercent() {
    return comboGameState->CurrentPoint / 100;
}

FText UComboStatsWidget::GetComboLevelDisplay() {
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EComboLevel"), true);
    if(!EnumPtr) return FText::FromString("Invalid");
    FText result = FText::FromString(EnumPtr->GetNameStringByValue(comboGameState->CurrentComboLevel));
    return result;
}