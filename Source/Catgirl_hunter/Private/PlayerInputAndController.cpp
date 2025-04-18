#include "PlayerInputAndController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

APlayerInputAndController::APlayerInputAndController()
{
	if (GEngine) {
		if (MoveAction == NULL) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "null action");
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "constructed");
		}
		
	}
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void APlayerInputAndController::BeginPlay()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "begin game");
	}
	// Call the base class  
	Super::BeginPlay();
}

void APlayerInputAndController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MyMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{

		//EnhancedInputComponent->BindAction;
		// Setup events
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &APlayerInputAndController::Move);
	}
}

void APlayerInputAndController::Move() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "pressed");
	}
	return;
}
