#include "MainCharacter.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	/*
	Player2Cont = UGameplayStatics::GetPlayerController(GetWorld(), 1);
	Player2Char = Cast<AMainCharacter>(Player2Cont->GetPawn());
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		Player1Cont = Cast<APlayerController>(Controller);
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player1Cont->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	*/
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacter::Jumping);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);

		// Jumping Player 2
		//EnhancedInputComponent->BindAction(JumpActionPlayer2, ETriggerEvent::Triggered, this, &AMainCharacter::JumpingPlayer2);

		// Moving Player 2
		//EnhancedInputComponent->BindAction(MoveActionPlayer2, ETriggerEvent::Triggered, this, &AMainCharacter::MovePlayer2);
	}
}

void AMainCharacter::Jumping()
{
	Jump();
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMainCharacter::StartTimedPowerUp()
{
	GLog->Log("Power up started!");
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMainCharacter::EndTimedPowerUp, 1.0f, false, 5.0f);
}

void AMainCharacter::EndTimedPowerUp()
{
	GLog->Log("Power up ended...");
}

void AMainCharacter::StartLoopedPowerUp()
{
	GLog->Log("Looped Power up started!");
	GetWorldTimerManager().ClearTimer(LoopedTimerHandle);
	TimedLoopsRemaining = 5;
	GetWorldTimerManager().SetTimer(LoopedTimerHandle, this, &AMainCharacter::EndLoopedPowerUp, 1.0f, true, 1.0f);
}

void AMainCharacter::EndLoopedPowerUp()
{
	GLog->Log(FString::FromInt(TimedLoopsRemaining));
	if (--TimedLoopsRemaining < 0)
	{
		GetWorldTimerManager().ClearTimer(LoopedTimerHandle);
		GLog->Log("Looped Power completed.");
	}
}

/*
void AMainCharacter::JumpingPlayer2()
{
	if (Controller != Player2Cont)
	{
		Player2Char->Jump();
	}
}

void AMainCharacter::MovePlayer2(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != Player2Cont)
	{
		// find out which way is forward
		const FRotator Rotation = Player2Cont->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		Player2Char->AddMovementInput(ForwardDirection, MovementVector.Y);
		Player2Char->AddMovementInput(RightDirection, MovementVector.X);
	}
}
*/

void AMainCharacter::CallCreateLobby()
{
	UWorld* World = GetWorld();
	{
		World->ServerTravel("/Game/Levels/DefaultLevel?listen");
	}
}

void AMainCharacter::CallClientTravel(const FString& Address)
{
	APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}
