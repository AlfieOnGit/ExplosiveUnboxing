// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Selected = nullptr;
	test1 = 1.0f;
	responseNeeded = false;
	responseRecieved = false;
	confirmSelection = NULL;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (responseNeeded && responseRecieved) {
		SelectedActor.Broadcast(Selected);
		responseNeeded = false;
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("InputYaw", this, &APlayerCharacter::XLook);
	PlayerInputComponent->BindAxis("InputPitch", this, &APlayerCharacter::YLook);
}
void APlayerCharacter::XLook(float InputValue) 
{
	AddControllerYawInput(InputValue);
}
void APlayerCharacter::YLook(float InputValue)
{
	AddControllerPitchInput(InputValue);
}

