// Fill out your copyright notice in the Description page of Project Settings.


#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "FirstPeronProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Enemy.h"
#include "Engine.h"
#include "ComboGameState.h"


// Sets default values
AFirstPeronProjectile::AFirstPeronProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFirstPeronProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root componentFirs
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void AFirstPeronProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFirstPeronProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		Destroy();
	}

    auto* enemy = Cast<AEnemy>(OtherActor);
    auto* comboGameState = Cast<AComboGameState>(UGameplayStatics::GetGameState(this));
    if (enemy) {
        float bodyPartMultiplier;
        if (enemy->isHeadShot) {
            enemy->HP -= enemy->damageHead;
            bodyPartMultiplier = enemy->damageHead * 10;
        } else {
            enemy->HP -= enemy->damageBody;
            bodyPartMultiplier = enemy->damageBody * 10;
        }
        comboGameState->IncreaseComboValue(bodyPartMultiplier);
    }

    if (OtherActor != NULL && !enemy && !isHit) {
        isHit = true;
        comboGameState->DecreaseComboValue();
    }

}

