#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChamberPlate.generated.h"

class UBoxComponent;
class AButtonManager;

UCLASS()
class ASSIGNMENT_API AChamberPlate : public AActor
{
	GENERATED_BODY()
	
public:
	AChamberPlate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChamberPlate")
	int32 PlateID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChamberPlate")
	AButtonManager* SequenceManager = nullptr;

	UPROPERTY(EditAnywhere, Category = "ChamberPlate")
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(EditAnywhere, Category = "ChamberPlate")
	UStaticMeshComponent* PlateMesh;
	
	UPROPERTY(EditAnywhere, Category = "ChamberPlate")
	UBoxComponent* PlateCollider;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool bIsPressed = false;
	FVector StartLocation = FVector::ZeroVector;
	FVector EndOffset = FVector(0.0f, 0.0f , 10.0f);
	float LerpAlpha = 0.0f;
	float InterpSpeed = 2.0f;
};
