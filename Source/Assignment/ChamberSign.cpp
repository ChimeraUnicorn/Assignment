// Fill out your copyright notice in the Description page of Project Settings.


#include "ChamberSign.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AChamberSign::AChamberSign()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	RootComponent = TextComponent;

	TextComponent->SetHorizontalAlignment(EHTA_Center);
	TextComponent->SetVerticalAlignment(EVRTA_TextCenter);
	
}

// Called when the game starts or when spawned


void AChamberSign::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	TextComponent->SetText(DisplayText);
	TextComponent->SetWorldSize(TextSize);

	
	switch (FColor TextColour = FColor::White)
	{
		case ETextColour::TCO_Red:   TextColour  = FColor::Red; break;
		case ETextColour::TCO_Green: TextColour  = FColor::Green; break;
		case ETextColour::TCO_Blue:  TextColour  = FColor::Blue; break;
		case ETextColour::TCO_Yellow: TextColour  = FColor::Yellow; break;
		case ETextColour::TCO_Orange: TextColour  = FColor::Orange; break;
		case ETextColour::TCO_Purple: TextColour  = FColor::Purple; break;
		default: TextColour = FColor::White;
	}
}

// Called every frame
void AChamberSign::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

