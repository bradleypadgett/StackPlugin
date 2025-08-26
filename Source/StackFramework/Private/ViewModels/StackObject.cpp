#include "ViewModels/StackObject.h"
#include "ViewModels/StackEntry.h"
#include "ViewModels/StackItem.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "IPropertyRowGenerator.h"



UStackObject::UStackObject()
{
	bIsTopLevel = false;
	bHideTopLevelCategories = false;
}

void UStackObject::Initialize(
	const FStackEntryContext& InEntryContext,
	UObject* InObject,
	bool bInIsTopLevel,
	bool bInHideTopLevelCategories,
	FString InOwnerEntryEditorDataKey)
{
	FString InEntryEditorDataKey = FString::Printf(TEXT("%s-%s"), *InOwnerEntryEditorDataKey, *InObject->GetName());
	Super::Initialize(InEntryContext, InEntryEditorDataKey, InOwnerEntryEditorDataKey);

	WeakObject = InObject;
	bIsTopLevel = bInIsTopLevel;
	bHideTopLevelCategories = bInHideTopLevelCategories;
}

void UStackObject::FinalizeInternal()
{
	return;
}

void UStackObject::NotifyPreChange(FProperty* PropertyAboutToChange)
{
	return;
}

void UStackObject::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged)
{
	return;
}

void UStackObject::RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues)
{
	UObject* Object = WeakObject.Get();
	if (!Object)
	{
		return;
	}

	// TO-DO ~ Refactor property row generator
	if (!PropertyRowGenerator.IsValid())
	{
		FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		FPropertyRowGeneratorArgs Args;
		Args.NotifyHook = this;
		PropertyRowGenerator = PropertyEditorModule.CreatePropertyRowGenerator(Args);
		PropertyRowGenerator->SetObjects({ Object });

		PropertyRowGenerator->OnRowsRefreshed().AddUObject(this, &UStackObject::OnPropertyRowsRefreshed);
	}

	PropertyRowGenerator->InvalidateCachedState();

	// For now, just flattening all root nodes (no category collapsing)
	TArray<TSharedRef<IDetailTreeNode>> RootNodes = PropertyRowGenerator->GetRootTreeNodes();

	for (TSharedRef<IDetailTreeNode> Node : RootNodes)
	{
		// TO-DO ~ maybe wrap this node into a UStackPropertyRow-style child
	}
}

void UStackObject::OnPropertyRowsRefreshed()
{
	RefreshChildren();
}
