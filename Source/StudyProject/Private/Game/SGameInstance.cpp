// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/SGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SUnrealObjectClass.h"
#include "Example/SFlyable.h"
#include "Example/SPigeon.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"

USGameInstance::USGameInstance()
{
	UE_LOG(LogTemp, Log, TEXT("USGameInstance::USGameInstance() has been called."));
	
	m_Name = TEXT("USGameInstance Class Default Object");

}

void USGameInstance::Init()
{
	Super::Init();
	
	
	
}

void USGameInstance::Shutdown()
{
	Super::Shutdown();
	UE_LOG(LogTemp, Log, TEXT("USGameInstance::Shutdown() has been called."));

}

