// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "FirstPeronProjectile.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

    BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootComponent);

    HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadMesh"));
    HeadMesh->SetupAttachment(RootComponent);
    HeadMesh->SetCollisionProfileName("HeadShot");

    HeadShotBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HeadShotBox"));
    HeadShotBox->InitBoxExtent(FVector(80,80,80)); // set size of the collision
    HeadShotBox->SetCollisionProfileName("HeadShotBoxTrigger");
    HeadShotBox->SetupAttachment(HeadMesh);

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AEnemy::NotifyHit (
        class UPrimitiveComponent *MyComp,
        class AActor *Other,
        class UPrimitiveComponent *OtherComp,
        bool bSelfMoved,
        FVector HitLocation,
        FVector HitNormal,
        FVector NormalImpulse,
        const FHitResult &Hit
) {
    auto projectile = Cast<AFirstPeronProjectile>(Other);
    if (!projectile) { return ;}
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Enemy::HP: %f"), HP));
    if (HP <= 0) {
        Destroy();
    }
}

