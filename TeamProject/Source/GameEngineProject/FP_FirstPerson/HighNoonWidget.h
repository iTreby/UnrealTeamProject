// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameCharacter.h"
#include "HighNoonWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEENGINEPROJECT_API UHighNoonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
		class AGameCharacter* Player;
};
