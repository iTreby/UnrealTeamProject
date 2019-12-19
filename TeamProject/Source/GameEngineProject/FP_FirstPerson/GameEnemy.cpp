// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEnemy.h"
#include "Engine.h"
#include "TimerManager.h"

// Sets default values
AGameEnemy::AGameEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HighNoonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HighNoonWidget"));
	HighNoonWidget->SetupAttachment(RootComponent);
	HighNoonWidget->SetVisibility(false);
}

//Redundancy - Remove edge case where Visibility was left on by character system
void AGameEnemy::RemoveHighNoon()
{
	HighNoonWidget->SetVisibility(false);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	if (Player != nullptr) {
		Player->ScannedEnemies = 0;
	}

	wasHighNooned = false;
}
void AGameEnemy::IsHighNooned() 
{
	//Do once
	if (wasHighNooned == false) {
		if (Player != nullptr) {
			Player->ScannedEnemies++;
		}
		wasHighNooned = true;
		HighNoonWidget->SetVisibility(true);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGameEnemy::RemoveHighNoon, 5, true);
	}
}

// Called when the game starts or when spawned
void AGameEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGameEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Only rotate high noon widget when it is set to visible by the player
	if (HighNoonWidget->IsVisible()) {
		auto camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		HighNoonWidget->SetWorldRotation(camera->GetCameraRotation());
		HighNoonWidget->AddLocalRotation(FRotator(0, 180, 0));
	}

}

// Called to bind functionality to input
void AGameEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

