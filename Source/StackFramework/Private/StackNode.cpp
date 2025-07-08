#include "StackNode.h"
#include "Graph/StackGraphSchema.h"
#include "ViewModels/Editor/StackSystemViewModel.h"
#include "StackSystem.h"
#include "Widgets/Editor/StackEditorStyle.h"
#include "ToolMenu.h"
#include "ToolMenuSection.h"
#include "GraphEditorActions.h"
#include "Framework/Commands/GenericCommands.h"



#define LOCTEXT_NAMESPACE "StackNode"

UStackNode::UStackNode()
	: OwningSystem(nullptr)
{
	bCanRenameNode = true;
};

void UStackNode::Initialize(UStackSystem* InAssetContext)
{
	OwningSystem = InAssetContext;
}

FText UStackNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return OwningSystem != nullptr
		? FText::FromString(OwningSystem->GetName())
		: LOCTEXT("UnnamedStackNode", "Unnamed Stack");
}

FLinearColor UStackNode::GetNodeTitleColor() const
{
	// TO-DO ~ Replace with stack style
	return FLinearColor(0.15f, 0.5f, 1.0f);
}

bool UStackNode::GetCanRenameNode() const
{
	return true;
}

bool UStackNode::CanUserDeleteNode() const
{
	return true;
}

bool UStackNode::CanDuplicateNode() const
{
	return true;
}

void UStackNode::OnRenameNode(const FString& NewName)
{
	if (OwningSystem)
	{
		OwningSystem->Rename(*NewName, nullptr);
	}
}

void UStackNode::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& EditSection = Menu->AddSection("StackEdit", LOCTEXT("Edit", "Edit"));

	EditSection.AddMenuEntry(FGenericCommands::Get().Cut);
	EditSection.AddMenuEntry(FGenericCommands::Get().Copy);
	EditSection.AddMenuEntry(FGenericCommands::Get().Delete);
	EditSection.AddMenuEntry(FGenericCommands::Get().Rename);
}

bool UStackNode::CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const
{
	return Schema->IsA<UStackGraphSchema>();
}

UStackSystem* UStackNode::GetOwningSystem() const
{
	return OwningSystem;
}

#undef LOCTEXT_NAMESPACE
