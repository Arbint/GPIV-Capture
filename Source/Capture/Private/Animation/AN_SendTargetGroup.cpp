// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AN_SendTargetGroup.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UAN_SendTargetGroup::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	UAbilitySystemComponent* OwnerAbilitySystemComoponent =
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner());

	if (!OwnerAbilitySystemComoponent)
		return;

	if (TargetSocketNames.Num() < 2)
	{
		UE_LOG(LogTemp, Error, TEXT("Target Group Will not be sent, at least 2 sockets has to be provide!"))
		return;
	}

	FGameplayEventData EventData;
	for (int i = 1; i < TargetSocketNames.Num(); ++i)
	{
		FVector StartLoc = MeshComp->GetSocketLocation(TargetSocketNames[i-1]);
		FVector EndLoc = MeshComp->GetSocketLocation(TargetSocketNames[i]);

		FGameplayAbilityTargetData_LocationInfo* LocationInfo = new FGameplayAbilityTargetData_LocationInfo;
		LocationInfo->SourceLocation.LiteralTransform.SetLocation(StartLoc);
		LocationInfo->TargetLocation.LiteralTransform.SetLocation(EndLoc);
	
		EventData.TargetData.Add(LocationInfo);
	}

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, EventData);
}
