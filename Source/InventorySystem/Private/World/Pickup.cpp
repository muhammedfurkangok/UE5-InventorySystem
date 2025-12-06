#include "World/Pickup.h"

#include "Items/ItemBase.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickUp Mesh");
	PickUpMesh->SetSimulatePhysics(true);
	SetRootComponent(PickUpMesh);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup(UItemBase::StaticClass(), ItemQuantity);
}


void APickup::InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{
}

void APickup::InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
}

void APickup::BeginFocus()
{
}

void APickup::EndFocus()
{
}

void APickup::Interact(AInventorySystemCharacter* PlayerCharacter)
{
}

void APickup::TakePickup(const AInventorySystemCharacter* Taker)
{
}
