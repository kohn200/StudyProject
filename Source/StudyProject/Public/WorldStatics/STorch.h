// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STorch.generated.h"

UCLASS()
class STUDYPROJECT_API ASTorch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTorch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASTorch", Meta = (AllowPrivateAccess))
	TObjectPtr<class UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASTorch", Meta = (AllowPrivateAccess))
	TObjectPtr<class UStaticMeshComponent> BodyStaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASTorch", Meta = (AllowPrivateAccess))
	TObjectPtr<class UPointLightComponent> PointLightComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASTorch", Meta = (AllowPrivateAccess))
	TObjectPtr<class UParticleSystemComponent> ParticleSystemComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ASTorch", Meta = (AllowPrivateAccess))
	int32 ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ASTorch", Meta = (AllowPrivateAccess))
	float RotationSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASElectricityPole", Meta = (AllowPrivateAccess))
	TObjectPtr<class URotatingMovementComponent> RotatingMovementComponent;

};
