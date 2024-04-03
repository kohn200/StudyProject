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
		/* Case 1. ������ BackView �����̾��ٸ�
			
		   BackView�� ��Ʈ�� ȸ���� == �������� ȸ����.
		   �׷��� QuarterView�� ĳ������ ȸ���� == ��Ʈ�� ȸ����.
		   ���� ���� ���� ���� ĳ������ ���� ȸ������ ��Ʈ�� ȸ���� �����ص־� ��.
		   �ȱ׷��� ��Ʈ�� ȸ���� �Ͼ�鼭 ���� ĳ������ ȸ������ �������� ȸ����(��Ʈ�� ȸ����)���� ����ȭ��.
		*/

		GetController()->SetControlRotation(GetActorRotation());	// ĳ������ ���� ȸ������ ��Ʈ�� ȸ���� �����ص־� ��.
		DestArmLength = 900.f;
		DestArmRotation = FRotator(-45.f, 0.f, 0.f);
		SetViewMode(EViewMode::QuarterView);
		break;
	case EViewMode::QuarterView:
		/* Case 2. ������ QuarterView �����̾��ٸ�

		   ��Ʈ�� ȸ���� ĳ���� ȸ���� ������ �ִ�.
		   QuaterView�� ���� ���������� ȸ������ ��Ʈ�� ȸ���� �����ص� ���¿��� ���� �����ؾ� �ùٸ�.
		   BackView������ ��Ʈ�� �����̼��� ���� ȸ���� ����ȭ�ǰ� ���� ȸ���� ������ ���� ȸ���� ����ȭ.
		   ���� ������ ���� ȸ���� ���Ƿ� ������ �� ����. 0���� ����
		*/

		GetController()->SetControlRotation(FRotator::ZeroRotator);	// ��Ʈ�� �����̼��� ���� ȸ���� ����ȭ. 0���� ����
		DestArmLength = 400.f;
		DestArmRotation = FRotator::ZeroRotator;	// ���� ȸ���� ������ ���� ȸ���� ����ȭ. 0���� ����
		SetViewMode(EViewMode::BackView);
		break;
	case EViewMode::End:
		break;
	default:
		break;
	}
}
