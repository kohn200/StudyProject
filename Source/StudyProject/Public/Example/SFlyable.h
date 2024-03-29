// SFlyable.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SFlyable.generated.h"

USTRUCT()
struct FBirdData
{
	GENERATED_BODY()

public:
	FBirdData() {}

	FBirdData(const FString& InName, int32 InID) : m_Name(InName), m_ID(InID) {}

	friend FArchive& operator<<(FArchive& Ar, FBirdData& InBirdData)
	{
		Ar << InBirdData.m_Name;
		Ar << InBirdData.m_ID;

		return Ar;
	}

	bool operator==(const FBirdData& InBirdData) const
	{
		return m_ID == InBirdData.m_ID;
	}

	friend uint32 GetTypeHash(const FBirdData& InBirdData)
	{
		return GetTypeHash(InBirdData.m_ID);
	}
	
	UPROPERTY()
	FString m_Name = TEXT("DefaultBirdName");
	
	UPROPERTY()
	int32 m_ID = 0;
};

UINTERFACE(MinimalAPI)
class USFlyable : public UInterface		// Ŭ���� ������ ������ �� ���
{
	GENERATED_BODY()
};

/**
 * 
 */
class STUDYPROJECT_API ISFlyable	// �Լ� �ۼ� �� ����
{
	GENERATED_BODY()

public:
	virtual void Fly() = 0;
};
