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

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->InitBoxExtent(FVector(300));
	BoxComponent->SetCollisionProfileName("Trigger");
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ARobot::OnOverlapBegin);

	Dimensions = FVector(300, 0, 0);
	AxisVector = FVector(0, 0, 1);
	Multiplier = 50.f;

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
	if (isActorOn)
	{
		FVector NewLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

		AngleAxis += DeltaTime * Multiplier;

		if (AngleAxis >= 360.0f) {
			AngleAxis = 0;
		}

		FVector RotateValue = Dimensions.RotateAngleAxis(AngleAxis, AxisVector);
		NewLocation.X += RotateValue.X;
		NewLocation.Y += RotateValue.Y;
		NewLocation.Z += RotateValue.Z;
		FRotator NewRotation = FRotator(0,AngleAxis,0);

		FQuat QuatRotation = FQuat(NewRotation);

		SetActorLocationAndRotation(NewLocation, QuatRotation, false, 0, ETeleportType::None);

		
	}
}

void ARobot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		isActorOn = true;
		Player = Cast<AFP_FirstPersonCharacter>(OtherActor);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Player Hit")));
	}
}