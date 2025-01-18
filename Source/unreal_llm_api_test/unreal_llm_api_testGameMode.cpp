// Copyright Epic Games, Inc. All Rights Reserved.

#include "unreal_llm_api_testGameMode.h"

#include "GenSecureKey.h"
#include "UObject/ConstructorHelpers.h"

Aunreal_llm_api_testGameMode::Aunreal_llm_api_testGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	// Get the API key from the plugin
	FString ApiKey = UGenSecureKey::GetGenerativeAIApiKey();
	
	// Display the API key if everything is successful
	if (GEngine)
	{
		FString DisplayMessage = FString::Printf(TEXT("Generative AI API Key: %s"), *ApiKey);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, DisplayMessage);
	}

}

void Aunreal_llm_api_testGameMode::OnChatCompletion(const FString& ResponseContent, const FString& ErrorMessage, bool bSuccess)
{
	if (bSuccess)
	{
		// Display the AI response if successful
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("AI Response: %s"), *ResponseContent));
		}
	}
	else
	{
		// Display the error message if failed
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: %s"), *ErrorMessage));
		}
	}
}