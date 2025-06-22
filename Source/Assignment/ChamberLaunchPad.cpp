// Fill out your copyright notice in the Description page of Project Settings.


#include "ChamberLaunchPad.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AChamberLaunchPad::AChamberLaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaunchpadMesh =  CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchpadMesh"));
	RootComponent = LaunchpadMesh;

	LaunchpadCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LaunchpadCollider"));
	LaunchpadCollider->SetupAttachment(LaunchpadMesh);
	LaunchpadCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LaunchpadCollider->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AChamberLaunchPad::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)
	{
		return;
	}

	if (ACharacter* C = Cast<ACharacter>(OtherActor))
	{
		FVector Dir = LaunchDirection.Vector();
		C->LaunchCharacter(Dir * LaunchSpeed, true, true);
		return;
	}

	UPrimitiveComponent* PhysComp = nullptr;
	
	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		PhysComp = OtherComp;
	}
	else
	{
		TArray<UPrimitiveComponent*> Comps;
		OtherActor->GetComponents<UPrimitiveComponent>(Comps);
		for (UPrimitiveComponent* Comp : Comps)
		{
			if (Comp->IsSimulatingPhysics())
			{
				PhysComp = Comp;
				break;
			}
		}
	}

	if (PhysComp)
	{
		FVector Dir = LaunchDirection.Vector();
		PhysComp->AddImpulse(Dir * LaunchSpeed * PhysComp->GetMass());
	}
}

// Called when the game starts or when spawned
void AChamberLaunchPad::BeginPlay()
{
	Super::BeginPlay();

	LaunchpadCollider->OnComponentBeginOverlap.AddDynamic(this, &AChamberLaunchPad::OnComponentBeginOverlap);
}

// Called every frame
void AChamberLaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

