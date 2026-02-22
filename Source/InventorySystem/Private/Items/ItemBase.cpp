// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"
#include "Components/InventoryComponent.h"

UItemBase::UItemBase()
{
}

UItemBase* CreateItemCopy(const UItemBase* ItemToCopy, UObject* NewOuter)
{
	UItemBase* ItemCopy = NewObject<UItemBase>(NewOuter, ItemToCopy->GetClass());

	ItemCopy->ID = ItemToCopy->ID;
	ItemCopy->Quantity = ItemToCopy->Quantity;
	ItemCopy->ItemQuality = ItemToCopy->ItemQuality;
	ItemCopy->ItemType = ItemToCopy->ItemType;
	ItemCopy->ItemTextData = ItemToCopy->ItemTextData;
	ItemCopy->ItemNumericData = ItemToCopy->ItemNumericData;
	ItemCopy->ItemStatistics = ItemToCopy->ItemStatistics;
	ItemCopy->ItemAssetData= ItemToCopy->ItemAssetData;

	return ItemCopy;
}


void UItemBase::SetQuantity(const int32 NewQuantity)
{
	if(NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 1, ItemNumericData.bIsStackable ? ItemNumericData.MaxStackSize : 1);

		if(OwningInventory)
		{
			if(Quantity <= 0)
			{
				OwningInventory->HandleRemoveItem(this);
			}
		}
	}
}

void UItemBase::Use(AInventorySystemCharacter* Character)
{
}
