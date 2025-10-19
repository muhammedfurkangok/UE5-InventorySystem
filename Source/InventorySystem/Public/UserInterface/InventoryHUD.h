#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Interfaces/InteractionInterface.h"
#include "InventoryHUD.generated.h"

class UInteractionWidget;
class UMainMenu;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AInventoryHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	bool bIsMenuVisible;

	AInventoryHUD();

	void DisplayMenu();
	void HideMenu();

	void ShowInteractionWidget();
	void HideInteractionWidget();
	void UpdateInteractionWidget(const FInteractableData InteractableData);

	UPROPERTY();
	UMainMenu* MainMenuWidget;

	UPROPERTY();
	UInteractionWidget* InteractionWidget;
	
	void BeginPlay() override;
};


