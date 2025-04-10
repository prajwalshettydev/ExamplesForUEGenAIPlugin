// Fill out your copyright notice in the Description page of Project Settings.


#include "XAI/TXAIChatExample.h"
#include "Data/XAI/GenXAIChatStructs.h"
#include "Data/GenAIOrgs.h"
#include "Models/XAI/GenXAIChat.h"
#include "Secure/GenSecureKey.h"
#include "Utilities/THelper.h"


// Sets default values
ATXAIChatExample::ATXAIChatExample()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATXAIChatExample::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("XAI Key: %s"), *UGenSecureKey::GetGenerativeAIApiKey(EGenAIOrgs::XAI));

	FGenXAIChatSettings ChatSettings;
	ChatSettings.Model = TEXT("grok-3-latest");
		ChatSettings.Messages.Add(FGenXAIMessage{
		TEXT("system"),
		TEXT("You are a helpful AI assistant for a game. Please provide concise responses.")
	});
	ChatSettings.Messages.Add(FGenXAIMessage{TEXT("user"), TEXT("Create a brief description for a forest level in a fantasy game")});
	ChatSettings.MaxTokens = 1000;

	UGenXAIChat::SendChatRequest(
		ChatSettings,
		FOnXAIChatCompletionResponse::CreateLambda(
			[this](const FString& Response, const FString& ErrorMessage, bool bSuccess)
			{
				if (!UTHelper::IsContextStillValid(this))
				{
					return;
				}
				
				UE_LOG(LogTemp, Warning, TEXT("XAI Chat response: %s"), *Response);
				
				if (!bSuccess)
				{
					UE_LOG(LogTemp, Error, TEXT("XAI Chat error: %s"), *ErrorMessage);
				}
			})
	);
}

// Called every frame
void ATXAIChatExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
