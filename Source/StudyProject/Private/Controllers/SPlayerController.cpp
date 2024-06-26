// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SPlayerController.h"

ASPlayerController::ASPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAxis(TEXT("LeftRight"), this, &ThisClass::LeftRight);
}

void ASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
}

void ASPlayerController::LeftRight(float InAxisValue)
{
	//UE_LOG(LogTemp, Log, TEXT("ASPlayerController::LeftRight(%.3f)"), InAxisValue);
}

#pragma region TEST
//void ASPlayerController::PostInitializeComponents()
//{
//	UE_LOG(LogTemp, Warning, TEXT("       Start ASPlayerController::PostInitializeComponents()"));
//	Super::PostInitializeComponents();
//	UE_LOG(LogTemp, Warning, TEXT("       End   ASPlayerController::PostInitializeComponents()"));
//}
//
//void ASPlayerController::PlayerTick(float DeltaSeconds)
//{
//	static bool bOnce = false;
//	if (bOnce == false)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("       Start ASPlayerController::PlayerTick()"));
//	}
//	Super::PlayerTick(DeltaSeconds);
//	if (bOnce == false)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("       End   ASPlayerController::PlayerTick()"));
//		bOnce = true;
//	}
//}
//
//void ASPlayerController::SetupInputComponent()
//{
//	UE_LOG(LogTemp, Warning, TEXT("       Start ASPlayerController::SetupInputComponent()"));
//	Super::SetupInputComponent();
//	UE_LOG(LogTemp, Warning, TEXT("       End   ASPlayerController::SetupInputComponent()"));
//}
//
//void ASPlayerController::OnPossess(APawn* aPawn)
//{
//	UE_LOG(LogTemp, Warning, TEXT("       Start ASPlayerController::OnPossess(ASPlayerPawn)"));
//	Super::OnPossess(aPawn);
//	UE_LOG(LogTemp, Warning, TEXT("       End   ASPlayerController::OnPossess(ASPlayerPawn)"));
//}
//
//void ASPlayerController::OnUnPossess()
//{
//	UE_LOG(LogTemp, Warning, TEXT("       Start ASPlayerController::OnUnPossess()"));
//	Super::OnUnPossess();
//	UE_LOG(LogTemp, Warning, TEXT("       End   ASPlayerController::OnUnPossess()"));
//}
//
//void ASPlayerController::BeginPlay()
//{
//	UE_LOG(LogTemp, Warning, TEXT("       Start ASPlayerController::BeginPlay()"));
//	Super::BeginPlay();
//	UE_LOG(LogTemp, Warning, TEXT("       End   ASPlayerController::BeginPlay()"));
//}
//
//void ASPlayerController::EndPlay(EEndPlayReason::Type EndPlayReason)
//{
//	UE_LOG(LogTemp, Warning, TEXT("       Start ASPlayerController::EndPlay()"));
//	Super::EndPlay(EndPlayReason);
//	UE_LOG(LogTemp, Warning, TEXT("       End   ASPlayerController::EndPlay()"));
//}
#pragma endregion