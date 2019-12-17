// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

class UInputComponent;

UCLASS()
class GAMEENGINEPROJECT_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const;
public:	
	void OnHighNoon();

	UPROPERTY(EditAnywhere)
		float scanOffset;

	UPROPERTY(EditAnywhere)
		float scanWidth = 250;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
