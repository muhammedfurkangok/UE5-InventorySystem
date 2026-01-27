#include "Components/InventoryComponent.h"
#include "Items/ItemBase.h"

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

UItemBase* UInventoryComponent::FindMatchingItem(const TObjectPtr<UItemBase>& ItemIn) const
{
	if (ItemIn)
	{
		if (InventoryContents.Contains(ItemIn))
		{
			return ItemIn;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextItemByID(const TObjectPtr<UItemBase>& ItemIn) const
{
	if (ItemIn)
	{
		if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
		{
			return *Result;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextPartialStack(const TObjectPtr<UItemBase>& ItemIn) const
{
	if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByPredicate(
		[&ItemIn](const UItemBase* InventoryItem)
		{
			return InventoryItem->ID == ItemIn->ID && !InventoryItem->IsFullItemStack();
		})
	)
	{
		return *Result;
	}

	return nullptr;
}

int32 UInventoryComponent::CalculateWeightAddAmount(const TObjectPtr<UItemBase>& ItemIn, const int32 RequestedAddAmount) const
{
	const int32 WeightMaxAddAmount = FMath::FloorToInt((MaxWeightCapacity - InventoryTotalWeight) / ItemIn->GetItemSingleWeight());
	if (WeightMaxAddAmount >= RequestedAddAmount)
	{
		return RequestedAddAmount;
	}
	return WeightMaxAddAmount;
}

int32 UInventoryComponent::CalculateNumberForFullStack(const TObjectPtr<UItemBase>& StackableItem, const int32 RequestedAddAmount) const
{
	const int32 AddAmountToMakeFullStack = StackableItem->ItemNumericData.MaxStackSize - StackableItem->Quantity;
	return FMath::Min(RequestedAddAmount, AddAmountToMakeFullStack);
}

void UInventoryComponent::MergeItems(const TObjectPtr<UItemBase>& TargetItem, const TObjectPtr<UItemBase>& SourceItem)
{
	const int32 AmountToShift = CalculateNumberForFullStack(TargetItem, SourceItem->Quantity);

	if (AmountToShift > 0)
	{
		TargetItem->SetQuantity(TargetItem->Quantity + AmountToShift);
		HandleRemoveItem(SourceItem, AmountToShift, false);
	}
}

void UInventoryComponent::HandleRemoveItem(UItemBase* ItemToRemove, const int32 AmountToRemove, const bool bAdjustWeight)
{
	if (bAdjustWeight)
		InventoryTotalWeight -= ItemToRemove->GetItemStackWeight();

	if (AmountToRemove > 0)
	{
		// adjust the quantity
		ItemToRemove->SetQuantity(ItemToRemove->Quantity - AmountToRemove);

		// if quantity is now 0, the entire item should be removed from the inventory
		if (ItemToRemove->Quantity <= 0)
		{
			InventoryContents.RemoveSingle(ItemToRemove);
		}
	}
	else
	{
		// if amount to remove is 0, assume the item entry should be removed directly
		InventoryContents.RemoveSingle(ItemToRemove);
	}

	InventoryWasUpdated.Broadcast();
}

void UInventoryComponent::SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit)
{
	
	if (InventoryContents.Num() + 1 <= ItemSlotCount)
	{
		HandleRemoveItem(ItemIn, AmountToSplit);
		AddNewItem(ItemIn, AmountToSplit);
	}
}

FItemAddResult UInventoryComponent::HandleNonStackableItems(const TObjectPtr<UItemBase>& InputItem)
{
	return FItemAddResult::AddedNone(FText::FromString("HandleNonStackableItems not yet implemented."));
}

int32 UInventoryComponent::HandleStackableItems(const TObjectPtr<UItemBase>& ItemIn, const int32 RequestedAddAmount)
{


	return 0;
}

FItemAddResult UInventoryComponent::HandleAddItem(const TObjectPtr<UItemBase>& InputItem)
{
	
	return FItemAddResult::AddedNone(FText::FromString("TryAddItem fallthrough error."));
}

void UInventoryComponent::AddNewItem(const TObjectPtr<UItemBase>& Item, const int32 AmountToAdd)
{
	
}
