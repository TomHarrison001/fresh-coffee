#include "TriggerDoor.h"

// Sets default values for this component's properties
UTriggerDoor::UTriggerDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerDoor::BeginPlay()
{
	Super::BeginPlay();
	CurrentLocation = GetOwner()->GetActorLocation();
	TargetHeight += CurrentLocation.Z;
}

// Called every frame
void UTriggerDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetAllValidActors(DeltaTime);
}

void UTriggerDoor::OpenDoor(float DeltaTime)
{
	CurrentLocation.Z = FMath::FInterpConstantTo(CurrentLocation.Z, TargetHeight, DeltaTime, MoveSpeed);
	GetOwner()->SetActorLocation(CurrentLocation);
}

void UTriggerDoor::GetAllValidActors(float DeltaTime)
{
	TArray<AActor*> OverlappingActors;

	if (TriggerVol != nullptr)
	{
		TriggerVol->GetOverlappingActors(OverlappingActors);

		for (AActor* Actor : OverlappingActors)
		{
			for (FName Tag : Actor->Tags)
			{
				if (Tag == "Player")
				{
					OpenDoor(DeltaTime);
				}
				//GLog->Log(Tag.ToString());
			}
		}
	}
}
