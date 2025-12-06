#include "World/Pickup.h"

#include "Items/ItemBase.h"
#include "UserInterface/Inventory/InventoryPanel.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickUp Mesh");
	PickUpMesh->SetSimulatePhysics(true);
	SetRootComponent(PickUpMesh);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup(UItemBase::StaticClass(), ItemQuantity);
}


void APickup::InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{
	if(ItemDataTable && !DesiredItemID.IsNone())
	{
		const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID,DesiredItemID.ToString());

		ItemReference = NewObject<UItemBase>(this,BaseClass);

		ItemReference->ID = ItemData->ID;
		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->ItemQuality = ItemData->ItemQuality;
		ItemReference->ItemNumericData = ItemData->ItemNumericData;
		ItemReference->ItemTextData = ItemData->ItemTextData;
		ItemReference->ItemAssetData = ItemData->ItemAssetData;

		InQuantity <= 0 ? ItemReference->SetQuantatiy(1) : ItemReference->SetQuantatiy(InQuantity);

		PickUpMesh->SetStaticMesh(ItemData->ItemAssetData.Mesh);
	}
	
}

void APickup::InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
	ItemReference = ItemToDrop;
	InQuantity <= 0 ? ItemReference->SetQuantatiy(1) : ItemReference->SetQuantatiy(InQuantity);
	ItemReference->ItemNumericData.Weight = ItemToDrop->GetItemSingleWeight();
	PickUpMesh->SetStaticMesh(ItemToDrop->ItemAssetData.Mesh);

	UpdateInteractableData();
	
}

void APickup::UpdateInteractableData()
{
  InstanceInteractableData.InteractableType = EInteractableType::Pickup;
	InstanceInteractableData.ActionText =ItemReference->ItemTextData.InteractionText;
	InstanceInteractableData.NameText = ItemReference->ItemTextData.ItemName;
	InstanceInteractableData.Quantity = ItemReference->Quantity;
	InteractableData = InstanceInteractableData;
}

void APickup::BeginFocus()
{

	if(PickUpMesh)
	{
		PickUpMesh->SetRenderCustomDepth(true);
	}
}

void APickup::EndFocus()
{
 	if(PickUpMesh)
	{
		PickUpMesh->SetRenderCustomDepth(false);
	}
	
}

void APickup::Interact(AInventorySystemCharacter* PlayerCharacter)
{
	if(PlayerCharacter)
	{
		TakePickup(PlayerCharacter);
	}
	
}


void APickup::TakePickup(const AInventorySystemCharacter* Taker)
{
	if(IsPendingKillEnabled())
	{
		if(ItemReference)
		{
			// if(UInventoryComponent* )
		}
	}
}
