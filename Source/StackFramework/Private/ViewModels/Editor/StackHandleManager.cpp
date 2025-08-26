#include "ViewModels/Editor/StackHandleManager.h"
#include "ViewModels/Editor/StackSystemManager.h"
#include "StackSystem.h"
#include "ViewModels/Editor/StackRootManager.h"
#include "ViewModels/Editor/StackManager.h"
#include "EditorData/StackRootEditorData.h"
#include "Internationalization/Text.h"
#include "StackHandle.h"



FStackHandleManager::FStackHandleManager()
	: StackHandle(nullptr)
	, StackManager(MakeShared<FStackManager>())
	, StackRootManager(NewObject<UStackRootManager>())
	, bIsRenamePending(false)
{
}

FStackHandleManager::~FStackHandleManager()
{
	// Cleanup if needed in the future
}

void FStackHandleManager::Initialize(TSharedRef<FStackSystemManager> InSystemManager, int32 InHandleIndex)
{
	SystemManagerWeak = InSystemManager;
	HandleIndex = InHandleIndex;
	bIsRenamePending = false;
	StackHandle = &InSystemManager->GetSystem().GetHandle(InHandleIndex);
	StackManager->Initialize(*StackHandle->GetStack());
	// TO-DO ~ hook up selection delegate for StackManager 

	StackRootManager->InitializeStack(InSystemManager, SharedThis(this));
}

FGuid FStackHandleManager::GetHandleID() const
{
	return StackHandle ? StackHandle->GetHandleID() : FGuid();
}


FName FStackHandleManager::GetName() const
{
	return StackHandle ? StackHandle->GetName() : FName();
}

bool FStackHandleManager::CanRename() const
{
	return true;
}

void FStackHandleManager::SetName(FName NewName)
{
	if (StackHandle) StackHandle->SetName(NewName);
}

void FStackHandleManager::OnNameCommitted(const FText& NewText)
{
	SetName(FName(*NewText.ToString()));
}

TSharedRef<FStackSystemManager> FStackHandleManager::GetSystemManager() const
{
	return SystemManagerWeak.Pin().ToSharedRef();
}

TSharedRef<FStackManager> FStackHandleManager::GetStackManager() const
{
	return StackManager;
}

UStackRootManager* FStackHandleManager::GetStackRootManager()
{
	return StackRootManager;
}

void FStackHandleManager::Reset()
{
	SystemManagerWeak.Reset();
	StackManager->Reset();
	StackRootManager->Reset();
	StackHandle = nullptr;
}