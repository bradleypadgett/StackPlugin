#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "StackHandle.generated.h"



class UStack;

// Represents a stack's data & behavior from the system's perspective
USTRUCT()
struct FStackHandle
{
	GENERATED_BODY()

public:
	FStackHandle();

	FStackHandle(UStack& InStack);

	bool IsValid() const;
	FGuid GetHandleID() const;
	FName GetName() const;
	void SetName(FName NewName);
	UStack* GetStack() const;

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
	

private:
	UPROPERTY()
	FGuid ID;

	UPROPERTY()
	FName Name;

	UPROPERTY()
	TObjectPtr<UStack> Stack = nullptr;

	UPROPERTY()
	bool bIsEnabled = true;

};
