#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	SetFocus(PlayerPawn);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MoveToActor(PlayerPawn, 150);
}
