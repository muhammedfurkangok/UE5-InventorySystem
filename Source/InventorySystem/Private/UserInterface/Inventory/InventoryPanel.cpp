// game
#include "UserInterface/Inventory/InventoryPanel.h"
#include "Components/InventoryComponent.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"

// engine
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Items/ItemBase.h"

void UInventoryPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	bIsLinkedToInventory = false;
}



void UInventoryPanel::UnlinkFromInventory()
{
	if (bIsLinkedToInventory)
	{
	
		bIsLinkedToInventory = false;
	}
}

void UInventoryPanel::RefreshInventory()
{
	if (InventoryReference && InventorySlotClass)
	{
		InventoryWrapBox->ClearChildren();

		for (UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
		{
		
			
		}

		SetInfoText();
	}
}

void UInventoryPanel::SetInfoText() const
{
	const FString WeightInfoValue{
		FString::SanitizeFloat(InventoryReference->InventoryTotalWeight) + "/"
		+ FString::SanitizeFloat(InventoryReference->MaxWeightCapacity)
	};

	const FString CapacityInfoValue{
		FString::FromInt(InventoryReference->GetInventoryContents().Num()) + "/"
		+ FString::FromInt(InventoryReference->ItemSlotCount)
	};

	WeightInfo->SetText(FText::FromString(WeightInfoValue));
	CapacityInfo->SetText(FText::FromString(CapacityInfoValue));
}

bool UInventoryPanel::NativeOnDrop(const FGeometry& InGeometry,const FDragDropEvent& InDragDropEvent,UDragDropOperation* InOperation)
{

	return false;
}