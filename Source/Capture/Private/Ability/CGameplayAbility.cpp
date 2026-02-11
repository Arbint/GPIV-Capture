// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/CGameplayAbility.h"
#include "Components/SkeletalMeshComponent.h"

UAnimInstance* UCGameplayAbility::GetOwnerAnimInst() const
{
	USkeletalMeshComponent* OwnerSkeletalMesh = GetOwningComponentFromActorInfo();
	if (!OwnerSkeletalMesh)
		return nullptr;

	return OwnerSkeletalMesh->GetAnimInstance();
}
