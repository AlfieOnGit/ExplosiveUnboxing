// Fill out your copyright notice in the Description page of Project Settings.


#include "APlayerController.h"

void AAPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*
	if (WasInputKeyJustPressed(EKeys::AnyKey)) {
		UE_LOG(LogTemp, Display, TEXT("Test"));
	}*/

	InputComponent->BindAction("My Action", EInputEvent::IE_Pressed, this, AAPlayerController::KeyPressed);
}

void AAPlayerController::KeyPressed(FKey key)
{
	if (key == "N") {
		UE_LOG(LogTemp, Display, TEXT("Test"));
	}
	// Add code for calls or reading of keys here
}