// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExamplesForUEGenAIPluginGameMode.generated.h"

UCLASS(minimalapi)
class AExamplesForUEGenAIPluginGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AExamplesForUEGenAIPluginGameMode();
	void OnChatCompletion(const FString& ResponseContent, const FString& ErrorMessage, bool bSuccess);
};



