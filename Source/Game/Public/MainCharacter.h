#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputActionValue.h"
#include "FPSProjectile.h"
#include "MainCharacter.generated.h"

UCLASS()
class GAME_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Mapping Context file
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	// Jump Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	// Look Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	// Move Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	void Jumping();
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);

	void StartTimedPowerUp();
	void EndTimedPowerUp();

	void StartLoopedPowerUp();
	void EndLoopedPowerUp();

	FTimerHandle TimerHandle;
	FTimerHandle LoopedTimerHandle;
	int32 TimedLoopsRemaining;

	// Splitscreen Attributes
	/*
	// Jump Player 2 Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpActionPlayer2;

	// Move Player 2 Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveActionPlayer2;

	void JumpingPlayer2();
	void MovePlayer2(const FInputActionValue& Value);

	AMainCharacter* Player2Char;

	APlayerController* Player1Cont;
	APlayerController* Player2Cont;
	*/

	// LAN Multiplayer Attributes
	UFUNCTION(BlueprintCallable)
	void CallCreateLobby();

	UFUNCTION(BlueprintCallable)
	void CallClientTravel(const FString& Address);

	// FPS camera
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* FPSCameraComponent;

	// First-person mesh (arms), visible only to the owning player
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FPSMesh;

	// Jump Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* ShootAction;

	// Gun muzzle offset from the camera location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector MuzzleOffset;

	// Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AFPSProjectile> ProjectileClass;
	
	// Called for Shoot input
	void Shoot();

	// Save Data functions
	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();
};
