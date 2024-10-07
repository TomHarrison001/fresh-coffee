#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "TriggerDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UTriggerDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);

	void GetAllValidActors(float DeltaTime);

private:
	UPROPERTY(EditAnywhere, Category = "Door")
	float TargetHeight = 20.f;

	UPROPERTY(EditAnywhere, Category = "Door")
	float MoveSpeed = 20.f;
	
	UPROPERTY(EditAnywhere, Category = "Door")
	ATriggerVolume* TriggerVol;

	FVector CurrentLocation;
};
