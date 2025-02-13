// Fill out your copyright notice in the Description page of Project Settings.


#include "DeepSeek/TDeepSeekChatExample.h"

#include "Models/DeepSeek/GenDSeekChat.h"
#include "Utilities/THelper.h"
#include "Secure/GenSecureKey.h"
#include "Data/OpenAI/GenOAIChatStructs.h"


// Sets default values
ATDeepSeekChatExample::ATDeepSeekChatExample()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATDeepSeekChatExample::BeginPlay()
{
    Super::BeginPlay();

    
    UE_LOG(LogTemp, Warning, TEXT("DeepSeek Key: %s"), *UGenSecureKey::GetGenerativeAIApiKey(EGenAIOrgs::DeepSeek));


    // ---- DeepSeek Chat Test ----
    FGenDSeekChatSettings ChatSettings;
    ChatSettings.Model = EDeepSeekModels::Chat; // Use deepseek-chat model
    ChatSettings.MaxTokens = 4096;
    ChatSettings.Messages.Add(FGenChatMessage{TEXT("system"), TEXT("You are a helpful assistant.")});
    ChatSettings.Messages.Add(FGenChatMessage{TEXT("user"), TEXT("What is the capital of France?")});

    UGenDSeekChat::SendChatRequest(
        ChatSettings,
        FOnDSeekChatCompletionResponse::CreateLambda(
            [this](const FString& Response, const FString& ErrorMessage, bool bSuccess)
            {
                if (!UTHelper::IsContextStillValid(this))
                {
                    return;
                }

                if (bSuccess)
                {
                    UE_LOG(LogTemp, Warning, TEXT("DeepSeek Chat Response: %s"), *Response);
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("DeepSeek Chat Error: %s"), *ErrorMessage);
                }
            })
    );

    // ---- DeepSeek Reasoning Test ----
    FGenDSeekChatSettings ReasoningSettings;
    ReasoningSettings.Model = EDeepSeekModels::Reasoner; // Use deepseek-reasoner model
    ReasoningSettings.MaxTokens = 8000; // Reasoning model supports up to 8K tokens
    ReasoningSettings.Messages.Add(FGenChatMessage{TEXT("user"), TEXT("9.11 and 9.8, which is greater?")});

    UGenDSeekChat::SendChatRequest(
        ReasoningSettings,
        FOnDSeekChatCompletionResponse::CreateLambda(
            [this](const FString& Response, const FString& ErrorMessage, bool bSuccess)
            {
                if (!UTHelper::IsContextStillValid(this))
                {
                    return;
                }

                if (bSuccess)
                {
                    UE_LOG(LogTemp, Warning, TEXT("DeepSeek Reasoning Response: %s"), *Response);
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("DeepSeek Reasoning Error: %s"), *ErrorMessage);
                }
            })
    );
}


// Called every frame
void ATDeepSeekChatExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

