
#include "ChamberPlate.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ButtonManager.h"

AChamberPlate::AChamberPlate()
{
	PrimaryActorTick.bCanEverTick = true;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	RootComponent = FrameMesh;

	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	PlateMesh->SetupAttachment(FrameMesh);
	
	PlateCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PlateCollider"));
	PlateCollider->SetupAttachment(PlateMesh);
	PlateCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PlateCollider->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
}

void AChamberPlate::BeginPlay()
{
	Super::BeginPlay();

	PlateCollider->OnComponentBeginOverlap.AddDynamic(this, &AChamberPlate::OnComponentBeginOverlap);
	PlateCollider->OnComponentEndOverlap.AddDynamic(this, &AChamberPlate::OnComponentEndOverlap);

	StartLocation = PlateMesh->GetRelativeLocation();
}

void AChamberPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsPressed)
	{
		LerpAlpha = FMath::Clamp<float>(LerpAlpha + (InterpSpeed * DeltaTime), 0.0f, 1.0f);
	}
	else
	{
		LerpAlpha = FMath::Clamp<float>(LerpAlpha - (InterpSpeed * DeltaTime), 0.0f, 1.0f);
	}

	FVector EndLocation = FMath::Lerp(StartLocation, (StartLocation - EndOffset), LerpAlpha);
	PlateMesh->SetRelativeLocation(EndLocation);
}


void AChamberPlate::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bIsPressed = true;
	if (SequenceManager)
	{
		SequenceManager->NotifyPlatePressed(PlateID);
	}
}

void AChamberPlate::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsPressed = false;
	if (SequenceManager)
	{
		SequenceManager->NotifyPlateReleased(PlateID);
	}
}
