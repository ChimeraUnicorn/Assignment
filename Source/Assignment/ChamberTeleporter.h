// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChamberTeleporter.generated.h"

class UCapsuleComponent;

UCLASS()
class ASSIGNMENT_API AChamberTeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChamberTeleporter();
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TeleporterBase;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* TeleporterCollider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
