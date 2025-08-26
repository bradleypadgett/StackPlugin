#pragma once
#include "Misc/Guid.h"
#include "Templates/SharedPointer.h"



class FStackSystemManager;
class FStackManager;
struct FStackHandle;
class UStackRootManager;

class FStackHandleManager : public TSharedFromThis<FStackHandleManager>
{
public:
	FStackHandleManager();
	~FStackHandleManager();

	void Initialize(TSharedRef<FStackSystemManager> InSystemManager, int32 InHandleIndex);

	FGuid GetHandleID() const;
	FName GetName() const;
	void SetName(FName NewName);

	bool CanRename() const;
	void OnNameCommitted(const FText& NewText);

	TSharedRef<FStackSystemManager> GetSystemManager() const;
	TSharedRef<FStackManager> GetStackManager() const;
	UStackRootManager* GetStackRootManager();

	void Reset();

private:
	FStackHandle* StackHandle;
	int32 HandleIndex;

	TWeakPtr<FStackSystemManager> SystemManagerWeak;
	TSharedRef<FStackManager> StackManager;
	TObjectPtr<UStackRootManager> StackRootManager;

	bool bIsRenamePending;
};
