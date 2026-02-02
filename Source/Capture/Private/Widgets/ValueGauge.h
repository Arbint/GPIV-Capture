// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ValueGauge.generated.h"

/**
 * 
 */
UCLASS()
class UValueGauge : public UUserWidget
{
	GENERATED_BODY()
public:
	// the same as the construction script in blueprint.
	virtual void NativePreConstruct() override;

private:	
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* ProgressBar;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ValueText;

	UPROPERTY(EditAnywhere, Category = "Value Guage")
	FLinearColor BarColor;
};
