// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ACPlayerController : public APlayerController
{
	GENERATED_BODY()
public:		
	//called on the server only
	virtual void OnPossess(APawn* NewPawn) override;

	//called on the client and the listening server only
	virtual void AcknowledgePossession(APawn* NewPawn) override;

private:
	UPROPERTY()
	class ACPlayerCharacter* CPlayerCharacter;
};
