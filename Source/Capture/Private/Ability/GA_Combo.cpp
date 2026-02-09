// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GA_Combo.h"

void UGA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Combo Ability Activated!"))
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
