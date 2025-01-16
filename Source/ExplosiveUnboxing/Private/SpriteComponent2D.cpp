// Fill out your copyright notice in the Description page of Project Settings.


#include "SpriteComponent2D.h"
USpriteComponent2D::USpriteComponent2D()
{
    // Default sprite here
    static ConstructorHelpers::FObjectFinder<UPaperSprite> DefaultSprite(TEXT("/Game/Sprites/MyDefaultSprite.MyDefaultSprite")); // change path
    if (DefaultSprite.Succeeded())
    {
        SetSprite(DefaultSprite.Object);
    }
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