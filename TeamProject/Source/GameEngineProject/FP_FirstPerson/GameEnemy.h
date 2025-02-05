// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "GameFramework/Character.h"
#include "WidgetComponent.h"
#include "GameEnemy.generated.h"

UCLASS()
class GAMEENGINEPROJECT_API AGameEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameEnemy();

	UPROPERTY(EditAnywhere)
		UWidgetComponent* HighNoonWidget;

	UPROPERTY(BlueprintReadWrite)
		bool IsBoss;

	class AGameCharacter* Player;
	void IsHighNooned();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle;
	void RemoveHighNoon();
	bool wasHighNooned;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
