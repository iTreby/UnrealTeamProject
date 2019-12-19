// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"
#include "GameEnemy.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"

#define COLLISION_WEAPON		ECC_GameTraceChannel3

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Widget != nullptr) {
		HighNoonHud = CreateWidget<UHighNoonWidget>(UGameplayStatics::GetPlayerController(this, 0), Widget);
		HighNoonHud->Player = this;
	}

}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameCharacter::CallHighNoon() 
{
	if (!HighNoonOnCooldown && !HighNoonCalled) {
		//UGameplayStatics::PlaySoundAtLocation(this, HealSound, GetActorLocation()); Play High Noon
		HighNoonCalled = true;
		HighNoonOnCooldown = true;
		if (Widget != nullptr && ItsHighNoon != nullptr) {
			HighNoonHud->AddToViewport();
			UGameplayStatics::PlaySoundAtLocation(this, ItsHighNoon, GetActorLocation());
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("It's High Noon")));
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGameCharacter::OnHighNoon, .5f, true);
	}
	else if (HighNoonCalled) {
		HasFiredHighNoon = true;
	}
}

//Called every .5 Seconds for 5 seconds by CallHighNoon
void AGameCharacter::OnHighNoon()
{

	if (HighNoonTickCounter != 0) {
		HighNoonTickCounter--;

		//Declare Overlap params
		TArray<TEnumAsByte<EObjectTypeQuery>> query;
		TArray<AActor*> ignore;
		TArray<AActor*> out;

		//Get Player Cam rotation and apply offset to only check infront of player (in Fov)
		auto camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		FVector scanLocation = ((camera->GetActorForwardVector() * scanOffset) + camera->GetCameraLocation());

		//Throw overlap area
		UKismetSystemLibrary::BoxOverlapActors(this, scanLocation, FVector(scanWidth, scanWidth, 500), query, AGameEnemy::StaticClass(), ignore, out);
		//DrawDebugBox(GetWorld(), scanLocation, FVector(scanWidth, scanWidth, 500), FColor::Purple, true, -1, 0, 10);
		FString result = FString::Printf(TEXT("%d actors in Scan Area"), out.Num());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, result);

		APlayerController* PlayerController = Cast<APlayerController>(GetController());

		FVector ShootDir = FVector::ZeroVector;
		FVector StartTrace = FVector::ZeroVector;

		if (PlayerController)
		{
			// Calculate the direction of fire and the start location for trace
			FRotator CamRot;
			PlayerController->GetPlayerViewPoint(StartTrace, CamRot);
			ShootDir = CamRot.Vector();

			// Adjust trace so there is nothing blocking the ray between the camera and the pawn, and calculate distance from adjusted start
			StartTrace = StartTrace + ShootDir * ((GetActorLocation() - StartTrace) | ShootDir);
		}

		//Throw Linetrace to each enemy actor hit in Box Overlap Scan Area
		//Then apply logic to only the actors in FoV (not behind walls)
		for (AActor* enemyActor : out)
		{
			auto enemy = Cast<AGameEnemy>(enemyActor);

			if (enemy != nullptr && !enemy->IsBoss)
			{
				const FVector EndTrace = enemyActor->GetActorLocation();
				const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);

				if (!HasFiredHighNoon){
					enemy->Player = this;
					enemy->IsHighNooned();
				}

				else if (HasFiredHighNoon && Impact.Actor == Cast<AGameEnemy>(enemyActor)) {
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("ENEMY HIT")));
					enemy->HighNoonWidget->SetVisibility(false);

					if (HighNoonKillParticle != nullptr) {
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HighNoonKillParticle, enemy->GetActorTransform());
					}
					if (ExplodeSound != nullptr) {
						UGameplayStatics::PlaySoundAtLocation(this, ExplodeSound, enemy->GetActorLocation());
					}
					enemy->Destroy();
					ScannedEnemies = 0;
					HighNoonTickCounter = 0;
				}
				if (HighNoonTickCounter == 0 || HasFiredHighNoon) {
					enemy->HighNoonWidget->SetVisibility(false);
					ScannedEnemies = 0;
				}
			}
		}
	}
	
	//High Noon Used / Ended - Reset, call cooldown
	else {
		ScannedEnemies = 0;
		if (Widget != nullptr) {
			HighNoonHud->RemoveFromParent();
		}
		HasFiredHighNoon = false;
		HighNoonCalled = false;
		HighNoonTickCounter = 10;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		HighNoonOnCooldown = true;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGameCharacter::CooldownHighNoon, 5, true);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("High Noon Over")));
	}

}

void AGameCharacter::CooldownHighNoon() {
	HighNoonOnCooldown = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("High Noon Ready to use")));
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

//Throw custom linetrace (GameTrace4 Is Custom High Noon Linetrace that hits only Enemies)
FHitResult AGameCharacter::WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, Instigator);
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECollisionChannel::ECC_GameTraceChannel4, TraceParams); 

	//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, true);
	return Hit;
}


// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("HighNoon", IE_Pressed, this, &AGameCharacter::CallHighNoon);

}

