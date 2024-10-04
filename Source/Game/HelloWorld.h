#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "HelloWorld.generated.h"

class AMyModule;

UCLASS()
class GAME_API AHelloWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHelloWorld();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UTextRenderComponent* MyText;

	UPROPERTY(EditAnywhere, Category = "MyCategory")
	float MyFloat;

	UPROPERTY(VisibleAnywhere, Category = "MyCategory")
	float MyFloat2;

	UPROPERTY(EditInstanceOnly, Category = "MyCategory")
	int32 MyInt;

	UPROPERTY(EditDefaultsOnly, Category = "MyCategory")
	int32 MyInt2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	bool MyBool;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyCategory")
	bool MyBool2;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "MyCategory")
	bool MyBool3;

	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	void MyFunction();

	void CreateTextComponent();

	AMyModule* MyFirstRef; // Assign a reference to MyModule class
};
