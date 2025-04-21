// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenAI/TOpenAIChatExample.h"
#include "Data/OpenAI/GenOAIChatStructs.h"
#include "Data/GenAIOrgs.h"
#include "Models/OpenAI/GenOAIChat.h"
#include "Secure/GenSecureKey.h"
#include "Utilities/THelper.h"


// Sets default values
ATOpenAIChatExample::ATOpenAIChatExample()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATOpenAIChatExample::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("OpenAI Key: %s"), *UGenSecureKey::GetGenerativeAIApiKey(EGenAIOrgs::OpenAI));

	FGenChatSettings ChatSettings;
	
	// Using the enum instead of directly setting the model string
	ChatSettings.ModelEnum = EGenOAIChatModel::GPT_4O_Mini;
	// The UpdateModel() function will be called inside MakeRequest
	
	ChatSettings.Messages.Add(FGenChatMessage{
		TEXT("system"),
		TEXT("You are a helpful AI assistant. Please respond briefly and clearly.")
	});
	ChatSettings.Messages.Add(FGenChatMessage{TEXT("user"), TEXT("What are the latest OpenAI models available and their differences?")});
	ChatSettings.MaxTokens = 1024;

	// First example using gpt-4o-mini
	UGenOAIChat::SendChatRequest(
		ChatSettings,
		FOnChatCompletionResponse::CreateLambda(
			[this](const FString& Response, const FString& ErrorMessage, bool bSuccess)
			{
				if (!UTHelper::IsContextStillValid(this))
				{
					return;
				}
				
				UE_LOG(LogTemp, Warning, TEXT("GPT-4o-mini response: %s"), *Response);
				
				// Now test the GPT-4.1-mini model after receiving the first response
				TestGPT41Mini();
			})
	);
}

void ATOpenAIChatExample::TestGPT41Mini()
{
	FGenChatSettings ChatSettings;
	ChatSettings.ModelEnum = EGenOAIChatModel::GPT_4_1_Mini;
	
	ChatSettings.Messages.Add(FGenChatMessage{
		TEXT("system"),
		TEXT("You are a helpful AI assistant. Keep responses very concise.")
	});
	ChatSettings.Messages.Add(FGenChatMessage{TEXT("user"), TEXT("What's special about the GPT-4.1 series of models?")});
	ChatSettings.MaxTokens = 1024;

	UGenOAIChat::SendChatRequest(
		ChatSettings,
		FOnChatCompletionResponse::CreateLambda(
			[this](const FString& Response, const FString& ErrorMessage, bool bSuccess)
			{
				if (!UTHelper::IsContextStillValid(this))
				{
					return;
				}
				
				UE_LOG(LogTemp, Warning, TEXT("GPT-4.1-mini response: %s"), *Response);
				
				// Now test the GPT-4.1-nano model
				TestGPT41Nano();
			})
	);
}

void ATOpenAIChatExample::TestGPT41Nano()
{
	FGenChatSettings ChatSettings;
	ChatSettings.ModelEnum = EGenOAIChatModel::GPT_4_1_Nano;
	
	ChatSettings.Messages.Add(FGenChatMessage{
		TEXT("system"),
		TEXT("You are a helpful AI assistant.")
	});
	ChatSettings.Messages.Add(FGenChatMessage{TEXT("user"), TEXT("Compare GPT-4.1-nano to GPT-4o-mini in terms of performance and capabilities.")});
	ChatSettings.MaxTokens = 1024;

	UGenOAIChat::SendChatRequest(
		ChatSettings,
		FOnChatCompletionResponse::CreateLambda(
			[this](const FString& Response, const FString& ErrorMessage, bool bSuccess)
			{
				if (!UTHelper::IsContextStillValid(this))
				{
					return;
				}
				
				UE_LOG(LogTemp, Warning, TEXT("GPT-4.1-nano response: %s"), *Response);

				TestGPTO4Mini();
			})
	);
}

void ATOpenAIChatExample::TestGPTO4Mini()
{
	FGenChatSettings ChatSettings;
	ChatSettings.ModelEnum = EGenOAIChatModel::O4_Mini;
	
	ChatSettings.Messages.Add(FGenChatMessage{
		TEXT("system"),
		TEXT("You are a helpful AI assistant.")
	});
	ChatSettings.Messages.Add(FGenChatMessage{TEXT("user"), TEXT("What are the key differences between GPT-o4 and GPT-o4-mini?")});
	ChatSettings.MaxTokens = 1024;

	UGenOAIChat::SendChatRequest(
		ChatSettings,
		FOnChatCompletionResponse::CreateLambda(
			[this](const FString& Response, const FString& ErrorMessage, bool bSuccess)
			{
				if (!UTHelper::IsContextStillValid(this))
				{
					return;
				}

				TestO3();
				
				UE_LOG(LogTemp, Warning, TEXT("GPT-O4 response: %s"), *Response);
			})
	);
}

void ATOpenAIChatExample::TestO3()
{
	FGenChatSettings ChatSettings;
	ChatSettings.ModelEnum = EGenOAIChatModel::O3;
	
	ChatSettings.Messages.Add(FGenChatMessage{
		TEXT("system"),
		TEXT("You are a helpful AI assistant.")
	});
	ChatSettings.Messages.Add(FGenChatMessage{TEXT("user"), TEXT("What are the key differences between GPT-o4 and O3?")});
	ChatSettings.MaxTokens = 1024;

	UGenOAIChat::SendChatRequest(
		ChatSettings,
		FOnChatCompletionResponse::CreateLambda(
			[this](const FString& Response, const FString& ErrorMessage, bool bSuccess)
			{
				if (!UTHelper::IsContextStillValid(this))
				{
					return;
				}
				
				UE_LOG(LogTemp, Warning, TEXT("O3 response: %s"), *Response);
			})
	);
}

// Called every frame
void ATOpenAIChatExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
