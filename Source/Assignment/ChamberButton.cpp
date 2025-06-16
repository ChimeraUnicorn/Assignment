// Fill out your copyright notice in the Description page of Project Settings.


#include "ChamberButton.h"

#include "Components/BoxComponent.h"

// Sets default values
AChamberButton::AChamberButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	RootComponent = FrameMesh;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(FrameMesh);

	ButtonCollider =  CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonCollider"));
	ButtonCollider->SetupAttachment(FrameMesh);

}

void AChamberButton::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bIsBeingStoodOn = true;
	
	if (!IsButtonPressed)
	{
		IsButtonPressed = true;
		OnButtonActivated.Broadcast();

		if (ButtonManager)
		{
			ButtonManager->NotifyButtonPressed(ButtonID);
		}
	}
}

void AChamberButton::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsBeingStoodOn = false;

	if (bPendingReset)
	{
		GetWorldTimerManager().ClearTimer(PendingResetTimerHandle);
		ResetButton();
		bPendingReset = false;
	}
}

void AChamberButton::RequestReset()
{
	if (!bIsBeingStoodOn)
	{
		ResetButton();
		return;
	}
	else
	{
		bPendingReset = true;
		GetWorldTimerManager().SetTimer(PendingResetTimerHandle, this, &AChamberButton::ForceReset, PendingResetDelay, false);
	}
	
}

void AChamberButton::ForceReset()
{
	ResetButton();
	bPendingReset = false;
	GetWorldTimerManager().ClearTimer(PendingResetTimerHandle);
}

void AChamberButton::ResetButton()
{
	IsButtonPressed = false;
	bIsBeingStoodOn = false;
	LerpAlpha = 0.0f;
	ButtonMesh->SetRelativeLocation(StartLocation);
}

// Called when the game starts or when spawned
void AChamberButton::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(ButtonCollider))
	{
		ButtonCollider->OnComponentBeginOverlap.AddDynamic(this, &AChamberButton::OnComponentBeginOverlap);
		ButtonCollider->OnComponentEndOverlap.AddDynamic(this, &AChamberButton::OnComponentEndOverlap);
	}
	StartLocation = ButtonMesh->GetRelativeLocation();
}

// Called every frame
void AChamberButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsButtonPressed)
	{
		LerpAlpha = FMath::Clamp<float>(LerpAlpha + (InterpSpeed * DeltaTime), 0.0f, 1.0f);
	}
	else
	{
		LerpAlpha = FMath::Clamp<float>(LerpAlpha - (InterpSpeed * DeltaTime), 0.0f, 1.0f);
	}

	FVector EndLocation = FMath::Lerp(StartLocation, (StartLocation - EndOffset), LerpAlpha);
	ButtonMesh->SetRelativeLocation(EndLocation);
}

