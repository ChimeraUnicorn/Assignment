// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChamberPlatform.generated.h"

class UBoxComponent;

UENUM()
enum class EPlatformBehaviour
{
	Move UMETA(DisplayName="Move"),
	Fall UMETA(DisplayName="Fall"),
};

UCLASS()
class ASSIGNMENT_API AChamberPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChamberPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* PlatformBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChamberPlatform")
	EPlatformBehaviour PlatformBehaviour = EPlatformBehaviour::Move;

	// Falling Behaviour
	UPROPERTY(EditAnywhere, Category = "ChamberPlatform|Fall")
	float FallDelay = 2.0f;

	UPROPERTY(EditAnywhere, Category = "ChamberPlatform|Fall")
	float FallSpeed = 300.0f;

	bool bPlayerIsOnPlatform = false;
	float TimeOnPlatform = 0.0f;
	bool bIsFalling = false;

	// Moving Behaviour
	UPROPERTY(EditAnywhere, Category = "ChamberPlatform|Move")
	FVector MoveOffest = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "ChamberPlatform|Move")
	float MoveSpeed = 100.0f;

private:
	FVector StartLocation = FVector(0.0f, 0.0f, 0.0f);
	FVector EndLocation = FVector(0.0f, 0.0f, 0.0f);
	bool bIsMoving = true;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
