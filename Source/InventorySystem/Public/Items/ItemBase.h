// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStructs.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UItemBase : public UObject
{
	GENERATED_BODY()

public:

	//Properties&Variables
	// UPROPERTY()
	// UInventoryComponent* OwningInventory;
	
	UPROPERTY(VisibleAnywhere,Category="Item")
	int32 Quantity;
	UPROPERTY(VisibleAnywhere, Category="Item")
	FName ID;
	UPROPERTY(VisibleAnywhere, Category="Item")
	EItemType ItemType;
	UPROPERTY(VisibleAnywhere, Category="Item")
	EItemQuality ItemQuality;
	UPROPERTY(VisibleAnywhere, Category="Item")
	FItemStatistics ItemStatistics;
	UPROPERTY(VisibleAnywhere, Category="Item")
	FItemTextData ItemTextData;
	UPROPERTY(VisibleAnywhere, Category="Item")
	FItemNumericData ItemNumericData;
	UPROPERTY(VisibleAnywhere, Category="Item")
	FItemAssetData ItemAssetData;

	//Functions
	UItemBase();

	UItemBase* CreateItemCopy() const;

	UFUNCTION(Category= "Item")
	FORCEINLINE float GetItemStackWeight() const {return  Quantity * ItemNumericData.Weight; };
	
	UFUNCTION(Category= "Item")
	FORCEINLINE float GetItemSingleWeight() const {return  ItemNumericData.Weight; };
	
	UFUNCTION(Category= "Item")
	FORCEINLINE bool IsFullItemStack() const {return  Quantity == ItemNumericData.MaxStackSize; };
	
	UFUNCTION(Category= "Item")
	void SetQuantatiy(const int32 NewQuantity);
	
	UFUNCTION(Category= "Item")
	virtual void Use(AInventorySystemCharacter* Character);

protected:
	bool operator==(const FName& OtherID) const
	{
		return this->ID == OtherID;
	}
};
