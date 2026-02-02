// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/CAbilitySystemComponent.h"

void UCAbilitySystemComponent::ApplyInitialEffects()
{
	if (!GetOwner()->HasAuthority())
		return;

	for (const TSubclassOf<UGameplayEffect>& InitialEffect : InitialEffects)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(InitialEffect, 1, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
	}
}
