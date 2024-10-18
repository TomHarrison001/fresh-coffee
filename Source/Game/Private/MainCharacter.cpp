#include "MainCharacter.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <Kismet/GameplayStatics.h>
#include "ShooterSaveGame.h"
#include "Gun.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	// Create a first person camera component
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// Attach the camera component to our capsule component
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	// Position the camera slightly above the eyes
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// Enable the pawn to control camera rotation
	FPSCameraComponent->bUsePawnControlRotation = true;
	// Create a first person mesh component for the owning player
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);
	// Attach the FPS mesh to the FPS camera
	FPSMesh->SetupAttachment(FPSCameraComponent);
	*/

	// Create a Spring Arm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//Spring Arm Component is attached to Mesh
	SpringArmComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	// Create a Third person camera component.
	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	//Attach CameraComponent as a child of Spring Arm
	TPSCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
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

	/*
	// Disable some environmental shadows to preserve illusion of single mesh
	if (FPSMesh != nullptr)
	{
		FPSMesh->bCastDynamicShadow = false;
		FPSMesh->CastShadow = false;
		FPSMesh->SetOnlyOwnerSee(true); // Only the owning player sees this mesh
	}

	// The owning player doesn't see the regular (third-person) body mesh
	GetMesh()->SetOwnerNoSee(true);
	*/

	if (SpringArmComponent != nullptr)
	{
		//Set Location and Rotation
		SpringArmComponent->SetRelativeLocation(FVector(0.0f, 70.0f, 100.0f));
		SpringArmComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

		// Set how far away from character
		SpringArmComponent->TargetArmLength = 250.0f;
		// Set camera lag behaviour
		SpringArmComponent->bEnableCameraLag = true;
		SpringArmComponent->CameraLagSpeed = 10.0f;
	}

	if (TPSCameraComponent != nullptr)
	{
		// Camera pawn rotation must be enabled to allow player to move camera
		TPSCameraComponent->bUsePawnControlRotation = true;
	}

	//Gun Code
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
	Gun->SetOwner(this);
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

		// Shoot
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AMainCharacter::Shoot);
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

void AMainCharacter::Shoot()
{
	// Attempt to shoot a projectile
	if (ProjectileClass)
	{
		// Get the camera transform
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Set MuzzleOffset to spawn projectiles slightly in front of the camera
		MuzzleOffset.Set(100.0f, 0.0f, 50.0f);

		// Transform MuzzleOffset from camera space to world space
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);


		FRotator MuzzleRotation = CameraRotation;
		// Skew the aim to be slightly upwards if required
		// MuzzleRotation.Pitch += 5.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

void AMainCharacter::SaveGame()
{
	UShooterSaveGame* SaveGameInstance = Cast<UShooterSaveGame>(UGameplayStatics::CreateSaveGameObject(UShooterSaveGame::StaticClass()));

	SaveGameInstance->WorldLocation = GetActorLocation();
	SaveGameInstance->WorldRotation = GetActorRotation();

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SlotName, SaveGameInstance->SlotIndex);
}

void AMainCharacter::LoadGame()
{
	UShooterSaveGame* LoadGameInstance = Cast<UShooterSaveGame>(UGameplayStatics::CreateSaveGameObject(UShooterSaveGame::StaticClass()));

	LoadGameInstance = Cast<UShooterSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SlotName, LoadGameInstance->SlotIndex));

	SetActorLocation(LoadGameInstance->WorldLocation);
	SetActorRotation(LoadGameInstance->WorldRotation);
}
