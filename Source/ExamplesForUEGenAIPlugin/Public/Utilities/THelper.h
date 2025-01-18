// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "THelper.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLESFORUEGENAIPLUGIN_API UTHelper : public UObject
{
	GENERATED_BODY()

public:
	static bool IsContextStillValid(TWeakObjectPtr<UObject> ContextObject);
};
