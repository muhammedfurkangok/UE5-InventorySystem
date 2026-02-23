#pragma once

#include "CoreMinimal.h"
#include "Components/InventoryComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractionInterface.h"
#include "Logging/LogMacros.h"
#include "InventorySystemCharacter.generated.h"

class AInventoryHUD;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

	FInteractionData() : CurrentInteractable( nullptr ),LastInteractionChecekTime( 0.0f )
	{
		
	};

	UPROPERTY()
	AActor* CurrentInteractable;
UPROPERTY()
	float LastInteractionChecekTime;
};


UCLASS(config=Game)
class AInventorySystemCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY()
	AInventoryHUD* InventoryHUD;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Interact Input Action */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AInventorySystemCharacter();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); }

	FORCEINLINE UInventoryComponent* GetInventory() const { return PlayerInventory; }
	FORCEINLINE AInventoryHUD* GetHUD() const { return InventoryHUD; }

	void UpdateInteractionWidget() const;

	void DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop );

	UPROPERTY(VisibleAnywhere,Category="Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	UPROPERTY(VisibleAnywhere,Category="Character | Inventory")
	UInventoryComponent* PlayerInventory;

	float InteractionCheckFrequency;

	float InteractionCheckDistance;

	FTimerHandle TimerHandle_Interaction;

	FInteractionData InteractionData;

	void ToggleMeun();

	void Aim();
	void StopAiming();

	UFUNCTION()
	void UpdateCameraTimeline(const float TimelineValue) const;

	UFUNCTION()
	void CameraTimelineEnd() const;
	
	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteraction();
	void EndInteraction();
	void Interact();

	
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();
};
