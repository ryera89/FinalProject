// Copyright Epic Games, Inc. All Rights Reserved.

#include "FinalProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/Interactable.h"
#include "Stats/HealthComponent.h"
#include "Inventory/Inventory.h"
#include "UI/HUDWidget.h"
#include "UI/InGameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Components/SkeletalMeshComponent.h"
#include "FinalProjectGameMode.h"

//////////////////////////////////////////////////////////////////////////
// AFinalProjectCharacter

AFinalProjectCharacter::AFinalProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.5f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Health Component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	
	InventoryComponent = CreateDefaultSubobject<UInventory>(TEXT("InventoryComponent"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFinalProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AFinalProjectCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AFinalProjectCharacter::StopRunning);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFinalProjectCharacter::Interact);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AFinalProjectCharacter::Attack);
	//PlayerInputComponent->BindAction("Attack", IE_DoubleClick, this, &AFinalProjectCharacter::Attack);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFinalProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFinalProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFinalProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFinalProjectCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFinalProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFinalProjectCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFinalProjectCharacter::OnResetVR);
}


void AFinalProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	//HealthComponent->OnHealthChange.AddUObject()
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (AInGameHUD* HUD = Cast<AInGameHUD>(PlayerController->GetHUD()))
	{
		InteractionHint.BindUObject(HUD, &AInGameHUD::InteractionHint);

		if (HealthComponent != nullptr)
		{
			HealthComponent->OnHealthChange.AddUObject(HUD, &AInGameHUD::UpdatePlayerHealthBar);
			HealthComponent->OnHealthChange.AddUObject(this, &AFinalProjectCharacter::HandleDeath);
		}
			
	}
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AFinalProjectCharacter::HandleDeath(float CurrentHealth, float MaxHealth)
{
	if (CurrentHealth <= 0.0f && !IsDeath)
	{
		IsDeath = true;
		if (DeathAnimation != nullptr)
		{
			
			DisableInput(Cast<APlayerController>(GetController()));
			GetMesh()->PlayAnimation(DeathAnimation, false);
			float DeathAnimDuration = DeathAnimation->GetPlayLength();	
			AFinalProjectGameMode* GameMode = Cast<AFinalProjectGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			/*handle the player death after the death animation ends*/
			if (GameMode != nullptr)
			{
				FTimerHandle timer;
				GetWorld()->GetTimerManager().SetTimer(timer, GameMode, 
					&AFinalProjectGameMode::HandlePlayerDeath, DeathAnimDuration);
				
				APlayerController* PlayerController = Cast<APlayerController>(GetController());
				if (AInGameHUD* HUD = Cast<AInGameHUD>(PlayerController->GetHUD()))
				{
					HUD->ShowGameMessage("You Died", DeathAnimDuration);
				}
			}
			//
			//UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
			//AnimInst->Montage_Play(DeathAnimationMontage);
		}
		
	}
}

void AFinalProjectCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Overlap begins"));

	//remains nullptr if OtherActor doesn't implement the IInteractable interface
	InteractableActor = Cast<IInteractable>(OtherActor);
	if (InteractableActor != nullptr)
	{
		InteractableActor->FocusStart_Implementation();
		//Show Interaction Hint on UI
		InteractionHint.ExecuteIfBound(InteractableActor->InteractionHint_Implementation() + " "
			+ InteractableActor->InteractableObjectName_Implementation(), true);
	}

}

void AFinalProjectCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Overlap ends"));

	if ((InteractableActor != nullptr) && (InteractableActor == Cast<IInteractable>(OtherActor)))
	{
		InteractableActor->FocusEnd_Implementation();
		//Hide interaction hint on UI
		InteractionHint.ExecuteIfBound("", false);
		InteractableActor = nullptr;
	}
}

float AFinalProjectCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!IsDeath)
	{
		if (HealthComponent) HealthComponent->ModifyHealth(-DamageAmount);

		return DamageAmount;
	}
	return 0.f;
}

void AFinalProjectCharacter::OnResetVR()
{
	// If FinalProject is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in FinalProject.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFinalProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AFinalProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AFinalProjectCharacter::Interact()
{
	if (InteractableActor != nullptr) InteractableActor->Interacted_Implementation(this);
		//IInteractable::Execute_Interacted(InteractableActor, this);
}
void AFinalProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFinalProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFinalProjectCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFinalProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
void AFinalProjectCharacter::Run()
{
	bIsSprinting = true;
	bIsWalking = false;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AFinalProjectCharacter::StopRunning()
{
	bIsWalking = true;
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
void AFinalProjectCharacter::Attack()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Attack Method Fired"));
	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (AttackMontage && !AnimInst->Montage_IsPlaying(AttackMontage))
	{
		if (GetCharacterMovement()->IsFalling())
		{
			AnimInst->Montage_Play(AttackMontage, 2.f);
		}
		else
		{
			AnimInst->Montage_Play(AttackMontage, 1.5f);
		}
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Attack Animation Fired"));
	}
}