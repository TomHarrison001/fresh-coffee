#include "Collectable.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Mesh
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CollectableSceneComponent"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMeshComponent"));
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	StaticMesh->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);

	// Register Events
	OnActorBeginOverlap.AddDynamic(this, &ACollectable::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ACollectable::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollectable::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor name: %s"), *OtherActor->GetName());

	if (Cast<AMainCharacter>(OtherActor))
	{
		AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
		//MainChar->StartTimedPowerUp();
		MainChar->StartLoopedPowerUp();
		Destroy();
	}
}

void ACollectable::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	// Not currently used
}
