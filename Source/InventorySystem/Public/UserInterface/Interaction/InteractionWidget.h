// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class AInventorySystemCharacter;
struct FInteractableData;
class UTextBlock;
class UProgressBar;

UCLASS()
class INVENTORYSYSTEM_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category="Ineraction Widget | Player Reference")
	AInventorySystemCharacter* PlayerCharacter;

	void UpdateWidget(const FInteractableData* InteractableData);

protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="Ineteraction Widget | Interactable Data")
	UTextBlock* NameText;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="Ineteraction Widget | Interactable Data")
	UTextBlock* ActionText;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="Ineteraction Widget | Interactable Data")
	UTextBlock* QuantityText;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="Ineteraction Widget | Interactable Data")
	UTextBlock* KeyPressText;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="Ineteraction Widget | Interactable Data")
	UProgressBar* InteractionProgressBar;

	float CurrentInteractionDuration;

	UFUNCTION(Category="Interaction Widget | Interactable Data")
	float UpdateInteractionProgress();

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
};
