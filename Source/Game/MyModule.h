#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyModule.generated.h"

UCLASS()
class GAME_API AMyModule : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyModule();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MyFunction();
};
