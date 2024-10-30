#include "EnemyBTAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AEnemyBTAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		// Sets to PlayerActor to blackboard key
		GetBlackboardComponent()->SetValueAsObject(TEXT("PlayerActor"), PlayerPawn);
		// Sets to EnemyActor start position to blackboard key
		GetBlackboardComponent()->SetValueAsVector(TEXT("EnemyStartPosition"), GetPawn()->GetActorLocation());
	}
}

void AEnemyBTAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Set bIsPlayerSeen to true if player is seen (Blackboard key)
	GetBlackboardComponent()->SetValueAsBool(TEXT("bIsPlayerSeen"), LineOfSightTo(PlayerPawn));
}
