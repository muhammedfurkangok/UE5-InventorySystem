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
	
	UPROPERTY(VisibleAnywhere,Category="Item Data",meta=(UIMin="1",UIMax="100"))
	int32 Quantity;
	UPROPERTY(EditAnywhere, Category="Item Data")
	FName ID;
	UPROPERTY(EditAnywhere, Category="Item Data")
	EItemType ItemType;
	UPROPERTY(EditAnywhere, Category="Item Data")
	EItemQuality ItemQuality;
	UPROPERTY(EditAnywhere, Category="Item Data")
	FItemStatistics ItemStatistics;
	UPROPERTY(EditAnywhere, Category="Item Data")
	FItemTextData ItemTextData;
	UPROPERTY(EditAnywhere, Category="Item Data")
	FItemNumericData ItemNumericData;
	UPROPERTY(EditAnywhere, Category="Item Data")
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
		return ID == OtherID;
	}
};
