// Fill out your copyright notice in the Description page of Project Settings.


#include "Anthropic/TClaudeChatExample.h"

#include "Models/Anthropic/GenClaudeChat.h"
#include "Utilities/THelper.h"
#include "Data/GenAIOrgs.h"
#include "Secure/GenSecureKey.h"
#include "Data/OpenAI/GenOAIChatStructs.h"


// Sets default values
ATClaudeChatExample::ATClaudeChatExample()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATClaudeChatExample::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Anthropic Key: %s"), *UGenSecureKey::GetGenerativeAIApiKey(EGenAIOrgs::Anthropic));

    // ---- Claude Chat Test ----
    FGenClaudeChatSettings ChatSettings;
    ChatSettings.Model = EClaudeModels::Claude_3_7_Sonnet; // Use Claude 3.7 Sonnet model
    ChatSettings.MaxTokens = 4096;
    ChatSettings.Temperature = 0.7f;
    ChatSettings.Messages.Add(FGenChatMessage{TEXT("system"), TEXT("You are a helpful assistant.")});
    ChatSettings.Messages.Add(FGenChatMessage{TEXT("user"), TEXT("What is the capital of France?")});
    
    UGenClaudeChat::SendChatRequest(
        ChatSettings,
        FOnClaudeChatCompletionResponse::CreateLambda(
            [this](const FString& Response, const FString& ErrorMessage, bool bSuccess)
            {
                if (!UTHelper::IsContextStillValid(this))
                {
                    return;
                }
    
                if (bSuccess)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Claude Chat Response: %s"), *Response);
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Claude Chat Error: %s"), *ErrorMessage);
                }
            })
    );

    // ---- Claude Creative Writing Test ----
    FGenClaudeChatSettings CreativeSettings;
    CreativeSettings.Model = EClaudeModels::Claude_3_Opus;
    CreativeSettings.MaxTokens = 1000;
    CreativeSettings.Temperature = 1.0f;
    CreativeSettings.Messages.Add(FGenChatMessage{TEXT("system"), TEXT("You are a creative writing assistant.")});
    CreativeSettings.Messages.Add(FGenChatMessage{TEXT("user"), TEXT("Write a short story about an AI that becomes sentient.")});
    CreativeSettings.bStreamResponse = false;

    // Add some debugging logs
    UE_LOG(LogTemp, Warning, TEXT("Sending Claude Creative Writing Request"));

    UGenClaudeChat::SendChatRequest(
        CreativeSettings,
        FOnClaudeChatCompletionResponse::CreateLambda(
            [this](const FString& Response, const FString& ErrorMessage, bool bSuccess)
            {
                if (!UTHelper::IsContextStillValid(this))
                {
                    return;
                }

                // Log response details regardless of success
                UE_LOG(LogTemp, Warning, TEXT("Claude Creative Response Received - Success: %d"), bSuccess);
                UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response);
                if (!ErrorMessage.IsEmpty())
                {
                    UE_LOG(LogTemp, Error, TEXT("Error Message: %s"), *ErrorMessage);
                }
            })
    );
}

// Called every frame
void ATClaudeChatExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}