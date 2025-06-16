// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonManager.h"
#include "ChamberButton.h"
#include "ChamberDoor.h"

// Sets default values
AButtonManager::AButtonManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AButtonManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtonManager::NotifyButtonPressed(int32 ButtonID)
{
	CurrentSequence.Add(ButtonID);

	if (CurrentSequence.Num() > CorrectSequence.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Too many inputs. Resetting."));
		ResetSequence();
		return;
	}

	// If full sequence entered, check against expected sequence
	if (CurrentSequence.Num() == CorrectSequence.Num())
	{
		bool bMatch = true;

		for (int32 i = 0; i < CorrectSequence.Num(); ++i)
		{
			if (CurrentSequence[i] != CorrectSequence[i])
			{
				bMatch = false;
				break;
			}
		}

		if (bMatch)
		{
			UE_LOG(LogTemp, Warning, TEXT("Correct sequence! Opening door."));
			if (DoorToOpen)
			{
				DoorToOpen->bShouldOpen = true;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Wrong sequence. Resetting."));
			ResetSequence(); // Always reset after full attempt
		}
	}
}

void AButtonManager::ResetSequence()
{
	UE_LOG(LogTemp, Warning, TEXT("Resetting Sequence."));
	for (AChamberButton* CurrentButton : Buttons)
	{
		if (CurrentButton != nullptr)
		{
			CurrentButton->RequestReset();
			UE_LOG(LogTemp, Warning, TEXT("Resetting Button."));
		}
	}
	CurrentSequence.Empty();
}

