// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_FirstPersonCharacter.h"
#include "Blueprint/UserWidget.h"
#include "FpHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEENGINEPROJECT_API UFpHPWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BluePrintReadOnly)
		class AFP_FirstPersonCharacter* Player;

};
