// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"


UCLASS()
class INVENTORYSYSTEM_API APickup : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	

protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
