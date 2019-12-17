// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"
#include "GameEnemy.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"

#define COLLISION_WEAPON		ECC_GameTraceChannel1

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

}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameCharacter::OnHighNoon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("It's High Noon")));

	TArray<TEnumAsByte<EObjectTypeQuery>> query;
	TArray<AActor*> ignore;
	TArray<AActor*> out;
	auto camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	this->SetActorRotation(camera->GetCameraRotation());
	/*
	FVector actorLocation = camera->GetCameraLocation();
	actorLocation.X += scanOffset; // Create Scan infront of player so as to not scan for enemies behind player (outside of FoV)*/

	FVector actorLocation = GetActorLocation();
	actorLocation.X += scanOffset;
	UKismetSystemLibrary::BoxOverlapActors(this, actorLocation, FVector(scanWidth, scanWidth, 100), query, AGameEnemy::StaticClass(), ignore, out);
	DrawDebugBox(GetWorld(), actorLocation, FVector(scanWidth, scanWidth, 100), FColor::Purple, true, -1, 0, 10);
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

	for (AActor* actor : out)
	{
		auto enemy = Cast<AGameEnemy>(actor);
		
		if (enemy != nullptr)
		{	
			const FVector EndTrace = actor->GetActorLocation();
			const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
			//AActor* DamagedActor = Impact.GetActor();
		}
	}

	// Calculate endpoint of trace
	

	// Check for impact
	

	// Deal with impact
	


//	ScanBox->SetCollisionEnabled = true;

}

FHitResult AGameCharacter::WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, Instigator);
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, COLLISION_WEAPON, TraceParams);

	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, true);
	return Hit;
}


// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("HighNoon", IE_Pressed, this, &AGameCharacter::OnHighNoon);

}

