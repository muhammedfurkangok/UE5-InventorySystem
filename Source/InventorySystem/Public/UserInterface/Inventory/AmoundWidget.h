#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

DECLARE_DELEGATE_OneParam(FOnValueConfirm, int32)

class UItemBase;
class UButton;
class UTextBlock;


UCLASS()
class CSTUTORIAL_API UAmountWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	FOnValueConfirm OnValueConfirm;


	FORCEINLINE void SetItemReference(UItemBase* ItemIn) { ItemReference = ItemIn; };
	FORCEINLINE void SetHeaderText(const FText& InputText) const;

protected:
	
	int32 AmountValue;

	UPROPERTY()
	TObjectPtr<UItemBase> ItemReference;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HeaderText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Minus5Button;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Minus1Button;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Plus1Button;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Plus5Button;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AmountText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CancelButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;


	UFUNCTION()
	void Minus5Clicked();
	UFUNCTION()
	void Minus1Clicked();
	UFUNCTION()
	void Plus1Clicked();
	UFUNCTION()
	void Plus5Clicked();
	UFUNCTION()
	void ConfirmClicked();
	UFUNCTION()
	void CancelClicked();

	void CloseAmountWidget();


	virtual void NativeOnInitialized() override;

};