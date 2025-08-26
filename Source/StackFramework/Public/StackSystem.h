#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "StackHandle.h"
#include "StackSystem.generated.h"



struct FStackHandle;
class UStackSystemEditorData;

UCLASS(BlueprintType)
class STACKFRAMEWORK_API UStackSystem : public UObject
{
	GENERATED_BODY()

public:
	UStackSystem();

	virtual void PostInitProperties() override;

	UStackSystemEditorData* GetSystemEditorData();

	int32 GetNumHandles() const { return Handles.Num(); }
	const TArray<FStackHandle>& GetHandles() const { return Handles; }
	TArray<FStackHandle>& GetHandles() { return Handles; }

	FStackHandle& GetHandle(int HandleIndex);

	void ClearHandles() { Handles.Reset(); }
	FStackHandle AddHandle(UStack& InStack, FName InStackName);
	void RemoveHandle(FStackHandle& InHandleToRemove);


	UPROPERTY(EditAnywhere, Category = "System")
	FName Name;

protected:
	UPROPERTY()
	TArray<FStackHandle> Handles;

private:

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UStackSystemEditorData> SystemEditorData;
#endif

};
