// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "SwordSlashAbility.h"
#include "MyHUD.h"
#include "MyPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CATGIRL_HUNTER_API AMyPlayerCharacter : public APaperCharacter
{
	GENERATED_BODY()
	public:
		AMyPlayerCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	bool DamageCharacter(int damage);

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private: 
	void EndDamageIFrames();
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	TMap<FString, UPaperFlipbookComponent*> characterabilities;

	class AMyHUD* HUD;

	UPaperFlipbook* NotMovingFlipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = stats, meta = (AllowPrivateAccess = "true"))
	int MaxHealth = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = stats, meta = (AllowPrivateAccess = "true"))
	int CurrentHealth = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = state, meta = (AllowPrivateAccess = "true"))
	bool RecentlyHit = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = state, meta = (AllowPrivateAccess = "true"))
	float RecentlyHitDuration = 2.0; //seconds until character can be hit again

	FTimerHandle RecentlyHitTimerHandle;
};
