#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class GAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaSeconds) override;

	APawn* PlayerPawn;

};
