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
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
			MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
			bIsMenuVisible = false;
		}
	}
	
}

void AInventoryHUD::DisplayMenu()
{
}

void AInventoryHUD::HideMenu()
{
}

void AInventoryHUD::ShowInteractionWidget()
{
}

void AInventoryHUD::HideInteractionWidget()
{
}

void AInventoryHUD::UpdateInteractionWidget(const FInteractableData InteractableData)
{
}


