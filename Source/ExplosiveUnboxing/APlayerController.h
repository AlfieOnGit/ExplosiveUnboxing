// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "APlayerController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class EXPLOSIVEUNBOXING_API AAPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	virtual void SetupInputComponent() override;
	void KeyPressed(FKey key);
};
