// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SPlayerPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ASPlayerPawn::ASPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	float CharacterHalfHeight = 95.f;
	float CharacterRadius = 40.f;

#pragma region InitializeCapsuleComponent
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetCapsuleHalfHeight(CharacterHalfHeight);
	CapsuleComponent->SetCapsuleRadius(CharacterRadius);
#pragma endregion

#pragma region InitializeSkeletalMesh
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	FVector PivotPosition(0.f, 0.f, -CharacterHalfHeight);
	FRotator PivotRotation(0.f, -90.f, 0.f);
	SkeletalMeshComponent->SetRelativeLocationAndRotation(PivotPosition, PivotRotation);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/KwangAlbino.KwangAlbino'"));
	if (SkeletalMesh.Succeeded() == true)
	{
		SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassInfo(TEXT("/Script/Engine.AnimBlueprint'/Game/StudyProject/Animations/AnimationBlueprints/ABP_PlayerPawn.ABP_PlayerPawn_C'"));
	if (AnimInstanceClassInfo.Succeeded() == true)
	{
		SkeletalMeshComponent->SetAnimClass(AnimInstanceClassInfo.Class);
	}
#pragma endregion

#pragma region InitializeCamera
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
#pragma endregion

	FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovementComponent"));
}

void ASPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ThisClass::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ThisClass::LeftRight);
}

void ASPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ASPlayerPawn::UpDown(float InAxisValue)
{
	AddMovementInput(GetActorForwardVector(), InAxisValue);
}

void ASPlayerPawn::LeftRight(float InAxisValue)
{
	AddMovementInput(GetActorRightVector(), InAxisValue);
}

#pragma region TEST
//void ASPlayerPawn::PostInitializeComponents()
//{
//    UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      PostInitializeComponents()"));
//    Super::PostInitializeComponents();
//    UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      PostInitializeComponents()"));
//}
//
//void ASPlayerPawn::PossessedBy(AController* NewController)
//{
//    UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      PossessedBy(ASPlayerController)"));
//    Super::PossessedBy(NewController);
//    UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      PossessedBy(ASPlayerController)"));
//}
//
//void ASPlayerPawn::UnPossessed()
//{
//    UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      UnPossessed()"));
//    Super::UnPossessed();
//    UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      UnPossessed()"));
//}
//
//void ASPlayerPawn::Tick(float DeltaSeconds)
//{
//    static bool bOnce = false;
//    if (false == bOnce)
//    {
//        UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      Tick()"));
//    }
//    Super::Tick(DeltaSeconds);
//    if (false == bOnce)
//    {
//        UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      Tick()"));
//        bOnce = true;
//    }
//}
//
//void ASPlayerPawn::EndPlay(EEndPlayReason::Type EndPlayReason)
//{
//    UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      EndPlay()"));
//    Super::EndPlay(EndPlayReason);
//    UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      EndPlay()"));
//}
//
//void ASPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//    UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      SetupPlayerInputComponent(PlayerInputComponent)"));
//    Super::SetupPlayerInputComponent(PlayerInputComponent);
//    UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      SetupPlayerInputComponent(PlayerInputComponent)"));
//}
//
//void ASPlayerPawn::BeginPlay()
//{
//    UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      BeginPlay()"));
//    Super::BeginPlay();
//    UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      BeginPlay()"));
//}
#pragma endregion