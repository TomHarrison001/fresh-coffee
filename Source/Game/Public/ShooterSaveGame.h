#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ShooterSaveGame.generated.h"

UCLASS()
class GAME_API UShooterSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UShooterSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 SlotIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVector WorldLocation;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FRotator WorldRotation;
};
