// USGameInstance.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USGameInstance : public UGameInstance
{
public:
	GENERATED_BODY()

public:
	USGameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

private:
	UPROPERTY()
	FString m_Name;

	UPROPERTY()
	TObjectPtr<class USPigeon> m_SerializedPigeon;
};

