// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "SpriteComponent2D.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXPLOSIVEUNBOXING_API USpriteComponent2D : public UPaperSpriteComponent
{
	GENERATED_BODY()
	
public:
    // Sets default values for this actor's properties
    USpriteComponent2D();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite")
    UPaperSpriteComponent* SpriteComponent;

public:
    // Function to set / update sprite
    //UFUNCTION(BlueprintCallable, Category = "Sprite")
    bool SetSprite(UPaperSprite* NewSprite);
};
