#include "World/Pickup.h"

#include "Items/ItemBase.h"
#include "Player/InventorySystemCharacter.h"
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

		InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);

		PickUpMesh->SetStaticMesh(ItemData->ItemAssetData.Mesh);
	}
	
}

void APickup::InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
	ItemReference = ItemToDrop;
	InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);
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
	if (!IsPendingKillPending())
	{
		if (ItemReference)
		{
			if (UInventoryComponent* PlayerInventory = Taker->GetPlayerInventory())
			{
				const FItemAddResult AddResult = PlayerInventory->HandleAddItem(ItemReference);

				switch (AddResult.OperationResult)
				{
				case EItemAddResult::IAR_NoItemAdded:
					break;
				case EItemAddResult::IAR_PartialAmountItemAdded:
					UpdateInteractableData();
					Taker->UpdateInteractionWidget();
					break;
				case EItemAddResult::IAR_AllItemAdded:
					Destroy();
					break;
				default:
					break;
				}

				UE_LOG(LogTemp, Warning, TEXT("%s"), *AddResult.ResultMessage.ToString());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Player inventory component is null!"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup internal item reference was somehow null!"));
		}
	}
}
