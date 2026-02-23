#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"


class AInventorySystemCharacter;

UENUM()
enum EInteractableType : uint8
{
	Pickup UMETA(DisplayName = "Pickup"),
	NonPlayerCharacter UMETA(DisplayName = "NPC"),
	Device UMETA(DisplayName = "Device"),
	Toggle UMETA(DisplayName = "Toggle"),
	Container UMETA(DisplayName = "Container"),
};

USTRUCT()
struct FInteractableData
{
	GENERATED_BODY()

	FInteractableData() : InteractableType(EInteractableType::Pickup),
	NameText(FText::FromString("Default Item")),
	ActionText(FText::FromString("Pick Up")),
	Quantity(1),
	InteractionDuration(1.0f) {};
	
	UPROPERTY(EditInstanceOnly)
	TEnumAsByte<EInteractableType> InteractableType;

	UPROPERTY(EditInstanceOnly)
	FText NameText;
	
	UPROPERTY(EditInstanceOnly)
	FText ActionText;

	UPROPERTY(EditInstanceOnly)
	int8 Quantity;
	UPROPERTY(EditInstanceOnly)
	float InteractionDuration;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORYSYSTEM_API IInteractionInterface
{
	GENERATED_BODY()

public:
	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteract();
	virtual void EndInteract();
	virtual auto Interact(AInventorySystemCharacter* PlayerCharacter) -> void;

	FInteractableData InteractableData;
};
