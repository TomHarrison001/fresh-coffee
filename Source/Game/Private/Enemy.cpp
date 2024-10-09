#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block); // Set collision to block
	StaticMesh->BodyInstance.SetInstanceNotifyRBCollision(true); // Enables hit events
	StaticMesh->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
	StaticMesh->OnComponentHit.AddDynamic(this, &AEnemy::OnHit); // Register Hit Event to function
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<AMainCharacter>(OtherActor))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemy::ResetHit, 1.0f, false, 0.1f);
		if (!bHitDetected)
		{
			GLog->Log("Character Hit detected");
			AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
			//MainChar->Jump();
			GLog->Log(FString::SanitizeFloat(MainChar->GetVelocity().Length()));
			bHitDetected = true;
		}
	}
}

void AEnemy::ResetHit()
{
	bHitDetected = false;
}
