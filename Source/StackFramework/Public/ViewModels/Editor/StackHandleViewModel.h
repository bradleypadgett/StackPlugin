#pragma once
#include "Misc/Guid.h"
#include "Templates/SharedPointer.h"



class FStackSystemViewModel;
class FStackViewModel;
class UStackEditorData;
struct FStackHandle;
class UStackRootViewModel;

class FStackHandleViewModel : public TSharedFromThis<FStackHandleViewModel>
{
public:
	FStackHandleViewModel();
	~FStackHandleViewModel();

	void Initialize(TSharedRef<FStackSystemViewModel> InSystemViewModel, FGuid InStackID, FName InName, UStackEditorData* InEditorData);

	FGuid GetHandleID() const;
	FName GetName() const;
	void SetName(FName NewName);

	FText GetDisplayNameText() const;
	bool CanRename() const;
	void OnNameCommitted(const FText& NewText);

	UStackEditorData* GetEditorData() const;
	TSharedRef<FStackSystemViewModel> GetSystemViewModel() const;
	TSharedRef<FStackViewModel> GetStackViewModel() const;

private:
	FStackHandle* StackHandle;

	TWeakPtr<FStackSystemViewModel> SystemViewModel;
	TSharedRef<FStackViewModel> StackViewModel;
	TObjectPtr<UStackRootViewModel> RootViewModel;

	FGuid StackID;
	FName Name;
	UStackEditorData* EditorData;

	bool bIsRenamePending;
};
