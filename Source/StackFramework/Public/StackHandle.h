#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Definition/StackSource.h"
#include "StackHandle.generated.h"



class UStack;

// Represents a stack's data & behavior from the system's perspective
USTRUCT()
struct FStackHandle
{
	GENERATED_BODY()

public:
	FStackHandle();

	FStackHandle(const TScriptInterface<IStackSource>& InStackSource);

	bool IsValid() const;
	FGuid GetHandleID() const;
	FName GetName() const;
	void SetName(FName NewName);

	FORCEINLINE bool operator==(const FStackHandle& Other) const
	{
		return ID == Other.ID;
	}

	FORCEINLINE bool operator!=(const FStackHandle& Other) const
	{
		return !(*this == Other);
	}

	FORCEINLINE friend uint32 GetTypeHash(const FStackHandle& Handle)
	{
		return GetTypeHash(Handle.ID);
	}
	
public:

	IStackSource* GetSource() const { return StackSource.GetInterface(); }
	UStack& GetStack() { return StackSource->GetStack(); }
	virtual const UStack& GetStack() const { return StackSource->GetStack(); }

private:
	UPROPERTY()
	TScriptInterface<IStackSource> StackSource;

	UPROPERTY()
	FGuid ID;

	UPROPERTY()
	FName Name;

	UPROPERTY()
	bool bIsEnabled = true;

};
