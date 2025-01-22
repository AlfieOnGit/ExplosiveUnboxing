// Fill out your copyright notice in the Description page of Project Settings.


#include "SpriteComponent2D.h"
USpriteComponent2D::USpriteComponent2D()
{
    // Default sprite here
    static ConstructorHelpers::FObjectFinder<UPaperSprite> DefaultSprite(TEXT("/Game/SpriteAssets/SpriteComponents/spritepng_Sprite_1.spritepng_Sprite_1")); // change path
    if (DefaultSprite.Succeeded())
    {
        SetSprite(DefaultSprite.Object);
    }
}

void USpriteComponent2D::OnEventResponse(UPaperSprite* NewSprite)
{
    SetSprite(NewSprite);
}

// Change the sprite
bool USpriteComponent2D::SetSprite(UPaperSprite* NewSprite)
{
    if (NewSprite)
    {
        Super::SetSprite(NewSprite);
        return true;
    }
    return false;
}

/*
void USpriteComponent2D::BindToEvent(CustomEvent* EventTrigger)
{
    if (EventTrigger)
    {
        EventTrigger->OnCustomEventTriggered.AddDynamic(this, &USpriteComponent2D::OnCustomEventResponse);
    }
}
*/