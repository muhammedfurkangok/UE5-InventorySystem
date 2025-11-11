#pragma once

#include "CoreMinimal.h"
#include "MainMenu.h"
#include "GameFramework/HUD.h"
#include "Interaction/InteractionWidget.h"
#include "Interfaces/InteractionInterface.h"
#include "InventoryHUD.generated.h"


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

protected:
	virtual void BeginPlay() override;
	UPROPERTY();
	UMainMenu* MainMenuWidget;

	UPROPERTY();
	UInteractionWidget* InteractionWidget;
	
};


