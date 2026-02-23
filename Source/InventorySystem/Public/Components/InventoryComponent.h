#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);


UENUM(BlueprintType)
enum class EItemAddResult:uint8
{
	IAR_NoItemAdded UMETA(DisplayName="No Item Added"),
	IAR_PartialAmountItemAdded UMETA(DisplayName="Partial Amount of Item Added"),
	IAR_AllItemAdded UMETA(DisplayName="All Items Added")
};

USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_BODY()

	FItemAddResult() : ActualAmountAdded(0),
	OperationResult(EItemAddResult::IAR_NoItemAdded),
	ResultMessage(FText::GetEmpty())
	{};

	UPROPERTY(BlueprintReadOnly, Category= "Item Add Result")
	int32 ActualAmountAdded;
	UPROPERTY(BlueprintReadOnly, Category= "Item Add Result")
	EItemAddResult OperationResult;
	UPROPERTY(BlueprintReadOnly ,Category= "Item Add Result")
	FText ResultMessage;
	
	static FItemAddResult AddedNone(const FText& ErrorText)
	{
		FItemAddResult AddedNoneResult;
		AddedNoneResult.ActualAmountAdded = 0;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_NoItemAdded;
		AddedNoneResult.ResultMessage = ErrorText;
		return AddedNoneResult;
	};
	
	static FItemAddResult AddedPartial(const int32 PartialAmountAdded, const FText& ErrorText)
	{
		FItemAddResult AddedPartialResult;
		AddedPartialResult.ActualAmountAdded = PartialAmountAdded;
		AddedPartialResult.OperationResult = EItemAddResult::IAR_PartialAmountItemAdded;
		AddedPartialResult.ResultMessage = ErrorText;
		return AddedPartialResult;
	};
	
	static FItemAddResult AddedAll(const int32 AmountAdded, const FText& Message)
	{
		FItemAddResult AddedAllResult;
		AddedAllResult.ActualAmountAdded = AmountAdded;
		AddedAllResult.OperationResult = EItemAddResult::IAR_AllItemAdded;
		AddedAllResult.ResultMessage = Message;
		return AddedAllResult;
	};
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	FOnInventoryUpdated InventoryWasUpdated;

	UPROPERTY(VisibleAnywhere, Category="Inventory")
	float InventoryTotalWeight;
	UPROPERTY(EditInstanceOnly, Category="Inventory")
	int32 ItemSlotCount;
	UPROPERTY(EditInstanceOnly, Category="Inventory")
	float MaxWeightCapacity;

	
	UInventoryComponent();

	FItemAddResult HandleAddItem(const TObjectPtr<UItemBase>& InputItem);
	UItemBase* FindMatchingItem(const TObjectPtr<UItemBase>& ItemIn) const;
	UItemBase* FindNextItemByID(const TObjectPtr<UItemBase>& ItemIn) const;
	UItemBase* FindNextPartialStack(const TObjectPtr<UItemBase>& ItemIn) const;
	
	void MergeItems(const TObjectPtr<UItemBase>& TargetItem, const TObjectPtr<UItemBase>& SourceItem);
	void HandleRemoveItem(UItemBase* ItemToRemove, int32 AmountToRemove = 0, const bool bAdjustWeight = true);
	
	void SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit);
	
	FORCEINLINE TArray<UItemBase*> GetInventoryContents() const { return InventoryContents; }


	
	FORCEINLINE void SetSlotsCapacity(const int32 NewSlotsCapacity) { ItemSlotCount = NewSlotsCapacity; }
	FORCEINLINE void SetWeightCapacity(const float NewWeightCapacity) { MaxWeightCapacity = NewWeightCapacity; }

protected:
	UPROPERTY(VisibleAnywhere, Category="Inventory")
	TArray<TObjectPtr<UItemBase>> InventoryContents;

	
	virtual void BeginPlay() override;

	FItemAddResult HandleNonStackableItems(const TObjectPtr<UItemBase>& InputItem);
	int32 HandleStackableItems(const TObjectPtr<UItemBase>& ItemIn, int32 RequestedAddAmount);
	int32 CalculateWeightAddAmount(const TObjectPtr<UItemBase>& ItemIn, int32 RequestedAddAmount) const;
	int32 CalculateNumberForFullStack(const TObjectPtr<UItemBase>& StackableItem, int32 RequestedAddAmount) const;

	void AddNewItem(const TObjectPtr<UItemBase>& Item, const int32 AmountToAdd);
};