// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChamberBox.generated.h"

class UBoxComponent;
class InputComponent;


UCLASS()
class ASSIGNMENT_API AChamberBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChamberBox();

	UFUNCTION(BlueprintCallable, Category = "ChamberBox")
	void PickupBox();

	UFUNCTION(BlueprintCallable, Category = "ChamberBox")
	void DropBox();
	
	UPROPERTY(EditAnywhere, Category = "ChamberBox")
	UStaticMeshComponent* BoxMesh;

	UPROPERTY(EditAnywhere, Category = "ChamberBox")
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, Category = "ChamberBox")
	UBoxComponent* PlayerOverlapCollider;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bIsHeld;
	bool bPlayerNearby;

	UInputComponent* InputComp = nullptr;

	APawn* PlayerPawn = nullptr;

	UPROPERTY(EditAnywhere, Category = "ChamberBox")
	FVector HeldOffset = FVector(95, 0, 75);

	void OnGrabPressed();
	
};
