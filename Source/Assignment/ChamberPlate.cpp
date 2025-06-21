
#include "ChamberPlate.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ButtonManager.h"

AChamberPlate::AChamberPlate()
{
	PrimaryActorTick.bCanEverTick = true;

	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	RootComponent = PlateMesh;

	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	PlateMesh->SetupAttachment(PlateMesh);
}

void AChamberPlate::BeginPlay()
{
	Super::BeginPlay();

	PlateCollider->OnComponentBeginOverlap.AddDynamic(this, &AChamberPlate::OnComponentBeginOverlap);
	PlateCollider->OnComponentEndOverlap.AddDynamic(this, &AChamberPlate::OnComponentEndOverlap);

}


void AChamberPlate::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SequenceManager)
	{
		SequenceManager->NotifyPlatePressed(PlateID);
	}
}

void AChamberPlate::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (SequenceManager)
	{
		SequenceManager->NotifyPlateReleased(PlateID);
	}
}
