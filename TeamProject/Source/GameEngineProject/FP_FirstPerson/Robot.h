// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Robot.generated.h"

UCLASS()
class GAMEENGINEPROJECT_API ARobot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARobot();
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Robot;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* BoxComponent;
	bool isActorOn = false;

	float AngleAxis;

	UPROPERTY(EditAnywhere, Category = Movement)
		FVector Dimensions;

	UPROPERTY(EditAnywhere, Category = Movement)
		FVector AxisVector;

	UPROPERTY(EditAnywhere, Category = Movement)
		float Multiplier;

	UPROPERTY(EditAnywhere)
		class USoundBase* RobotAtk;

	UPROPERTY(EditAnywhere)
		class USoundBase* RobotActivate;


private:
	class AFP_FirstPersonCharacter* Player = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
