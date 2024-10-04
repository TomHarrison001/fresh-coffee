#include "HelloWorld.h"
#include "MyModule.h"

// Sets default values
AHelloWorld::AHelloWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CreateTextComponent();
}

// Called when the game starts or when spawned
void AHelloWorld::BeginPlay()
{
	Super::BeginPlay();
	
	//MyFunction();

	//MyFirstRef->MyFunction();
}

// Called every frame
void AHelloWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHelloWorld::MyFunction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Red,
			FString::Printf(TEXT("Hello World 1")));
		UE_LOG(LogTemp, Warning, TEXT("Hello World 2"));
		GLog->Log(TEXT("Hello World 3"));
	}
}

void AHelloWorld::CreateTextComponent()
{
	MyText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("My Text Component"));
	MyText->SetWorldSize(150.f);
	MyText->SetText(FText::FromString(TEXT("defaultText")));
	RootComponent = MyText;
}
