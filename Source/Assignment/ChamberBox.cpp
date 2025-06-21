// Fill out your copyright notice in the Description page of Project Settings.


#include "ChamberBox.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChamberBox::AChamberBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	RootComponent = BoxMesh;

	BoxCollider =  CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(BoxMesh);

	PlayerOverlapCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerOverlapCollider"));
	PlayerOverlapCollider->SetupAttachment(BoxMesh);
	PlayerOverlapCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PlayerOverlapCollider->SetGenerateOverlapEvents(true);
	PlayerOverlapCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	PlayerOverlapCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AChamberBox::PickupBox()
{
	if (!PlayerPawn || bIsHeld)
	{
		return;
	}

	bIsHeld = true;

	BoxMesh->SetSimulatePhysics(false);

	FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld, true);
	AttachToComponent(PlayerPawn->GetRootComponent(), Rules);
	SetActorRelativeLocation(HeldOffset);
}

void AChamberBox::DropBox()
{
	bIsHeld = false;

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	BoxMesh->SetSimulatePhysics(true);
}

void AChamberBox::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == PlayerPawn)
	{
		bPlayerNearby = true;
	}
}

void AChamberBox::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == PlayerPawn)
	{
		bPlayerNearby = false;
	}
}

// Called when the game starts or when spawned
void AChamberBox::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	PlayerOverlapCollider->OnComponentBeginOverlap.AddDynamic(this, &AChamberBox::OnComponentBeginOverlap);
	PlayerOverlapCollider->OnComponentEndOverlap.AddDynamic(this, &AChamberBox::OnComponentEndOverlap);

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		EnableInput(PC);
		InputComp = InputComponent;
		if (InputComp)
		{
			InputComp->BindAction("Grab", IE_Pressed, this, &AChamberBox::OnGrabPressed);
		}
	}
}

// Called every frame
void AChamberBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChamberBox::OnGrabPressed()
{
	if (bIsHeld)
	{
		DropBox();
	}
	else if (bPlayerNearby)
	{
		PickupBox();
	}
}

