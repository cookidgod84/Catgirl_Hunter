// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"


// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	movementcomponent = CreateDefaultSubobject<UBaseEnemyMovementComponent>(TEXT("BaseEnemyMoveComponent"));
	movementcomponent->UpdatedComponent = RootComponent;
	
	collisioncomponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseEnemtCollisionComponent"));
	collisioncomponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	collisioncomponent->SetNotifyRigidBodyCollision(true);
	collisioncomponent->SetSphereRadius(10);
	
	flipbookcomponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("BaseEnemyFlipbookComponent"));
	flipbookcomponent->AttachToComponent(collisioncomponent, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Move(DeltaTime);
}

UPawnMovementComponent* ABaseEnemy::GetMovementComponent() const
{
	return movementcomponent;
}

void ABaseEnemy::SetEnemyData(FEnemyDataStruct* data)
{
	UE_LOG(LogTemp, Warning, TEXT("we setting up"));
	FString name = data->move_flipbook->GetName();
	enemydata = *data;
	flipbookcomponent->SetFlipbook(data->move_flipbook);
}

void ABaseEnemy::Move(float DeltaTime)
{
	FVector characterposition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector movementvector = characterposition - Super::GetActorLocation();
	movementvector.Normalize(0.001);
	movementvector = movementvector * enemydata.base_speed / 10;
	movementcomponent->AddInputVector(movementvector, false);
}

void ABaseEnemy::Attack()
{
}

void ABaseEnemy::Die()
{
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void UBaseEnemyMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 300.0f;
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we bumped into something, try to slide along it
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
}

