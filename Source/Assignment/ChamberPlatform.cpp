// Fill out your copyright notice in the Description page of Project Settings.


#include "ChamberPlatform.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"

// Sets default values
AChamberPlatform::AChamberPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	RootComponent = PlatformMesh;

	PlatformBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PlatformBox"));
	PlatformBox->SetupAttachment(PlatformMesh);
}

// Called when the game starts or when spawned
void AChamberPlatform::BeginPlay()
{
	Super::BeginPlay();

	PlatformBox->OnComponentBeginOverlap.AddDynamic(this, &AChamberPlatform::OnComponentBeginOverlap);
	PlatformBox->OnComponentEndOverlap.AddDynamic(this, &AChamberPlatform::OnComponentEndOverlap);

	StartLocation = GetActorLocation();
	EndLocation = StartLocation + MoveOffest;
}

// Called every frame
void AChamberPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlatformBehaviour == EPlatformBehaviour::Move)
	{
		FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), bIsMoving ? EndLocation : StartLocation, DeltaTime, MoveSpeed);

		SetActorLocation(NewLocation);

		if (FVector::Dist(NewLocation, bIsMoving ? EndLocation : StartLocation) < 1.0f)
		{
			bIsMoving = !bIsMoving;
		}
	}
	else if (PlatformBehaviour == EPlatformBehaviour::Fall)
	{
		if (bPlayerIsOnPlatform && !bIsFalling)
		{
			TimeOnPlatform = TimeOnPlatform + DeltaTime;

			if (TimeOnPlatform >= FallDelay)
			{
				bIsFalling = true;
			}
		}

		if (bIsFalling)
		{
			FVector FallLocation = GetActorLocation();
			FallLocation.Z -= FallSpeed * DeltaTime;
			SetActorLocation(FallLocation);
		}
	}
}

void AChamberPlatform::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor))
	{
		TimeOnPlatform = 0.0f;
		bPlayerIsOnPlatform = true;
	}
}

void AChamberPlatform::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ACharacter>(OtherActor))
	{
		bPlayerIsOnPlatform = false;
		TimeOnPlatform = 0.0f;
	}
}

