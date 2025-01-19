// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorClickedEvent, AActor*, Actor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHostSelected, bool, isHost);

UCLASS()
class EXPLOSIVEUNBOXING_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void XLook(float InputValue);
	void YLook(float InputValue);

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnActorClickedEvent SelectedActor;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHostSelected SelectedHost;

protected:

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Selected;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isSelectHost;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool responseNeeded;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool responseRecieved;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool confirmSelection;

};
