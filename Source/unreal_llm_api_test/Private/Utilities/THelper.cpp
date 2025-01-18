// Fill out your copyright notice in the Description page of Project Settings.


#include "unreal_llm_api_test/Public/Utilities/THelper.h"


bool UTHelper::IsContextStillValid(const TWeakObjectPtr<UObject> ContextObject)
{
	// Null check
	if (!ContextObject.IsValid())
	{
		return false;
	}

	// Unreal validity check
	if (!IsValid(ContextObject.Get()))
	{
		return false;
	}

	// Safely retrieve the world and check if it's a game world
	if (const UWorld* World = ContextObject.Get()->GetWorld())
	{
		return World->IsGameWorld();
	}

	return false; // World is null or not a game world
}