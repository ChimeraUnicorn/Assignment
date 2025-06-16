// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonManager.h"
#include "GameFramework/Actor.h"
#include "ChamberButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonActivated);

class UBoxComponent;

UCLASS()
class ASSIGNMENT_API AChamberButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChamberButton();

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void RequestReset();

	UFUNCTION(BlueprintCallable)
	void ForceReset();

	UFUNCTION(BlueprintCallable)
	void ResetButton();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FOnButtonActivated OnButtonActivated;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ButtonMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* ButtonCollider;

	UPROPERTY(EditAnywhere)
	int32 ButtonID;

	UPROPERTY(EditAnywhere)
	AButtonManager* ButtonManager;
	
	UPROPERTY(EditAnywhere)
	bool IsButtonPressed = false;
	
private:
	bool bIsBeingStoodOn = false;
	bool bPendingReset = false;
	FTimerHandle PendingResetTimerHandle;

	UPROPERTY(EditAnywhere)
	float PendingResetDelay = 2.0f;
	
	FVector StartLocation = FVector::ZeroVector;
	FVector EndOffset = FVector(0.0f, 0.0f , 10.0f);
	float LerpAlpha = 0.0f;
	float InterpSpeed = 2.0f;
};