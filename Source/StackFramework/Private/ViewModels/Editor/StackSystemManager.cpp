#include "ViewModels/Editor/StackSystemManager.h"
#include "ViewModels/Editor/StackSystemGraphManager.h"
#include "EditorData/StackSystemEditorData.h"
#include "EditorData/StackEditorData.h"
#include "Utilities/StackEditorUtilities.h"
#include "ViewModels/StackRoot.h"
#include "ViewModels/Editor/StackHandleManager.h"
#include "ViewModels/Editor/StackManager.h"
#include "ViewModels/Editor/StackRootManager.h"
#include "ViewModels/Editor/StackSelectionManager.h"
#include "StackSystem.h"
#include "StackHandle.h"
#include "Stack.h"
#include "Editor/StackNode.h"
#include "Widgets/SBoxPanel.h"
#include "StackFramework/StackFramework.h"



FStackSystemManager::FStackSystemManager()
{

}

FStackSystemManager::~FStackSystemManager()
{
	// Only unregister if the module is still loaded
	if (System)
	{
		if (FStackFrameworkModule* FrameworkModule = FModuleManager::GetModulePtr<FStackFrameworkModule>("StackFramework"))
		{
			FrameworkModule->UnregisterSystemManager(System);
		}
	}
}

void FStackSystemManager::Initialize(UStackSystem& InSystem, bool bIsTemporarySystem)
{
	System = &InSystem;

	FStackFrameworkModule::Get().RegisterSystemManager(System, AsShared());

	SelectionManager = NewObject<UStackSelectionManager>(GetTransientPackage());
	SelectionManager->Initialize(SharedThis(this));
	// TO-DO ~ hook up delegate

	SystemGraphManager = MakeShared<FStackSystemGraphManager>();
	SystemGraphManager->Initialize(SharedThis(this));

	SystemRootManager = NewObject<UStackRootManager>(GetTransientPackage());
	// TO-DO ~ hook up delegate

}

UStackSystem& FStackSystemManager::GetSystem() const
{
	return *System;
}

UStackRootManager* FStackSystemManager::GetSystemStackRootManager()
{
	return SystemRootManager;
}


void FStackSystemManager::RefreshAll()
{
	// TO-DO ~ remember to trigger a compile here once compilation is supported later on

	RefreshHandleManagers();
	SystemRootManager->InitializeStack(this->AsShared(), TSharedPtr<FStackHandleManager>());
}

void FStackSystemManager::RefreshHandleManagers()
{
	TArray<TSharedRef<FStackHandleManager>> OldManagers = HandleManagers;
	HandleManagers.Empty();

	int32 NumHandles = System->GetNumHandles();
	UE_LOG(LogTemp, Warning, TEXT("RefreshHandleManagers: System has %d handles."), NumHandles);

	for (int i = 0; i < System->GetNumHandles(); ++i)
	{
		// for each handle
		FStackHandle* Handle = &GetSystem().GetHandle(i);
		TSharedPtr<FStackHandleManager> NewHandleManager;

		// reuse or make new handle
		if (i < OldManagers.Num())
		{
			NewHandleManager = OldManagers[i];
		}
		else
		{
			NewHandleManager = MakeShared<FStackHandleManager>();
			// TO-DO ~ hook up delegates
		}

		HandleManagers.Add(NewHandleManager.ToSharedRef());
		NewHandleManager->Initialize(SharedThis(this), i);
	}

	// cleanup leftovers
	for (int32 i = System->GetNumHandles(); i < OldManagers.Num(); ++i)
	{
		TSharedRef<FStackHandleManager> ViewModel = OldManagers[i];
		ViewModel->Reset();
	}

	for (const TSharedRef<FStackHandleManager>& Handle : HandleManagers)
	{
		UE_LOG(LogTemp, Warning, TEXT("RefreshHandleManagers: HandleManager with HandleID %s."), *Handle->GetHandleID().ToString());
	}

	// OnHandleManagersChanged.Broadcast();
}

void FStackSystemManager::ResetHandleManagers()
{
	for (TSharedRef<FStackHandleManager> LocalManager : HandleManagers)
		LocalManager->Reset();
}


TSharedPtr<FStackHandleManager> FStackSystemManager::GetHandleManagerFromID(const FGuid& InHandleID) const
{
	for (const TSharedRef<FStackHandleManager>& Handle : HandleManagers)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetHandleManagerFromID: Checking HandleID %s."), *Handle->GetHandleID().ToString());
		if (Handle->GetHandleID() == InHandleID)
		{
			UE_LOG(LogTemp, Warning, TEXT("GetHandleManagerFromID: Found matching HandleID %s."), *InHandleID.ToString());
			return Handle;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("GetHandleManagerFromID: No matching HandleID for %s."), *InHandleID.ToString());
	return nullptr;
}

TSharedPtr<FStackHandleManager> FStackSystemManager::GetHandleManagerFromStack(const UStack& InStack) const
{
	/*if (UStackEditorData* StackEditorData = InStack.GetStackEditorData())
	{
		for (TSharedRef<FStackHandleManager> Handle : HandleManagers)
		{
			if (StackState == Handle->GetStackManager()->GetStack().GetStackEditorData())
			{
				return Handle;
			}
		}
	}*/
	return nullptr;
}


void FStackSystemManager::SetStackSource(TScriptInterface<IStackSource> InStackSource)
{
	check(InStackSource);
	StackSource = InStackSource;
}

IStackSource* FStackSystemManager::GetStackSource() const
{
	check(StackSource);
	return StackSource.GetInterface();
}

UStackSystemEditorData& FStackSystemManager::GetSystemEditorData() const
{
	check(System); // Ensure System is valid
	return *System->GetSystemEditorData();
}

void FStackSystemManager::AddStackSource(TScriptInterface<IStackSource> InStackSource)
{
	if (InStackSource)
	{
		StackSources.AddUnique(InStackSource);
	}
}

TArray<TScriptInterface<IStackSource>> FStackSystemManager::GetAllStackSources() const
{
	TArray<TScriptInterface<IStackSource>> Result;
	//for (auto& WeakStack : StackSources)
	//{
	//	if (TScriptInterface<IStackSource> TempStack = WeakStack.Get())
	//	{
	//		Result.Add(TempStack);
	//	}
	//}
	return Result;
}

void FStackSystemManager::SetActiveStackSource(TScriptInterface<IStackSource> InStackSource)
{
	ActiveStackSource = InStackSource;
}

TScriptInterface<IStackSource> FStackSystemManager::GetActiveStackSource() const
{
	return ActiveStackSource;
}

//////////////////////////////////////////

TSharedPtr<FStackHandleManager> FStackSystemManager::AddEmptyStackToSystem()
{
	FName UniqueName = MakeUniqueObjectName(GetTransientPackage(), UStack::StaticClass(), TEXT("Stack"));

	UStack* NewStack = NewObject<UStack>(GetTransientPackage(), UniqueName);
	NewStack->SetFlags(RF_Transactional);
	NewStack->SetUniqueStackName(UniqueName.ToString());
	NewStack->Initialize();

	UE_LOG(LogTemp, Warning, TEXT("AddEmptyStackToSystem: Created UStack %s, calling AddStackToSystem."), *UniqueName.ToString());

	TSharedPtr<FStackHandleManager> Result = AddStackToSystem(*NewStack);

	if (!Result.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("AddEmptyStackToSystem: AddStackToSystem returned nullptr for stack %s."), *UniqueName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AddEmptyStackToSystem: AddStackToSystem returned valid handle for stack %s."), *UniqueName.ToString());
	}

	return Result;
}


TSharedPtr<FStackHandleManager> FStackSystemManager::AddStackToSystem(UStack& Stack)
{
	// avoids dangling pointers
	ResetHandleManagers();

	// Start adding the stack to the system. gives back wrapped handle ID !!!
	const FGuid StackHandleID = FStackEditorUtilities::AddStackToSystem(GetSystem(), Stack);
	UE_LOG(LogTemp, Warning, TEXT("AddStackToSystem: Added stack, got handle ID %s."), *StackHandleID.ToString());

	RefreshAll();

	TSharedPtr<FStackHandleManager> Handle = GetHandleManagerFromID(StackHandleID);
	if (!Handle.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("AddStackToSystem: GetHandleManagerFromID failed for handle ID %s."), *StackHandleID.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AddStackToSystem: GetHandleManagerFromID succeeded for handle ID %s."), *StackHandleID.ToString());
	}

	return Handle;

	// TO-DO ~ Refactor to add this to the selection before giving the handle
	//return GetHandleManagerFromID(StackHandleID);
}

void FStackSystemManager::SetSelectedEntry(UStackEntry* InEntry)
{
	SelectedEntry = InEntry;
}

UStackEntry* FStackSystemManager::GetSelectedEntry() const
{
	return SelectedEntry.Get();
}

UStackSelectionManager* FStackSystemManager::GetSelectionManager() const
{
	return SelectionManager;
}


TSharedRef<SWidget> FStackSystemManager::CreatePaletteWidget()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(STextBlock).Text(FText::FromString(TEXT("🧩 Palette (stub)")))
		];
}
