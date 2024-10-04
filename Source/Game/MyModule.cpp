#include "MyModule.h"

// Sets default values
AMyModule::AMyModule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyModule::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyModule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyModule::MyFunction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Red,
			FString::Printf(TEXT("My Function Works.")));
	}
}
