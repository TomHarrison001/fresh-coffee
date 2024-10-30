#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyBTAIController.generated.h"

UCLASS()
class GAME_API AEnemyBTAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	APawn* PlayerPawn;

};
