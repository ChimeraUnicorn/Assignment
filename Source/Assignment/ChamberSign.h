// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChamberSign.generated.h"

class UTextRenderComponent;

UENUM(BlueprintType)
enum class ETextColour : uint8
{
	TCO_White UMETA(DisplayName="White"),
	TCO_Red UMETA(DisplayName="Red"),
	TCO_Green UMETA(DisplayName="Green"),
	TCO_Blue UMETA(DisplayName="Blue"),
	TCO_Yellow UMETA(DisplayName="Yellow"),
	TCO_Orange UMETA(DisplayName="Orange"),
	TCO_Purple UMETA(DisplayName="Purple"),
};

UCLASS()
class ASSIGNMENT_API AChamberSign : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChamberSign();

	UPROPERTY(VisibleAnywhere, Category="ChamberSign")
	UTextRenderComponent* TextComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ChamberSign")
	FText DisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ChamberSign")
	float TextSize = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ChamberSign")
	ETextColour TextColour = ETextColour::TCO_White;
	
protected:
	// Called when the game starts or when spawned
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
