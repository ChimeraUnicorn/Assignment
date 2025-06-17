// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChamberTeleporter.generated.h"

class UCapsuleComponent;
class UGameplayStatics;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelToLoad;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bHasTeleported = false;
};
