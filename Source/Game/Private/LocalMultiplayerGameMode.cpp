#include "LocalMultiplayerGameMode.h"

void ALocalMultiplayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld(); // Returns the world the actor is in
	UGameInstance* gameInstance = World->GetGameInstance();
	FString error = "Player not found.";

	ULocalPlayer* LocalPlayer = World->GetGameInstance()->CreateLocalPlayer(1, error, true);
}
