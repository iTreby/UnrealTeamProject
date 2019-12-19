// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HighNoonWidget.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "GameCharacter.generated.h"

class UInputComponent;

UCLASS()
class GAMEENGINEPROJECT_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacter();

	UPROPERTY(BlueprintReadOnly)
		UBoxComponent* ScanBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const;
	FTimerHandle TimerHandle;
	FTimerHandle CooldownHandle;

	//HighNoon
	bool HighNoonCalled;
	bool HasFiredHighNoon;
	bool HighNoonOnCooldown;
	int HighNoonTickCounter = 10;

	class UHighNoonWidget* HighNoonHud;

public:	
	
	//HighNoon
	UPROPERTY(EditAnywhere)
		float scanOffset;
	UPROPERTY(EditAnywhere)
		float scanWidth = 250;
	UPROPERTY(EditAnywhere)
		float scanLength = 250;
	UPROPERTY(EditAnywhere)
		UParticleSystem* HighNoonKillParticle;
	UPROPERTY(BlueprintReadOnly)
		int ScannedEnemies = 0;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UHighNoonWidget> Widget;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void OnHighNoon();
	void CallHighNoon();
	void CooldownHighNoon();
};
