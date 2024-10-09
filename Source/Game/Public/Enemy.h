#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class GAME_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Enemy static mesh
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	UStaticMeshComponent* StaticMesh;

	// Allows child components to move freely
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	USceneComponent* DefaultSceneRoot;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	bool bHitDetected;
	FTimerHandle TimerHandle;
	void ResetHit();
};
