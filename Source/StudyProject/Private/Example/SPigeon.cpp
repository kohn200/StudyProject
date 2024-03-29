// Fill out your copyright notice in the Description page of Project Settings.

#include "Example/SPigeon.h"

USPigeon::USPigeon()
{
	m_Name = TEXT("Pigeon CDO");
	m_ID = 0;
}

void USPigeon::Fly()
{
	UE_LOG(LogTemp, Log, TEXT("%s is now flying."), *m_Name);
}

void USPigeon::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	Ar << m_Name;
	Ar << m_ID;
}
