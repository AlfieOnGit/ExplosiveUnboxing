// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);  //place found code for keypress had no passed in variable to Setup
	InputComponent->BindAction("My Action", EInputEvent::IE_Pressed, this, APlayerPawn::KeyPressed);
}

void APlayerPawn::KeyPressed(FKey key)
{
	if (key == "N") {
		UE_LOG(LogTemp, Display, TEXT("Test"));
	}
	// Add code for calls or reading of keys here
}