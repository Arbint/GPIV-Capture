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

void UCAbilitySystemComponent::GiveInitialAbilities()
{
	if (!GetOwner()->HasAuthority())
		return;

	for (const TSubclassOf<UGameplayAbility>& AbilityClass : Abilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityClass, 0, -1));
	}

	for (const TSubclassOf<UGameplayAbility>& AbilityClass : BasicAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, -1));
	}
}
