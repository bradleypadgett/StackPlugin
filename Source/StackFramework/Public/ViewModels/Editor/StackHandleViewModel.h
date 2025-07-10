#pragma once
#include "Misc/Guid.h"
#include "Templates/SharedPointer.h"



class FStackSystemViewModel;
class FStackViewModel;
class UStackState;
struct FStackHandle;
class UStackRootViewModel;

class FStackHandleViewModel : public TSharedFromThis<FStackHandleViewModel>
{
public:
	FStackHandleViewModel();
	~FStackHandleViewModel();

	void Initialize(TSharedRef<FStackSystemViewModel> InSystemViewModel, FGuid InStackID, FName InName, UStackState* InStackState);

	FGuid GetHandleID() const;
	FName GetName() const;
	void SetName(FName NewName);

	FText GetDisplayNameText() const;
	bool CanRename() const;
	void OnNameCommitted(const FText& NewText);

	UStackState* GetStackState() const;
	TSharedRef<FStackSystemViewModel> GetSystemViewModel() const;
	TSharedRef<FStackViewModel> GetStackViewModel() const;

private:
	FStackHandle* StackHandle;

	TWeakPtr<FStackSystemViewModel> SystemViewModel;
	TSharedRef<FStackViewModel> StackViewModel;
	TObjectPtr<UStackRootViewModel> RootViewModel;

	FGuid HandleID;
	FName Name;
	UStackState* StackState;

	bool bIsRenamePending;
};
