// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SViewCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Inputs/SInputConfigData.h"

ASViewCharacter::ASViewCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASViewCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (::IsValid(PlayerController) == true)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (::IsValid(Subsystem) == true)
		{
			Subsystem->AddMappingContext(PlayerCharacterInputMappingContext, 0);
		}
	}
}

void ASViewCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	SetViewMode(EViewMode::BackView);

	DestArmLength = 400.f;
	DestArmRotation = FRotator::ZeroRotator;
}

void ASViewCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (CurrentViewMode)
	{
	case EViewMode::None:
		break;
	case EViewMode::BackView:
		break;
	case EViewMode::QuarterView:
	{
		if (KINDA_SMALL_NUMBER < DirectionToMove.SizeSquared())
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
			DirectionToMove = FVector::ZeroVector;
		}
	}
		break;
	case EViewMode::End:
		break;
	default:
		break;
	}

	if (KINDA_SMALL_NUMBER < abs(DestArmLength - SpringArmComponent->TargetArmLength))
	{
		SpringArmComponent->TargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, DestArmLength, DeltaSeconds, ArmLengthChangeSpeed);
		SpringArmComponent->SetRelativeRotation(FMath::RInterpTo(SpringArmComponent->GetRelativeRotation(), DestArmRotation, DeltaSeconds, ArmRotationChangeSpeed));
	}
}

void ASViewCharacter::SetViewMode(EViewMode InViewMode)
{
	if (CurrentViewMode == InViewMode)
		return;

	CurrentViewMode = InViewMode;

	switch (CurrentViewMode)
	{
	case EViewMode::BackView:
		//SpringArmComponent->TargetArmLength = 400.f;
		//SpringArmComponent->SetRelativeRotation(FRotator::ZeroRotator);

		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;

		SpringArmComponent->bUsePawnControlRotation = true;
		SpringArmComponent->bDoCollisionTest = true;
		SpringArmComponent->bInheritPitch = true;
		SpringArmComponent->bInheritRoll = true;
		SpringArmComponent->bInheritYaw = true;

		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);
		
		break;
	case EViewMode::QuarterView:
		//SpringArmComponent->TargetArmLength = 900.f;
		//SpringArmComponent->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;

		SpringArmComponent->bUsePawnControlRotation = false;
		SpringArmComponent->bDoCollisionTest = false;
		SpringArmComponent->bInheritPitch = false;
		SpringArmComponent->bInheritRoll = false;
		SpringArmComponent->bInheritYaw = false;

		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);
		break;
	case EViewMode::End:
		break;
	default:
		break;
	}
}

void ASViewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (::IsValid(EnhancedInputComponent) == true)
	{
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->MoveAction, ETriggerEvent::Triggered, this, &ASViewCharacter::Move);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->LookAction, ETriggerEvent::Triggered, this, &ASViewCharacter::Look);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->ChangeViewAction, ETriggerEvent::Started, this, &ASViewCharacter::ChangeView);
	}
}

void ASViewCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D MovementVector = InValue.Get<FVector2D>();

	switch (CurrentViewMode)
	{
	case EViewMode::None:
		break;
	case EViewMode::BackView:
	{
		const FRotator ControlRotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardVector, MovementVector.X);
		AddMovementInput(RightVector, MovementVector.Y);

		break;
	}
	case EViewMode::QuarterView:
		DirectionToMove.X = MovementVector.X;
		DirectionToMove.Y = MovementVector.Y;
		break;
	case EViewMode::End:
		break;
	default:
		AddMovementInput(GetActorForwardVector(), MovementVector.X);
		AddMovementInput(GetActorRightVector(), MovementVector.Y);
		break;
	}
}

void ASViewCharacter::Look(const FInputActionValue& InValue)
{
	FVector2D LookVector = InValue.Get<FVector2D>();

	switch (CurrentViewMode)
	{
	case EViewMode::None:
		break;
	case EViewMode::BackView:
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
		break;
	case EViewMode::QuarterView:
		break;
	case EViewMode::End:
		break;
	default:
		break;
	}
}

void ASViewCharacter::ChangeView(const FInputActionValue& InValue)
{
	switch (CurrentViewMode)
	{
	case EViewMode::None:
		break;
	case EViewMode::BackView:
		/* Case 1. 이전에 BackView 시점이었다면
			
		   BackView는 컨트롤 회전값 == 스프링암 회전값.
		   그러나 QuarterView는 캐릭터의 회전값 == 컨트롤 회전값.
		   따라서 시점 변경 전에 캐릭터의 현재 회전값을 컨트롤 회전에 세팅해둬야 함.
		   안그러면 컨트롤 회전이 일어나면서 현재 캐릭터의 회전값이 스프링암 회전값(컨트롤 회전값)으로 동기화됨.
		*/

		GetController()->SetControlRotation(GetActorRotation());	// 캐릭터의 현재 회전값을 컨트롤 회전에 세팅해둬야 함.
		DestArmLength = 900.f;
		DestArmRotation = FRotator(-45.f, 0.f, 0.f);
		SetViewMode(EViewMode::QuarterView);
		break;
	case EViewMode::QuarterView:
		/* Case 2. 이전에 QuarterView 시점이었다면

		   컨트롤 회전이 캐릭터 회전에 맞춰져 있다.
		   QuaterView는 현재 스프링암이 회전값을 컨트롤 회전에 세팅해둔 상태에서 시점 변경해야 올바름.
		   BackView에서는 컨트롤 로테이션이 폰의 회전과 동기화되고 폰의 회전이 스프링 암의 회전과 동기화.
		   따라서 스프링 암의 회전을 임의로 설정할 수 없음. 0으로 고정
		*/

		GetController()->SetControlRotation(FRotator::ZeroRotator);	// 컨트롤 로테이션이 폰의 회전과 동기화. 0으로 고정
		DestArmLength = 400.f;
		DestArmRotation = FRotator::ZeroRotator;	// 폰의 회전이 스프링 암의 회전과 동기화. 0으로 고정
		SetViewMode(EViewMode::BackView);
		break;
	case EViewMode::End:
		break;
	default:
		break;
	}
}
