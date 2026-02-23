#pragma once

#include "CoreMinimal.h"
#include "Interfaces/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"


class UItemBase;
class UDataTable;

UCLASS()
class INVENTORYSYSTEM_API APickup : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	APickup();
	void InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity);

	void InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity);

	FORCEINLINE UItemBase* GetItemData() const { return ItemReference; };

	virtual void BeginFocus() override;
	virtual void EndFocus() override;

protected:
	UPROPERTY(VisibleAnywhere, Category="Pickup | Components")
	UStaticMeshComponent* PickUpMesh;
	
	UPROPERTY(EditInstanceOnly, Category="Pickup | Item Database")
	UDataTable* ItemDataTable;
	
	UPROPERTY(EditInstanceOnly, Category="Pickup | Item Database")
	FName DesiredItemID;
	
	UPROPERTY(VisibleAnywhere, Category="Pickup | Item Reference")
	UItemBase* ItemReference;
	
	UPROPERTY(EditInstanceOnly, Category="Pickup | Item Reference")
	int32 ItemQuantity;
	
	UPROPERTY(VisibleInstanceOnly, Category="Pickup | Interaction")
	FInteractableData InstanceInteractableData;
	
	virtual void BeginPlay() override;

	virtual void Interact(AInventorySystemCharacter* PlayerCharacter) override;
	void UpdateInteractableData();

	void TakePickup(const AInventorySystemCharacter* Taker);
};
