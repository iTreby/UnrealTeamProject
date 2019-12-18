// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "FP_FirstPersonCharacter.h"

// Sets default values
ARobot::ARobot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Robot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RobotMesh"));
	Robot->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARobot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

