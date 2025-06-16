// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonManager.generated.h"

class AChamberDoor;
class AChamberButton;
UCLASS()
class ASSIGNMENT_API AButtonManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when a button is pressed
	UFUNCTION()
	void NotifyButtonPressed(int32 ButtonID);

	// Assign the correct sequence in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> CorrectSequence;

	// Current Sequence
	UPROPERTY(VisibleAnywhere)
	TArray<int32> CurrentSequence;

	UPROPERTY(EditAnywhere)
	TArray<AChamberButton*> Buttons;
	
	// Door to open set in editor
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	AChamberDoor* DoorToOpen = nullptr;

	UPROPERTY(BlueprintReadonly)
	AChamberButton* ResetButtons = nullptr;
	
private:
	void ResetSequence();
};
