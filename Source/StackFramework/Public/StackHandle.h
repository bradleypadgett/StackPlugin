#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Providers/StackSource.h"
#include "StackHandle.generated.h"



class UStack;

USTRUCT()
struct FStackHandle
{
	GENERATED_BODY()

public:
	FStackHandle();

	//FStackHandle(const TScriptInterface<IStackSource>& InStackSource);
	FStackHandle(UStack& InStack);

	bool IsValid() const;
	FGuid GetHandleID() const;
	FName GetName() const;
	void SetName(FName NewName);

	TObjectPtr<UStack> GetStack();

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

	//IStackSource* GetSource() const { return StackSource.GetInterface(); }
	//UStack& GetStack() { return StackSource->GetStack(); }
	//virtual const UStack& GetStack() const { return StackSource->GetStack(); }

private:
	//UPROPERTY()
	//TScriptInterface<IStackSource> StackSource;

	UPROPERTY()
	TObjectPtr<UStack> Stack;

	UPROPERTY()
	FGuid ID;

	UPROPERTY()
	FName Name;

	UPROPERTY()
	bool bIsEnabled = true;

};
