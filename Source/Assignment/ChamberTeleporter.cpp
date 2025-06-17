// Fill out your copyright notice in the Description page of Project Settings.


#include "ChamberTeleporter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AChamberTeleporter::AChamberTeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TeleporterBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeleporterBase"));
	RootComponent = TeleporterBase;

	TeleporterCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TeleporterCollider"));
	TeleporterCollider->SetupAttachment(TeleporterBase);
}

// Called when the game starts or when spawned
void AChamberTeleporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChamberTeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

