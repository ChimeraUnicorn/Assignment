// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChamberDoor.generated.h"

UCLASS()
class ASSIGNMENT_API AChamberDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChamberDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
	bool bShouldOpen = false;

	
private:
	FVector StartLocation = FVector::ZeroVector;
	FVector EndOffset = FVector(0.0f, 170.0f , 0.0f);
	float LerpAlpha = 0.0f;
	float InterpSpeed = 2.0f;
};