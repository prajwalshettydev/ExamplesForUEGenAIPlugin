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


    /* Timeout warning for reasoning models:
     * DeepSeek reasoning models can take a long time to respond, especially when the input is complex.
     * Unreal has a default timeout of 30 seconds for HTTP requests, which may not be enough for reasoning models.
     * Just simply overriding it with a higher value may not work as expected, as Unreal may still cancel the request.
     * So we need to update the timeout in the Engine settings, using default engine ini file.
     * */
    

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
    ReasoningSettings.Model = EDeepSeekModels::Reasoner;
    ReasoningSettings.MaxTokens = 100;
    ReasoningSettings.Messages.Add(FGenChatMessage{TEXT("system"), TEXT("You are a helpful assistant.")});
    ReasoningSettings.Messages.Add(FGenChatMessage{TEXT("user"), TEXT("9.11 and 9.8, which is greater?")});
    ReasoningSettings.bStreamResponse = false;

    // Add some debugging logs
    UE_LOG(LogTemp, Warning, TEXT("Sending DeepSeek Reasoning Request"));

    UGenDSeekChat::SendChatRequest(
        ReasoningSettings,
        FOnDSeekChatCompletionResponse::CreateLambda(
            [this](const FString& Response, const FString& ErrorMessage, bool bSuccess)
            {
                if (!UTHelper::IsContextStillValid(this))
                {
                    return;
                }

                // Log response details regardless of success
                UE_LOG(LogTemp, Warning, TEXT("DeepSeek Reasoning Response Received - Success: %d"), bSuccess);
                UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response);
                if (!ErrorMessage.IsEmpty())
                {
                    UE_LOG(LogTemp, Error, TEXT("Error Message: %s"), *ErrorMessage);
                }
            })
    );
}


// Called every frame
void ATDeepSeekChatExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

