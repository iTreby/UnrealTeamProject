// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class GAMEENGINEPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	//UPROPERTY(VisibleAnywhere)
    //class USceneComponent* Root;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* BodyMesh;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* HeadMesh;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* HeadShotBox;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float HP = 1.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    bool isHeadShot = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float damageBody = 0.1;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float damageHead = 0.3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void NotifyHit (
            class UPrimitiveComponent *MyComp,
            class AActor *Other,
            class UPrimitiveComponent *OtherComp,
            bool bSelfMoved,
            FVector HitLocation,
            FVector HitNormal,
            FVector NormalImpulse,
            const FHitResult &Hit
    ) override;

    class AFP_FirstPersonCharacter* GetPlayer();

	FTimerHandle TimerHandle;

	void UnFreeze();

	bool isFreeze = false;
	
};