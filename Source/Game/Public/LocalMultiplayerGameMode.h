#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LocalMultiplayerGameMode.generated.h"

UCLASS()
class GAME_API ALocalMultiplayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();
};
