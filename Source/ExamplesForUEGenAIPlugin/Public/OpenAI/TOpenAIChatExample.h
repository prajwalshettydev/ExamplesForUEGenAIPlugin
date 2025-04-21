// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TOpenAIChatExample.generated.h"

UCLASS()
class EXAMPLESFORUEGENAIPLUGIN_API ATOpenAIChatExample : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATOpenAIChatExample();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Methods to test different models
	void TestGPT41Mini();
	void TestGPT41Nano();
	void TestGPTO4Mini();
	void TestO3();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
