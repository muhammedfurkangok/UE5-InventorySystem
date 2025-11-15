#include "UserInterface/InventoryHUD.h"
#include "Blueprint/UserWidget.h"

AInventoryHUD::AInventoryHUD()
{
}

void AInventoryHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		if (MainMenuWidget)
		{
			MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
			MainMenuWidget->AddToViewport(10);
			MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
			bIsMenuVisible = false;
		}
	}

	if (InteractionWidget)
	{
		if (InteractionWidget)
		{
			InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
			InteractionWidget->AddToViewport(-1);
			InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void AInventoryHUD::DisplayMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
		bIsMenuVisible = true;
	}
}

void AInventoryHUD::HideMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		bIsMenuVisible = false;
	}
}

void AInventoryHUD::ShowInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AInventoryHUD::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AInventoryHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if(InteractionWidget)
	{
		 if(InteractionWidget->GetVisibility() == ESlateVisibility::Visible)
		 {
			 // Assuming UInteractionWidget has a method to update its display based on FInteractableData
			 InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		 }

		InteractionWidget->UpdateWidget(InteractableData);
	}
}
