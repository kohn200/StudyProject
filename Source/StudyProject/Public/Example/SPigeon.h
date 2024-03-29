// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SFlyable.h"
#include "SPigeon.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USPigeon : public UObject, public ISFlyable
{
	GENERATED_BODY()
	
public:
	USPigeon();

	virtual void Fly() override;

	const FString& GetName() const { return m_Name; }
	void SetName(const FString& InName) { m_Name = InName; }
	
	int32 GetID() const { return m_ID; }
	void SetID(int32 InID) { m_ID = InID; }

	virtual void Serialize(FArchive& Ar) override;

private:
	UPROPERTY()
	FString m_Name;

	UPROPERTY()
	int32 m_ID;
};
