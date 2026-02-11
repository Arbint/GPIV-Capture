// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GA_Combo.h"
#include "Ability/CGameplayTypes.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "GameplayTagsManager.h"

UGA_Combo::UGA_Combo()
{
	AbilityTags.AddTag(TAG_Combo);
	BlockAbilitiesWithTag.AddTag(TAG_Combo);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!K2_CommitAbility())
	{
		K2_EndAbility();
		return;
	}
	
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = 
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ComboMontage);
		
		PlayComboMontageTask->OnBlendOut.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnInterrupted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCancelled.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCompleted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->ReadyForActivation();

		UAbilityTask_WaitGameplayEvent* WaitComboChangeEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, TAG_Combo_Change, nullptr, false, false);
		WaitComboChangeEvent->EventReceived.AddDynamic(this, &UGA_Combo::HandleComboChange);
		WaitComboChangeEvent->ReadyForActivation();
	}

	BindInputPressedEvent();
}

void UGA_Combo::HandleComboChange(FGameplayEventData EventData)
{
	FGameplayTag EventTag = EventData.EventTag;
	if (EventTag == TAG_Combo_Change_End)
	{
		NextComboName = NAME_None;
		//UE_LOG(LogTemp, Warning, TEXT("Combo is cleared"))
		return;
	}

	TArray<FName> TagNames;
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);
	NextComboName = TagNames.Last();

	//UE_LOG(LogTemp, Warning, TEXT("Next Combo is: %s"), *(NextComboName.ToString()))
}

void UGA_Combo::BindInputPressedEvent()
{
	UAbilityTask_WaitInputPress* WaitInputPress = UAbilityTask_WaitInputPress::WaitInputPress(this, false);
	WaitInputPress->OnPress.AddDynamic(this, &UGA_Combo::HandleComboChangeCommit);
	WaitInputPress->ReadyForActivation();
}

void UGA_Combo::HandleComboChangeCommit(float TimeWaited)
{
	BindInputPressedEvent();

	if (NextComboName == NAME_None)
		return;

	if (UAnimInstance* OwnerAnimInstance = GetOwnerAnimInst())
	{
		OwnerAnimInstance->Montage_SetNextSection(OwnerAnimInstance->Montage_GetCurrentSection(ComboMontage), NextComboName, ComboMontage);
	}
}
