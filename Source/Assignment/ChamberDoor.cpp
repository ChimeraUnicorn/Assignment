// Fill out your copyright notice in the Description page of Project Settings.


#include "ChamberDoor.h"

// Sets default values
AChamberDoor::AChamberDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = FrameMesh;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorMesh->SetupAttachment(FrameMesh);

}

// Called when the game starts or when spawned
void AChamberDoor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = DoorMesh->GetRelativeLocation();
}

// Called every frame
void AChamberDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bShouldOpen)
	{
		LerpAlpha = FMath::Clamp<float>(LerpAlpha + (InterpSpeed * DeltaTime), 0.0f, 1.0f);
	}
	else
	{
		LerpAlpha = FMath::Clamp<float>(LerpAlpha - (InterpSpeed * DeltaTime), 0.0f, 1.0f);
	}

	FVector EndLocation = FMath::Lerp(StartLocation, (StartLocation - EndOffset), LerpAlpha);
	DoorMesh->SetRelativeLocation(EndLocation);
}