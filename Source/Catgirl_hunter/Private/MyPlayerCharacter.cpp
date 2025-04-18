// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Pawn.h"
#include "Materials/Material.h"
#include "PaperCharacter.h"
#include "BaseEnemy.h"
#include "GameScreenUI.h"
#include "Engine/World.h"


AMyPlayerCharacter::AMyPlayerCharacter()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	//transform
	SetActorRotation(FRotator(0.0, 90.0, 0.0));

	//get flipbooks
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> ASSET(TEXT("/Game/sprites/katytest_still.katytest_still"));
	NotMovingFlipbook = ASSET.Object;
	//set flipbook component data
	GetSprite()->SetFlipbook(NotMovingFlipbook);
	
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	//get HUD
	
	//HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//enable collisions and set up collision events
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMyPlayerCharacter::OnCompHit);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);

}

void AMyPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//ABaseEnemy* temp = NewObject<ABaseEnemy>(this);
	//temp->Attack();
}

void AMyPlayerCharacter::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//if (OtherActor->GetClass()->IsChildOf(ABaseEnemy::StaticClass())) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("hit enemy"));
	//}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("hit something"));
	if (!RecentlyHit) {
		DamageCharacter(1);
	}
}

bool AMyPlayerCharacter::DamageCharacter(int damage)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("character damaged"));
		CurrentHealth -= damage;
		HUD->UpdateCharacterHearts(CurrentHealth);
		if (CurrentHealth <= 0) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("character killed"));
		}
		RecentlyHit = true;
		GetWorldTimerManager().SetTimer(RecentlyHitTimerHandle, this, &AMyPlayerCharacter::EndDamageIFrames, 1.0f, false, RecentlyHitDuration);

	return false;
}

void AMyPlayerCharacter::EndDamageIFrames() {
	RecentlyHit = false;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("can be hit again"));
}

