#include "UserInterface/InventoryHUD.h"
#include "Blueprint/UserWidget.h"



AInventoryHUD::AInventoryHUD()
{
}

void AInventoryHUD::BeginPlay()
{
    Super::BeginPlay();

    // 1. MAIN MENU KONTROLÜ VE OLUŞTURULMASI
    if (MainMenuClass)
    {
        MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
        
        if (MainMenuWidget)
        {
            MainMenuWidget->AddToViewport(10);
            MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
            bIsMenuVisible = false;
        }
    }

    // 2. INTERACTION WIDGET KONTROLÜ VE OLUŞTURULMASI
    if (InteractionWidgetClass)
    {
        InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);

        if (InteractionWidget)
        {
            InteractionWidget->AddToViewport(-1);
            InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

void AInventoryHUD::DisplayMenu()
{
    if (MainMenuWidget)
    {
        bIsMenuVisible = true;
        MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void AInventoryHUD::HideMenu()
{
    if (MainMenuWidget)
    {
        bIsMenuVisible = false;
        MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void AInventoryHUD::ToggleMenu()
{
    if (MainMenuWidget)
    {
        HideMenu();


        const FInputModeGameOnly InputMode;
        GetOwningPlayerController()->SetInputMode(InputMode);
        GetOwningPlayerController()->SetShowMouseCursor(false);
    }
    else
    {
         DisplayMenu();
        const FInputModeGameAndUI InputMode;
        GetOwningPlayerController()->SetInputMode(InputMode);
        GetOwningPlayerController()->SetShowMouseCursor(true);
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
        // DÜZELTME: Burası Visible değil Collapsed olmalıydı.
        InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void AInventoryHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
    if (InteractionWidget)
    {
        if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
        {
            InteractionWidget->SetVisibility(ESlateVisibility::Visible);
        }

        InteractionWidget->UpdateWidget(InteractableData);
    }
}