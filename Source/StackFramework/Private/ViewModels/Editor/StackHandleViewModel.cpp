#include "ViewModels/Editor/StackHandleViewModel.h"
#include "ViewModels/Editor/StackSystemViewModel.h"
#include "ViewModels/Editor/StackRootViewModel.h"
#include "ViewModels/Editor/StackViewModel.h"
#include "EditorData/StackEntryEditorData.h"
#include "Internationalization/Text.h"



FStackHandleViewModel::FStackHandleViewModel()
	: StackHandle(nullptr)
	, StackViewModel(MakeShared<FStackViewModel>())
	, RootViewModel(NewObject<UStackRootViewModel>())
	, HandleID(FGuid::NewGuid())
	, bIsRenamePending(false)
{
}

FStackHandleViewModel::~FStackHandleViewModel()
{
	// Cleanup if needed in the future
}

void FStackHandleViewModel::Initialize(TSharedRef<FStackSystemViewModel> InSystemViewModel, FGuid InHandleID, FName InName, UStackState* InStackState)
{
	SystemViewModel = InSystemViewModel;
	HandleID = InHandleID;
	Name = InName;
	StackState = InStackState;
	bIsRenamePending = false;
}

FGuid FStackHandleViewModel::GetHandleID() const
{
	return HandleID;
}

FName FStackHandleViewModel::GetName() const
{
	return Name;
}

void FStackHandleViewModel::SetName(FName NewName)
{
	if (NewName != Name)
	{
		Name = NewName;
		// Optionally notify listeners
	}
}

FText FStackHandleViewModel::GetDisplayNameText() const
{
	return FText::FromName(Name);
}

bool FStackHandleViewModel::CanRename() const
{
	return true;
}

void FStackHandleViewModel::OnNameCommitted(const FText& NewText)
{
	SetName(FName(*NewText.ToString()));
}

UStackState* FStackHandleViewModel::GetStackState() const
{
	return StackState;
}

TSharedRef<FStackSystemViewModel> FStackHandleViewModel::GetSystemViewModel() const
{
	return SystemViewModel.Pin().ToSharedRef();
}

TSharedRef<FStackViewModel> FStackHandleViewModel::GetStackViewModel() const
{
	return StackViewModel;
}