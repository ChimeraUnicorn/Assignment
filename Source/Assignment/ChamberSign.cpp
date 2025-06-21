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
	TextComponent->SetHiddenInGame(false);
}

// Called when the game starts or when spawned

#if WITH_EDITOR
void AChamberSign::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	if (PropName == GET_MEMBER_NAME_CHECKED(AChamberSign, DisplayText) || PropName == GET_MEMBER_NAME_CHECKED(AChamberSign, TextColour) || PropName == GET_MEMBER_NAME_CHECKED(AChamberSign, TextSize))
	{
		TextComponent->SetText(DisplayText);
		TextComponent->SetWorldSize(TextSize);

		FColor ChosenColour;
		switch (TextColour)
		{
			case ETextColour::TCO_Red:   ChosenColour  = FColor::Red; break;
			case ETextColour::TCO_Green: ChosenColour  = FColor::Green; break;
			case ETextColour::TCO_Blue:  ChosenColour  = FColor::Blue; break;
			case ETextColour::TCO_Yellow: ChosenColour  = FColor::Yellow; break;
			case ETextColour::TCO_Orange: ChosenColour  = FColor::Orange; break;
			case ETextColour::TCO_Purple: ChosenColour  = FColor::Purple; break;
			default: ChosenColour = FColor::White;
		}

		TextComponent->SetTextRenderColor(ChosenColour);
		TextComponent->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	}
}
#endif

// Called every frame
void AChamberSign::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

