// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChamberLaunchPad.generated.h"

class UCapsuleComponent;

UCLASS()
class ASSIGNMENT_API AChamberLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChamberLaunchPad();

	UPROPERTY(EditAnywhere, Category = "ChamberLaunchPad")
	UStaticMeshComponent* LaunchpadMesh;

	UPROPERTY(EditAnywhere, Category = "ChamberLaunchPad")
	UCapsuleComponent* LaunchpadCollider;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "ChamberLaunchPad")
	FRotator LaunchDirection = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "ChamberLaunchPad")
	float LaunchSpeed = 100.0f;
};
