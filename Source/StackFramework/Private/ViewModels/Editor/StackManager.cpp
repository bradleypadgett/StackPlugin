#include "ViewModels/Editor/StackManager.h"
#include "Providers/StackSource.h"
#include "EditorData/StackEditorData.h"
#include "Stack.h"
#include "EditorData/StackRootEditorData.h"
#include "ViewModels/Editor/StackHandleManager.h"
#include "ViewModels/Editor/StackScriptManager.h"



FStackManager::FStackManager()
{

}

FStackManager::~FStackManager()
{

}

void FStackManager::Initialize(TScriptInterface<IStackSource> InStackSource)
{
	StackSource = InStackSource;
}

void FStackManager::Initialize(UStack& InStack)
{
	StackWeak = &InStack;
}

UStackEditorData& FStackManager::GetStackEditorData() const
{
	return *StackSource->GetStackEditorData();
}

IStackSource* FStackManager::GetStackSource() const
{
	return StackSource.GetInterface();
}


TSharedPtr<FStackHandleManager> FStackManager::GetHandleManager(const FStackHandleManager& InHandleManager) const
{
	return HandleManager;
}
/*
TSharedRef<FStackScriptManager> FStackManager::GetScriptManager()
{
	return ScriptManager;
}*/

FStackManager::FOnHandleRemoved& FStackManager::OnHandleRemoved()
{
	return OnHandleRemovedDelegate;
}

void FStackManager::Reset()
{

}