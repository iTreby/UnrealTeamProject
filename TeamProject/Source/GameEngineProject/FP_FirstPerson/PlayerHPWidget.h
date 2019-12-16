// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEENGINEPROJECT_API UPlayerHPWidget : public UUserWidget
{
	GENERATED_BODY()
public:
		UPROPERTY(BlueprintReadOnly)
		class AFP_FirstPersonCharacter* Player;
};
