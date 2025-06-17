// Fill out your copyright notice in the Description page of Project Settings.


#include "ChamberTeleporter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

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

void AChamberTeleporter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelToLoad);
}

// Called when the game starts or when spawned
void AChamberTeleporter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(TeleporterCollider))
	{
		TeleporterCollider->OnComponentBeginOverlap.AddDynamic(this, &AChamberTeleporter::OnComponentBeginOverlap);
	}
}

// Called every frame
void AChamberTeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

