// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenAI/TOpenAIChatExample.h"

#include "Data/OpenAI/GenOAIChat.h"
#include "Data/OpenAI/GenOAIChatStructs.h"
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

	FGenChatSettings ChatSettings;
	ChatSettings.Model = TEXT("gpt-4o");
	ChatSettings.Messages.Add(FGenChatMessage{
		TEXT("system"),
		TEXT("The conversation has now Ended. Summarize the above conversation in two concise sentences for bookkeeping.")
	});
	ChatSettings.MaxTokens = 16384;

	UGenOAIChat::SendChatRequest(
		ChatSettings,
		FOnChatCompletionResponse::CreateLambda(
			[this/*, OnResponseGenerated*/](const FString& Response, const FString& ErrorMessage, bool bSuccess)
			{
				if (!UTHelper::IsContextStillValid(this))
				{
					return;
				}
				/*if (bSuccess)
				{
					OnResponseGenerated(Response);
				}*/

				
				UE_LOG(LogTemp, Warning, TEXT("Chat response: %s"), *Response);
				
			})
	);
	
}

// Called every frame
void ATOpenAIChatExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

